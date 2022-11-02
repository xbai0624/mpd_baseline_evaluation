
void get_pedestal(const char* path, vector<TH1F*> &offset, vector<TH1F*> &noise, string org="uva")
{
    TFile *f = new TFile(path);

    TIter keyList(f->GetListOfKeys());
    TKey *key;

    while( (key = (TKey*)keyList() ) ){
        TClass *cl = gROOT -> GetClass(key -> GetClassName());
        if(!cl -> InheritsFrom("TH1"))
            continue;

        TH1F* h = (TH1F*) key -> ReadObj();
        string title = h -> GetTitle();

        // remove disconnected apvs
        // noise_crate_24_mpd_4_adc_13
        //cout<<title<<endl;
        if( title == "offset_crate_24_mpd_6_adc_12" ||
                title == "offset_crate_24_mpd_20_adc_11" ||
                title == "offset_crate_24_mpd_26_adc_8" ||
                title == "offset_crate_24_mpd_26_adc_10" ) {
            cout<<"found "<<title<<" broke."<<endl;
            continue;
        }

        if(org.find("uva") != string::npos)
        {
            if(title.find("25") != string::npos)
                continue;
        } else {
            if(title.find("25") == string::npos)
                continue;
        }

        if(title.find("offset") == string::npos)
            noise.push_back(h);
        else
            offset.push_back(h);
    }

    cout<<"from file: "<<path<<": offset histos: "<<offset.size()
        <<", noise histos: "<<noise.size()
        <<endl;
}

#define RANGE 100
void compare_histos(const vector<TH1F*> &histos1, const vector<TH1F*> &histos2,
        const char* l1 = "h1", const char* l2 = "h2")
{
    // noise compare
    //TH1F *h1 = new TH1F(l1, l1, RANGE, 2, RANGE);
    //TH1F *h2 = new TH1F(l2, l2, RANGE, 2, RANGE);
    // offset compare
    TH1F *h1 = new TH1F(l1, l1, RANGE, -300, 300);
    TH1F *h2 = new TH1F(l2, l2, RANGE, -300, 300);


    for(auto &i: histos1) {
        int nBins = i -> GetNbinsX();
        for(int b=10; b<= nBins-10; b++)
            h1 -> Fill(i -> GetBinContent(b));
    }

    for(auto &i: histos2) {
        int nBins = i -> GetNbinsX();
        for(int b=10; b<= nBins-10; b++)
            h2 -> Fill(i -> GetBinContent(b));
    }

    TCanvas *c = new TCanvas("c", "c", 1200, 900);
    gPad -> SetFrameLineWidth(2);
    h1 -> Scale(1./h1->Integral());
    h1 -> GetYaxis() -> SetTitle("Entries normalized by integral");
    h1 -> GetXaxis() -> SetTitle("ADC");
    h1 -> SetLineColor(2);
    h1 -> SetLineWidth(2);
    h1 -> SetFillColor(2);
    h1 -> SetFillStyle(3006);
    h1 -> Draw("hist");

    h2 -> Scale(1./h2->Integral());
    h2 -> SetLineColor(4);
    h2 -> SetLineWidth(2);
    h2 -> SetFillColor(4);
    h2 -> SetFillStyle(3004);
    h2 -> Draw("hist sames");

    TLegend *leg = new TLegend(0.3, 0.6, 0.5, 0.7);
    leg -> AddEntry(h1, l1, "lep");
    leg -> AddEntry(h2, l2, "lep");
    leg -> Draw();

    c -> Modified(); c -> Update();

    TPaveStats *s1 = (TPaveStats*)h1 -> GetListOfFunctions() -> FindObject("stats");
    s1 -> SetX1NDC(0.6); s1 -> SetX2NDC(0.8);
    s1 -> SetY1NDC(0.65); s1 -> SetY2NDC(0.85);
    TPaveStats *s2 = (TPaveStats*)h2 -> GetListOfFunctions() -> FindObject("stats");
    s2 -> SetX1NDC(0.6); s2 -> SetX2NDC(0.8);
    s2 -> SetY1NDC(0.4); s2 -> SetY2NDC(0.6);


    c -> Modified(); c -> Update();
}


void compare_ped_uva_vs_infn()
{
    const char* path_sbs_hall  = "tmp_plots/sbs_pedestal_in_hall.root";
    vector<TH1F*> sbs_hall_offset_uva, sbs_hall_noise_uva;
    get_pedestal(path_sbs_hall, sbs_hall_offset_uva, sbs_hall_noise_uva, "uva");

    vector<TH1F*> sbs_hall_offset_infn, sbs_hall_noise_infn;
    get_pedestal(path_sbs_hall, sbs_hall_offset_infn, sbs_hall_noise_infn, "infn");


    compare_histos(sbs_hall_offset_uva, sbs_hall_offset_infn, "UVa_Offset", "INFN_Offset");
    //compare_histos(sbs_hall_noise_uva, sbs_hall_noise_infn, "UVa_Noise", "INFN_Noise");

}
