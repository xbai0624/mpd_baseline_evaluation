#include <iostream>
#include <iomanip>
#include <algorithm>

#include "Globals.h"
#include "PedestalQualityCheck.h"

#include <TH1F.h>

#define nTS 6

PedestalQualityCheck* PedestalQualityCheck::instance = nullptr;

PedestalQualityCheck::~PedestalQualityCheck()
{
    // place holder
}

void PedestalQualityCheck::Init()
{
    save_path = global_variables::BaselineRootFileOutputPath;
    _file = new TFile(save_path.c_str(), "recreate");
    _tree = new TTree("T", "noise check");

    _tree -> Branch("event_number", &event_number, "event_number/I");
    _tree -> Branch("napv", &napv, "napv/I");

    _tree -> Branch("crate", crate, "crate[napv]/I");
    _tree -> Branch("mpd", mpd, "mpd[napv]/I");
    _tree -> Branch("adc_ch", adc_ch, "adc_ch[napv]/I");

    for(int i=0; i<nTS; ++i) {
        _tree -> Branch(Form("commonMode_ts%d", i), commonMode_ts[i], Form("commonMode_ts%d[napv]/F", i));
        _tree -> Branch(Form("maxADC_ts%d", i), maxADC_ts[i], Form("maxADC_ts%d[napv]/F", i));
        _tree -> Branch(Form("minADC_ts%d", i), minADC_ts[i], Form("minADC_ts%d[napv]/F", i));
        _tree -> Branch(Form("rangeADC_ts%d", i), rangeADC_ts[i], Form("rangeADC_ts%d[napv]/F", i));
        _tree -> Branch(Form("RMS_ts%d", i), RMS[i], Form("RMS_ts%d[napv]/F", i));
    }

    _tree -> Branch("rangeCommonMode", rangeCommonMode, "rangeCommonMode[napv]/F");

    // timing information
    _tree -> Branch("coarse_timing", coarse_timing, "coarse_timing[napv]/l"); // ULong64_t, 64 bit unsigned int
    _tree -> Branch("fine_timing", fine_timing, "fine_timing[napv]/i"); // 32 bit unsigned int
}

#define TS_LEN 129
void PedestalQualityCheck::FillEvent(const std::unordered_map<APVAddress, std::vector<int>> & apvs,
        const std::unordered_map<MPDAddress, std::pair<uint64_t, uint32_t>> &timing)
{
    static int event_id = 0;
    // remove the first 500 events
    //if(event_id < 500) {
    //    event_id++;
    //    return;
    //}
    event_number = event_id;
    // time sample adc analysis -- common mode
    auto get_commonMode = [&](const std::vector<int> &data, std::vector<float> &vCommonMode,
            std::vector<float> &vMaxADC, std::vector<float> &vMinADC)
    {
        for(int i=0; i<nTS; ++i)
        {
            std::vector<int> v_ts(data.begin() + i * TS_LEN, data.begin() + (i + 1) * TS_LEN);
            v_ts.pop_back(); // remove last element
            std::sort(v_ts.begin(), v_ts.end()); // small -> big, ascending order

            float _common_mode=0, _min=0, _max=0;

            for(int d=10; d<128-10; ++d) // remove the highest 10 strips and lowest 10 strips
                _common_mode += v_ts[d];

            _common_mode /= 108;
            _min = v_ts[10];
            _max = v_ts[128-10-1];

            // pass the results
            vCommonMode.push_back(_common_mode);
            vMaxADC.push_back(_max);
            vMinADC.push_back(_min);
        }
    };

    // time sample adc analysis -- rms noise
    auto get_rms = [&](const std::vector<int> &data, const std::vector<float> &vCommonMode,
            std::vector<float> &vRMS)
    {
        for(int i=0; i<nTS; ++i)
        {
            std::vector<int> v_ts(data.begin() + i * TS_LEN, data.begin() + (i + 1) * TS_LEN);
            v_ts.pop_back();

            TH1F h("h", "h", 4400, -2200, 2200);
            for(auto &adc: v_ts)
                h.Fill((float)adc - vCommonMode[i]);

            float sigma = h.GetRMS();
            vRMS.push_back(sigma);
        }
    };

    int i = 0;
    //napv = static_cast<int>(apvs.size()) - 1; // -1 : remove one noisy apv
    napv = static_cast<int>(apvs.size());
    if(napv <= 0) 
        return;

    //static APVAddress addr_cut(7, 15, 3); // this apv not stable

    for(auto &apv: apvs)
    {
        // cut off a malfunction apv
        //if(addr_cut == apv.first)
        //    continue;

        // apv address
        crate[i] = apv.first.crate_id;
        mpd[i]   = apv.first.mpd_id;
        adc_ch[i]   = apv.first.adc_ch;

        // common mode
        std::vector<float> vCommonMode;
        std::vector<float> vMaxADC;
        std::vector<float> vMinADC;

        get_commonMode(apv.second, vCommonMode, vMaxADC, vMinADC);
        assert(vCommonMode.size() == nTS);
        for(int ts=0; ts<nTS; ++ts){
            commonMode_ts[ts][i] = vCommonMode[ts];
            maxADC_ts[ts][i]     = vMaxADC[ts];
            minADC_ts[ts][i]     = vMinADC[ts];
            rangeADC_ts[ts][i]   = vMaxADC[ts] - vMinADC[ts];
        }

        std::sort(vCommonMode.begin(), vCommonMode.end());
        rangeCommonMode[i] = vCommonMode[nTS-1] - vCommonMode[0];

        // RMS noise
        std::vector<float> vRMS;
        get_rms(apv.second, vCommonMode, vRMS);
        assert(vRMS.size() == nTS);
        for(int ts=0; ts<nTS; ++ts) {
            RMS[ts][i] = vRMS[ts];
        }

        // timing information
        MPDAddress mpd_addr(crate[i], mpd[i]);
        if(timing.find(mpd_addr) == timing.end()) {
            std::cout<<__func__<<" Error: timing information not set for MPD: "<<mpd_addr
                     <<std::endl;
        }
        else {
            coarse_timing[i] = timing.at(mpd_addr).first;
            fine_timing[i] = timing.at(mpd_addr).second;
        }

        ++i;
    }

    _tree -> Fill();
    event_id++;
}

void PedestalQualityCheck::Save()
{
    std::cout<<"Writing file to: "<<save_path<<std::endl;
    _file -> Write();
    _file -> Close();
}

void  PedestalQualityCheck::SetOutputFilePath(const std::string &path)
{
    save_path = path;
}
