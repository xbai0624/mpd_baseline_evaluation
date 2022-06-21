////////////////////////////////////////////////////////////////
// Algorithm for pedestal calculation is arguable
// If one wants to discuss it, 
// please email Xinzhan Bai @ xb4zp@virginia.edu
// -------- 11/13/2020

#include "GEMPedestal.h"
#include "MPDVMERawEventDecoder.h"
#include "MPDSSPRawEventDecoder.h"

#include <iostream>
#include <thread>
#include <mutex>

#include <TFile.h>
#include <TROOT.h>
#include <TKey.h>


////////////////////////////////////////////////////////////////
// if computing resource is limited, then turn off multi-threading
// by setting NTHREAD to 1

#define NTHREAD 3
std::mutex mtx;

////////////////////////////////////////////////////////////////
// ctor

GEMPedestal::GEMPedestal()
{
    // place holder
}

////////////////////////////////////////////////////////////////
// dtor

GEMPedestal::~GEMPedestal()
{
    Clear();
}

////////////////////////////////////////////////////////////////
// set file used for calculating pedestal

void GEMPedestal::SetDataFile(const char* path)
{
    data_file_path = path;

    // get ready for storing data
    Clear();
}

////////////////////////////////////////////////////////////////
// set total number of events used for calculating pedestal

void GEMPedestal::SetNumberOfEvents(int num)
{
    fNumberEvents = static_cast<uint32_t>(num);
}

////////////////////////////////////////////////////////////////
// get total number of events used for calculating pedestal

int GEMPedestal::GetNumberOfEvents() const
{
    return static_cast<int>(fNumberEvents);
}

////////////////////////////////////////////////////////////////
// calculate pedestal

void GEMPedestal::CalculatePedestal()
{
    if(!file_reader)
        file_reader = new EvioFileReader();
    else
        file_reader -> CloseFile();

    file_reader -> SetFile(data_file_path);
    file_reader -> OpenFile();

    EventParser *event_parser[NTHREAD];
    MPDVMERawEventDecoder *mpd_vme_decoder[NTHREAD];
    //MPDSSPRawEventDecoder *mpd_ssp_decoder[NTHREAD];

    for(int i=0;i<NTHREAD;i++){
        event_parser[i] = new EventParser();
        mpd_vme_decoder[i] = new MPDVMERawEventDecoder();
        event_parser[i]->RegisterRawDecoder(static_cast<int>(Bank_TagID::MPD_VME), mpd_vme_decoder[i]);
    }

    uint32_t nEvents = 0;

    std::vector<std::thread> vth;
    for(int i=0;i<NTHREAD;i++){
        vth.emplace_back(&GEMPedestal::GetEvent, this, file_reader, event_parser[i], std::ref(nEvents));
    }

    for(auto &i: vth)
        i.join();

    //GenerateAPVPedestal_using_histo(); // slow
    GenerateAPVPedestal_using_vec();     // fast
}

////////////////////////////////////////////////////////////////
// precess batch events

void GEMPedestal::GetEvent(EvioFileReader *file_reader, EventParser *event_parser,
        uint32_t &nEvents)
{
    const uint32_t *pBuf;
    uint32_t fBufLen;
    bool run = true;
    while(run)
    {
        mtx.lock();
        run = (file_reader -> ReadNoCopy(&pBuf, &fBufLen)) == S_SUCCESS;
        nEvents++;
        mtx.unlock();

        event_parser->ParseEvent(pBuf, fBufLen);
        [[maybe_unused]] auto & decoded_data = dynamic_cast<MPDVMERawEventDecoder*>(
                event_parser->GetRawDecoder(static_cast<int>(Bank_TagID::MPD_VME)))
            ->GetAPV();

        CalculateEventRawPedestal(decoded_data);

        if(nEvents >= fNumberEvents)
            break;
    }
}

////////////////////////////////////////////////////////////////
// calculate raw pedestal for one event

void GEMPedestal::CalculateEventRawPedestal(
        const std::unordered_map<APVAddress, std::vector<int>> & event_data)
{
    for(auto &i: event_data)
    {
        //RawAPVUnit_histo(i); // slow
        RawAPVUnit_vec(i);     // fast
    }

    //RawPedestalThread(event_data, 0, static_cast<int>(event_data.size()));
}

////////////////////////////////////////////////////////////////
// process a sub range of the current event, for parallel
// obsolete function

void GEMPedestal::RawPedestalThread(const std::unordered_map<APVAddress, std::vector<int>> & data,
        int beg, int end)
{
    std::unordered_map<APVAddress, std::vector<int>>::const_iterator it_beg = data.begin();
    std::unordered_map<APVAddress, std::vector<int>>::const_iterator it_end = data.begin();
    std::advance(it_beg, beg);
    std::advance(it_end, end);

    for(;it_beg!=it_end;it_beg++)
    {
        RawAPVUnit_histo(*it_beg);
    }
}


////////////////////////////////////////////////////////////////
// process raw data in one APV, using TH1F (slow)

void GEMPedestal::RawAPVUnit_histo(const std::unordered_map<APVAddress, std::vector<int>>::value_type & i)
{
    const std::vector<StripRawADC> & apv_raw_data = DecodeAPV(i.second);
    auto apv_ts_commonMode = GetTimeSampleCommonMode(apv_raw_data);

    for(auto &strip: apv_raw_data)
    {
        APVStripAddress addr(i.first, strip.stripNo);

        if(mAPVStripNoise.find(addr) == mAPVStripNoise.end())
        {
            mtx.lock();
            mAPVStripNoise[addr] = new TH1F(
                    Form("noise_crate_%d_mpd_%d_ch_%d_strip_%d", addr.crate_id, addr.mpd_id, addr.adc_ch, addr.strip_no), 
                    "strip noise", 800, -400, 400
                    );
            mAPVStripOffset[addr] = new TH1F(
                    Form("offset_crate_%d_mpd_%d_ch_%d_strip_%d", addr.crate_id, addr.mpd_id, addr.adc_ch, addr.strip_no), 
                    "strip offset", 1000, 400, 1400
                    );
            mtx.unlock();
        }

        int time_sample_size = strip.GetTimeSampleSize();

        float offset = 0;
        for(auto &adc: strip.v_adc)
            offset += (float)adc;
        offset /= (float)time_sample_size;

        float noise = 0;
        for(int ts = 0; ts<time_sample_size;ts++)
            noise += ((float)strip.v_adc[ts] - (float)apv_ts_commonMode[ts]);
        noise /= (float)time_sample_size;

        mtx.lock();
        mAPVStripNoise[addr] -> Fill(noise);
        mAPVStripOffset[addr] -> Fill(offset); 
        mtx.unlock();
    }
}

////////////////////////////////////////////////////////////////
// process raw data in one APV, using std::vector (fast)

void GEMPedestal::RawAPVUnit_vec(const std::unordered_map<APVAddress, std::vector<int>>::value_type & i)
{
    const std::vector<StripRawADC> & apv_raw_data = DecodeAPV(i.second);
    auto apv_ts_commonMode = GetTimeSampleCommonMode(apv_raw_data);

    for(auto &strip: apv_raw_data)
    {
        APVStripAddress addr(i.first, strip.stripNo);

        int time_sample_size = strip.GetTimeSampleSize();

        float offset = 0;
        for(auto &adc: strip.v_adc)
            offset += (float)adc;
        offset /= (float)time_sample_size;

        float noise = 0;
        for(int ts = 0; ts<time_sample_size;ts++)
            noise += ((float)strip.v_adc[ts] - (float)apv_ts_commonMode[ts]);
        noise /= (float)time_sample_size;

        mtx.lock();
        mAPVStripNoiseVec[addr].push_back(noise);
        mAPVStripOffsetVec[addr].push_back(offset); 
        mtx.unlock();
    }
}


////////////////////////////////////////////////////////////////////////////////
// a helper to find highest 10 adc strips
// binary insert to a sorted vector and keep that vector to a fixed length
// sorting costs too much running time

static void binary_insert(std::vector<int> &vec, const float &val, size_t start, size_t end)
{
    if(start + 1 == end)
    {
        for(size_t i=0;i<start;i++)
        {
            vec[i] = vec[i+1];
        }
        vec[start] = val;
        return;
    }

    size_t pos = (start + end) / 2;
    if(vec[pos] >= val)
        binary_insert(vec, val, start, pos);
    else
        binary_insert(vec, val, pos, end);
}

////////////////////////////////////////////////////////////////
// get common Mode for each time sample in one APV

std::vector<float> GEMPedestal::GetTimeSampleCommonMode(const std::vector<StripRawADC> &apv_data)
{
    if(apv_data.size() != APV_STRIP_SIZE) {
        std::cout<<"Error: incorrect apv channel number."
            <<std::endl;
        exit(0);
    }

    int time_sample = apv_data[0].GetTimeSampleSize();

    // common mode in each time sample
    std::vector<float> res(time_sample, 0); 

    // one must remove the first 10 highest strips during time sample common mode calculation
    // due to the FIR (Finite Impulse Response) issue
#define FIR_SIZE 10
    std::vector<std::vector<int>> fir_strips(time_sample, std::vector<int>(FIR_SIZE, -99999));

    for(auto &strip: apv_data)
    {
        for(int ts=0;ts<time_sample;ts++) {
            res[ts] += (float)strip.v_adc[ts];

            if(strip.v_adc[ts] > fir_strips[ts][0])
                binary_insert(fir_strips[ts], strip.v_adc[ts], 0, FIR_SIZE);
        }
    }

    // remove 10 highest strips
    for(int ts=0; ts<time_sample; ts++) {
        float _tmp = 0.;
        for(auto &d: fir_strips[ts])
            _tmp += (float)d;
        res[ts] -= _tmp;
    }

    // common mode
    for(int ts = 0; ts<time_sample;ts++)
        res[ts] /= ((float)APV_STRIP_SIZE - FIR_SIZE);

    return res;
}

////////////////////////////////////////////////////////////////
// generate pedestal for each APV using the strip noise and offset
// using TH1F (slow)

void GEMPedestal::GenerateAPVPedestal_using_histo()
{
    // generate noise
    for(auto &i: mAPVStripNoise) {
        APVAddress addr(i.first.crate_id, i.first.mpd_id, i.first.adc_ch);
        int strip_no = i.first.strip_no;

        if(mAPVNoiseHisto.find(addr) == mAPVNoiseHisto.end())
            mAPVNoiseHisto[addr] = new TH1F(
                    Form("noise_crate_%d_mpd_%d_ch_%d", addr.crate_id, addr.mpd_id, addr.adc_ch), 
                    Form("noise_crate_%d_mpd_%d_ch_%d_RMS", addr.crate_id, addr.mpd_id, addr.adc_ch), 
                    APV_STRIP_SIZE+20, -10, APV_STRIP_SIZE+10);

        float noise = i.second->GetRMS();
        mAPVNoiseHisto[addr] -> SetBinContent(strip_no+10, noise);
        mAPVNoise[addr].push_back(noise);
    }

    // generate offset
    for(auto &i: mAPVStripOffset) {
        APVAddress addr(i.first.crate_id, i.first.mpd_id, i.first.adc_ch);
        int strip_no = i.first.strip_no;

        if(mAPVOffsetHisto.find(addr) == mAPVOffsetHisto.end())
            mAPVOffsetHisto[addr] = new TH1F(
                    Form("offset_crate_%d_mpd_%d_ch_%d", addr.crate_id, addr.mpd_id, addr.adc_ch), 
                    Form("offset_crate_%d_mpd_%d_ch_%d", addr.crate_id, addr.mpd_id, addr.adc_ch), 
                    APV_STRIP_SIZE+20, -10, APV_STRIP_SIZE+10);

        float offset = i.second -> GetMean();
        mAPVOffsetHisto[addr] -> SetBinContent(strip_no + 10, offset);
        mAPVOffset[addr].push_back(offset);
    }
}

////////////////////////////////////////////////////////////////
// generate pedestal for each APV using the strip noise and offset
// using vector (fast)

void GEMPedestal::GenerateAPVPedestal_using_vec()
{
    // generate noise for each apv
    for(auto &i: mAPVStripNoiseVec) {
        APVAddress addr(i.first.crate_id, i.first.mpd_id, i.first.adc_ch);
        int strip_no = i.first.strip_no;

        if(mAPVNoiseHisto.find(addr) == mAPVNoiseHisto.end())
            mAPVNoiseHisto[addr] = new TH1F(
                    Form("noise_crate_%d_mpd_%d_ch_%d", addr.crate_id, addr.mpd_id, addr.adc_ch), 
                    Form("noise_crate_%d_mpd_%d_ch_%d_RMS", addr.crate_id, addr.mpd_id, addr.adc_ch), 
                    APV_STRIP_SIZE+20, -10, APV_STRIP_SIZE+10
                    );

        float noise = GetRMS(i.second);
        mAPVNoiseHisto[addr] -> SetBinContent(strip_no+10, noise);
        mAPVNoise[addr].push_back(noise);
    }

    // generate offset
    for(auto &i: mAPVStripOffsetVec) {
        APVAddress addr(i.first.crate_id, i.first.mpd_id, i.first.adc_ch);
        int strip_no = i.first.strip_no;

        if(mAPVOffsetHisto.find(addr) == mAPVOffsetHisto.end())
            mAPVOffsetHisto[addr] = new TH1F(
                    Form("offset_crate_%d_mpd_%d_ch_%d", addr.crate_id, addr.mpd_id, addr.adc_ch), 
                    Form("offset_crate_%d_mpd_%d_ch_%d", addr.crate_id, addr.mpd_id, addr.adc_ch), 
                    APV_STRIP_SIZE+20, -10, APV_STRIP_SIZE+10
                    );

        float offset = GetMean(i.second);
        mAPVOffsetHisto[addr] -> SetBinContent(strip_no + 10, offset);
        mAPVOffset[addr].push_back(offset);
    }
}

////////////////////////////////////////////////////////////////
// a helper: get mean of a vector (for offset calculation)

float GEMPedestal::GetMean(const std::vector<float> &data)
{
    TH1F h("h", "h", 1000, 400, 1400);
    for(auto &i: data)
        h.Fill(i);

    int res = h.GetMean();
    return res;
}

////////////////////////////////////////////////////////////////
// a helper: get RMS of a vector (for noise calculation)

float GEMPedestal::GetRMS(const std::vector<float> &data)
{
    TH1F h("h", "h", 800, -400, 400);
    for(auto &i: data)
        h.Fill(i);

    float res = h.GetRMS();
    return res;
}


////////////////////////////////////////////////////////////////
// decode raw apv data 

std::vector<StripRawADC> GEMPedestal::DecodeAPV(std::vector<int> const & apv_data)
{
    std::vector<StripRawADC> res;

    int event_size = static_cast<int>(apv_data.size());
    if(event_size % MPD_APV_TS_LEN != 0) {
        std::cout<<"Warning: apv data size incorrect. Data might be corrupted."
            <<std::endl;
        return res;
    }
    int nTimeSample = event_size / MPD_APV_TS_LEN;

    for(int i=0; i<APV_STRIP_SIZE; i++) 
    {
        StripRawADC strip_raw_adc;
        strip_raw_adc.stripNo = i;

        for(int ts=0;ts<nTimeSample;ts++) {
            strip_raw_adc.v_adc.push_back(apv_data[i + ts*MPD_APV_TS_LEN]);
        }

        res.push_back(strip_raw_adc);
    }

    return res;
}

////////////////////////////////////////////////////////////////
// get pedestal noise

const std::unordered_map<APVAddress, std::vector<float>> & GEMPedestal::
GetAPVNoise() const
{
    return mAPVNoise;
}

////////////////////////////////////////////////////////////////
// get pedestal offset

const std::unordered_map<APVAddress, std::vector<float>> & GEMPedestal::
GetAPVOffset() const
{
    return mAPVOffset;
}

////////////////////////////////////////////////////////////////
// get pedestal noise histos

const std::unordered_map<APVAddress, TH1F*> & GEMPedestal::
GetAPVNoiseHisto() const 
{
    return mAPVNoiseHisto;
}

////////////////////////////////////////////////////////////////
// get pedestal offset histos

const std::unordered_map<APVAddress, TH1F*> & GEMPedestal::
GetAPVOffsetHisto() const
{
    return mAPVOffsetHisto;
}

////////////////////////////////////////////////////////////////
// save pedestal histograms to disk

void GEMPedestal::SavePedestalHisto(const char* path)
{
    TFile *f = new TFile(path, "recreate");
    for(auto &i: mAPVNoiseHisto) {
        i.second->SetDirectory(f);
        i.second->GetXaxis()->SetTitle("APV Channel No.");
        i.second->GetYaxis()->SetTitle("ADC");
        i.second->Write();
    }
    for(auto &i: mAPVOffsetHisto) {
        i.second->SetDirectory(f);
        i.second->GetXaxis()->SetTitle("APV Channel No.");
        i.second->GetYaxis()->SetTitle("ADC");
        i.second-> Write();
    }
    f->Close();
}

////////////////////////////////////////////////////////////////
// save pedestal texts to disk

void GEMPedestal::SavePedestalText()
{
}

////////////////////////////////////////////////////////////////
// load pedestal histograms to momory

void GEMPedestal::LoadPedestalHisto(const char* path)
{
    TFile *f = TFile::Open(path);
    TIter keyList(f->GetListOfKeys());
    TKey *key;
    while((key = (TKey*)keyList()))
    {
        TClass *cl = gROOT -> GetClass(key->GetClassName());
        if(!cl->InheritsFrom("TH1")) continue;
        TH1F* h = (TH1F*)key->ReadObj();
        std::string name = h->GetName();
        auto apv_address = ParseAPVAddressFromString(name);
        if(name.find("noise") != std::string::npos)
            mAPVNoiseHisto[apv_address] = h;
        else if(name.find("offset") != std::string::npos)
            mAPVOffsetHisto[apv_address] = h;
    }
}

////////////////////////////////////////////////////////////////
// load pedestal texts to memory

void GEMPedestal::LoadPedestalText()
{
}

////////////////////////////////////////////////////////////////
// parse apv address from string, when loading pedstal from file

APVAddress GEMPedestal::ParseAPVAddressFromString(const std::string & s)
{
    // noise_crate_%d_mpd_%d_ch_%d
    auto search = [&](size_t pos, const std::string & str, char tok)
        -> size_t
        {
            size_t res = -1;
            for(size_t i = pos;i<str.size(); i++){
                res = i;
                char _s = static_cast<char>(str[i]);
                if(_s == tok) return res;
            }
            return res;
        };

    // crate id
    size_t pos = s.find("crate_");
    size_t pos_ = search(pos + 6, s, '_');
    int crate_id = stoi(s.substr(pos+6, pos_));
    // mpd id
    pos = s.find("mpd_");
    pos_ = search(pos+4, s, '_');
    int mpd_id = stoi(s.substr(pos+4, pos_));
    // adc channel
    pos = s.find("ch_");
    pos_ = search(pos+3, s, '_');
    int adc_ch = stoi(s.substr(pos+3, pos_));

    APVAddress res(crate_id, mpd_id, adc_ch);
    return res;
}


////////////////////////////////////////////////////////////////
// reset

void GEMPedestal::Clear()
{
    for(auto &i: mAPVNoise)
        i.second.clear();
    //mAPVNoise.clear();

    for(auto &i: mAPVOffset)
        i.second.clear();
    //mAPVOffset.clear();

    for(auto &i: mAPVNoiseHisto)
        i.second->Reset("ICESM");
    //mAPVNoiseHisto.clear();

    for(auto &i: mAPVOffsetHisto)
        i.second->Reset("ICESM");
    //mAPVOffsetHisto.clear();

    for(auto &i: mAPVStripNoise)
        i.second->Reset("ICESM");
    //mAPVStripNoise.clear();

    for(auto &i: mAPVStripOffset)
        i.second->Reset("ICESM");
    //mAPVStripOffset.clear();

    for(auto &i: mAPVStripNoiseVec) {
        i.second.clear();
    }
    mAPVStripNoiseVec.clear();

    for(auto &i: mAPVStripOffsetVec) {
        i.second.clear();
    }
    mAPVStripOffsetVec.clear();
}


////////////////////////////////////////////////////////////////
// a thread-safe unordered_map look up routine
// when one thread is looking up the map, other threads are not
// allowed to modify the map

bool GEMPedestal::APVStripIsNew(const APVStripAddress & addr)
{
    mtx.lock();
    bool res = mAPVStripNoise.find(addr) == mAPVStripNoise.end();
    mtx.unlock();

    return res;
}


