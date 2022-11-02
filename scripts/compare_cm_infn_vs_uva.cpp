
void format_histo(TH1F* h)
{
    h -> SetLineWidth(2);

    h -> Scale(1./h->Integral());
    h -> GetXaxis() -> SetRangeUser(-200, 200);

    h -> GetYaxis() -> SetTitle("Normalized Counts");

    h -> GetXaxis() -> SetLabelSize(0.06);
    h -> GetYaxis() -> SetLabelSize(0.06);

    h -> GetXaxis() -> SetTitleSize(0.08);
    h -> GetYaxis() -> SetTitleSize(0.08);

    h -> GetXaxis() -> SetTitleOffset(0.6);
    h -> GetYaxis() -> SetTitleOffset(0.7);
}


void get_cm(const char* path, vector<TH1F*> &common_mode, string option="uva")
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

        // crate24_mpd8_adc9
        if(option.find("infn") == string::npos)
        {
            // uva results, 4, 5
            if(title.find("crate24_mpd4") == string::npos)
                continue;

            common_mode.push_back(h);
        }
        else 
        {
            // infn,  2, 4
            if(title.find("crate25_mpd2") == string::npos)
                continue;

            common_mode.push_back(h);
        }
    }

    cout<<"from file: "<<path<<": cm histos: "<<common_mode.size()
        <<endl;
}

void compare(const vector<TH1F*> &uva, const vector<TH1F*> &infn)
{
    if(uva.size() != infn.size())
    {
        cout<<"uva vs infn histos not match..."<<endl;
        return;
    }

    TCanvas *c = new TCanvas("c", "c", 1600, 900);
    c -> Divide(4, 4);

    for(size_t i=0; i<uva.size(); i++)
    {
        c -> cd(i+1);
        gPad -> SetFrameLineWidth(2);

        format_histo(uva[i]);
        uva[i] -> SetLineColor(2);
        uva[i] -> Draw("hist");

        format_histo(infn[i]);
        infn[i] -> Draw("hist sames");

        gPad -> Modified(); gPad -> Update();
        TPaveStats* s1 = (TPaveStats*)uva[i] -> GetListOfFunctions()->FindObject("stats");
        s1 -> SetX1NDC(0.55), s1 -> SetX2NDC(0.85);
        s1 -> SetY1NDC(0.6), s1 -> SetY2NDC(0.8);
        s1 ->Draw();

        TPaveStats* s2 = (TPaveStats*)infn[i] -> GetListOfFunctions()->FindObject("stats");
        s2 -> SetX1NDC(0.55), s2 -> SetX2NDC(0.85);
        s2 -> SetY1NDC(0.35), s2 -> SetY2NDC(0.55);
        s2 ->Draw();

        gPad -> Modified(); gPad -> Update();

        TLegend *leg = new TLegend(0.15, 0.6, 0.45, 0.8);
        leg -> AddEntry(uva[i], "UVa Hall Data", "lep");
        leg -> AddEntry(infn[i], "INFN Hall Data", "lep");
        leg -> Draw();
    }

}


void compare_cm_infn_vs_uva()
{
    const char* path = "data/result_histos/129610_results.root";

    vector<TH1F*> uva_cm, infn_cm;
    get_cm(path, uva_cm, "uva");
    get_cm(path, infn_cm, "infn");

    compare(uva_cm, infn_cm);
}
