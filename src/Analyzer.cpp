#include "Analyzer.h"
#include "ConfigSetup.h"

#include <iostream>
#include <fstream>

using namespace std;

Analyzer::Analyzer()
{
    Init();
}

Analyzer::~Analyzer()
{
    // place holder
}

void Analyzer::Init()
{
    file_reader = new EvioFileReader();
    event_parser = new EventParser();

#ifdef USE_SSP
        mpd_ssp_decoder = new MPDSSPRawEventDecoder();
        event_parser -> RegisterRawDecoder(static_cast<int>(Bank_TagID::MPD_SSP), mpd_ssp_decoder);
#endif

#ifdef USE_VME
        mpd_vme_decoder = new MPDVMERawEventDecoder();
        event_parser -> RegisterRawDecoder(static_cast<int>(Bank_TagID::MPD_VME), mpd_vme_decoder);
#endif

    file_is_open = false;
}

void Analyzer::SetFile(const std::string &path)
{
    input_file = path;
    file_reader -> CloseFile();
    file_reader -> SetFile(input_file.c_str());

    event_number = 0;
}

std::unordered_map<APVAddress, std::vector<int>> Analyzer::GetEvent()
{
    std::unordered_map<APVAddress, std::vector<int>> res;
    res.clear();

    if(!file_is_open)
        OpenFile();
 
    // open file failed, return
    if(!file_is_open) {
        std::cout<<"Error: failed openning file: "<<input_file<<std::endl;
        return res;
    }

    if( file_reader -> ReadNoCopy(&pBuf, &fBufLen) != S_SUCCESS) {
        std::cout<<"Info: finished reading file: "<<input_file<<std::endl;
        return res;
    }

    event_parser -> ParseEvent(pBuf, fBufLen);

#ifdef USE_SSP
        const std::unordered_map<APVAddress, std::vector<int>> & res_dec 
            = mpd_ssp_decoder -> GetAPV();
#endif
#ifdef USE_VME
        const std::unordered_map<APVAddress, std::vector<int>> & res_dec 
            = mpd_vme_decoder -> GetAPV();
#endif

    return res_dec;
}

static std::string parse_run_number(const std::string &input_file)
{
    size_t pos_start = input_file.find_last_of('/');
    size_t pos_end = input_file.find_last_of(".evio");
    size_t length = pos_end - pos_start - std::string(".evio").size() - 1;

    // e.g. gem_cleanroom_4432.evio.0
    std::string file_name = input_file.substr(pos_start+1, length);

    pos_start = file_name.find_last_of('_');
    length = file_name.size() - pos_start;
    file_name = file_name.substr(pos_start+1, length);
    file_name = "Rootfiles/pedestals_"+file_name+".root";

    return file_name;
}

void Analyzer::GeneratePedestal([[maybe_unused]]const char* path)
{
    /*
    // 1): generate pedestal
    std::cout<<"INFO::Preparing pedestals..."<<std::endl;
    pedestal -> SetDataFile(input_file.c_str());
    pedestal -> CalculatePedestal();
    std::string pedestal_output_file_name = parse_run_number(input_file);
    //pedestal -> SavePedestalHisto(pedestal_output_file_name.c_str());
    std::cout<<"INFO::Pedestals file written to: "<<pedestal_output_file_name<<std::endl;
    */
    // 2): common mode quality check


    [[maybe_unused]] static int counter = 0;
    while( file_reader -> ReadNoCopy(&pBuf, &fBufLen) == S_SUCCESS)
    {
        // use event 2000 - 4000 
        //if(counter++ < 13000) continue;
        //if(counter++ > 15000) break;

        event_parser -> ParseEvent(pBuf, fBufLen);

#ifdef USE_SSP
        const std::unordered_map<APVAddress, std::vector<int>> & res_dec 
            = mpd_ssp_decoder -> GetAPV();
        const std::unordered_map<MPDAddress, std::pair<uint64_t, uint32_t>> &
            timing = mpd_ssp_decoder -> GetTiming();
#endif
#ifdef USE_VME
        const std::unordered_map<APVAddress, std::vector<int>> & res_dec 
            = mpd_vme_decoder -> GetAPV();
        const std::unordered_map<MPDAddress, std::pair<uint64_t, uint32_t>> &
            timing = mpd_vme_decoder -> GetTiming();
#endif

    }
}

void Analyzer::CloseFile()
{
    file_reader -> CloseFile();

    file_is_open = false;
}

void Analyzer::OpenFile()
{
    std::ifstream infile(input_file.c_str());
    if(!infile.good()) {
        std::cout<<"File: "<<input_file<<" not exist."<<std::endl;
        return;
    }

    std::cout<<"Info: Openning file: "<<input_file<<std::endl;
    SetFile(input_file);

    file_reader -> OpenFile();

    file_is_open = true;
}
