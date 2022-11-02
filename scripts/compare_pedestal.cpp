
void get_pedestal(const char* path, vector<TH1F*> &offset, vector<TH1F*> &noise)
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

        // discard INFN for now
        if(title.find("25") != string::npos)
            continue;

        if(title.find("offset") == string::npos)
            noise.push_back(h);
        else
            offset.push_back(h);
    }

    cout<<"from file: "<<path<<": offset histos: "<<offset.size()
        <<", noise histos: "<<noise.size()
        <<endl;
}

#define HISTO_PER_CANVAS 16
void compare_histos(const vector<TH1F*> &histos1, const vector<TH1F*> &histos2, const int N,
        const char* l1 = "h1", const char* l2 = "h2")
{
    int nhistos = N < (int)histos1.size() ? N : (int)histos1.size();
    nhistos = nhistos < (int)histos2.size() ? nhistos : (int)histos2.size();

    int nCanvas = nhistos / HISTO_PER_CANVAS;
    if( nhistos % HISTO_PER_CANVAS > 0)
        nCanvas += 1;

    TCanvas * c[nCanvas];
    for(int i=0; i<nCanvas; i++) {
        c[i] = new TCanvas(Form("c%d", i), Form("c%d", i), 1200, 900);
        c[i] -> Divide(4, 4);
    }

    TLegend *leg[nhistos];

    for(int i=0; i<nhistos; i++) {
        int nc = i / HISTO_PER_CANVAS;
        int index = i % HISTO_PER_CANVAS + 1;

        c[nc] -> cd(index);
        gPad -> SetFrameLineWidth(2);

        histos1[i] -> Draw();
        histos1[i] -> GetXaxis() -> SetTitle("Channel");
        histos1[i] -> GetYaxis() -> SetTitle("ADC");
        histos1[i] -> GetXaxis() -> SetLabelSize(0.07);
        histos1[i] -> GetYaxis() -> SetLabelSize(0.07);
        histos1[i] -> GetXaxis() -> SetTitleSize(0.08);
        histos1[i] -> GetYaxis() -> SetTitleSize(0.08);
        histos1[i] -> GetXaxis() -> SetTitleOffset(0.6);
        histos1[i] -> GetYaxis() -> SetTitleOffset(0.6);
 
        histos2[i] -> SetLineColor(2);
        histos2[i] -> Draw("same");
 
        leg[i] = new TLegend(0.2, 0.15, 0.8, 0.35); // offset
        //leg[i] = new TLegend(0.2, 0.65, 0.8, 0.85); // noise
        leg[i] -> AddEntry(histos1[i], l1, "lep");
        leg[i] -> AddEntry(histos2[i], l2, "lep");
        leg[i] -> Draw();
    } 
}


void compare_pedestal()
{
    const char* path_sbs_hall  = "tmp_plots/sbs_pedestal_in_hall.root";
    vector<TH1F*> sbs_hall_offset, sbs_hall_noise;
    get_pedestal(path_sbs_hall, sbs_hall_offset, sbs_hall_noise);

    const char* path_bb_hall = "tmp_plots/bigbite_pedestal.root";
    vector<TH1F*> bb_hall_offset, bb_hall_noise;
    get_pedestal(path_bb_hall, bb_hall_offset, bb_hall_noise);

    compare_histos(sbs_hall_offset, bb_hall_offset, 64, "SBS GEMs in Hall", "SBS GEMs in EEL");
    //compare_histos(sbs_hall_noise, bb_hall_noise, 64, "SBS GEMs in Hall", "SBS GEMs in EEL");
}
