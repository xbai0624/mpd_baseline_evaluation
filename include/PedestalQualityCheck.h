/*
 *  If you want to use this class, you need to have ROOT setup properly
 *  If you don't have ROOT, then remove this from decoder.pro file
 *  and also remove it from the Analyzer.cpp file
 */

#ifndef PEDESTAL_QUALITY_CHECK_H
#define PEDESTAL_QUALITY_CHECK_H

#include <TFile.h>
#include <TTree.h>

#include <unordered_map>
#include <string>

#include "MPDDataStruct.h"

class PedestalQualityCheck
{
public:
    ~PedestalQualityCheck();

    static PedestalQualityCheck* Instance()
    {
        if(instance == nullptr)
            instance = new PedestalQualityCheck();
        return instance;
    }

    void SetOutputFilePath(const std::string &path);
    void Init();
    void FillEvent(const std::unordered_map<APVAddress, std::vector<int>> & res_dec,
            const std::unordered_map<MPDAddress, std::pair<uint64_t, uint32_t>> &timing);
    void Save();

private:
    static PedestalQualityCheck *instance;
    PedestalQualityCheck(){ /*Init();*/ }

    TFile *_file = nullptr;
    std::string save_path = "Rootfiles/1440.root";
    TTree *_tree = nullptr;

    // tree setup
    static const int MAX = 1000; // max 1000 APVs

    int event_number; // event number
    int napv; // total number of apvs

    int crate[MAX];      // crate id
    int mpd[MAX];        // mpd id
    int adc_ch[MAX];        // adc ch

    // baseline (common mode)
    // 6 time samples
    float commonMode_ts[6][MAX]; // common mode in time sample 0
    float maxADC_ts[6][MAX]; // max adc value in time sample 0 (after removing the highest and lowest 10 channels)
    float minADC_ts[6][MAX]; // min adc value in time sample 0 (after removing the highest and lowest 10 channels)
    float rangeADC_ts[6][MAX]; // (max - min) adc in time sample 0 (after removing the highest and lowest 10 channels)

    float rangeCommonMode[MAX]; // (hightest common mode - lowest common mode) out of the 6 time samples

    // noise (RMS)
    float RMS[6][MAX]; // rms noise for each time sample (Fill 128 (adc-baseline) into one histogram and take the RMS value)

    // timing information
    // timing has coarse timing and fine timing
    // coarse timing is simply apv clock counts
    // fine timing is the difference between trigger and apv clock
    // timing is MPD wise, APVs on the same MPD share the same trigger and clock
    // coarse timing is uint64_t format
    // fine timing is uint32_t format
    uint64_t coarse_timing[MAX];
    uint32_t fine_timing[MAX];
};

#endif
