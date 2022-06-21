#include <TBox.h>
#include <TCanvas.h>

// drawring range: -800mm, 800mm
const double HL = 800; // half length
const double mm = 0.5/HL; // unit mm

// coordinate transform origin at center (drawing coord) to origin at bottom left corner (canvas coord)
double to_canvas_coord(double x) {
    return (x + HL) * mm;
}

// apv rms value
double rms_12slot[12] = {
    999, 999, 999, 999, 999, 999,
    999, 999, 999, 999, 999, 999,
};
double rms_5slot_left[5] = {
    999, 999, 999, 999, 999,
};
double rms_5slot_right[5] = {
    999, 999, 999, 999, 999,
};

void gem_geo(const char* canvas_handler = "c")
{
    TCanvas *c = new TCanvas(canvas_handler, "gem geo", 1000, 600);
    // title
    TLatex *text = new TLatex();
    text -> DrawTextNDC(
            to_canvas_coord(-300),
            to_canvas_coord(650),
            "APV baseline fluctuation RMS "
            );
    // bottom gas window
    TBox *btm_window = new TBox(
            to_canvas_coord(-700),
            to_canvas_coord(-600),
            to_canvas_coord(700),
            to_canvas_coord(600)
            );
    btm_window -> SetFillColor(38);
    btm_window -> Draw();

    // readout plane
    TBox *readout_plane = new TBox(
            to_canvas_coord(-600),
            to_canvas_coord(-750),
            to_canvas_coord(600),
            to_canvas_coord(600)
            );
    readout_plane -> SetFillColor(41);
    readout_plane -> Draw();

    // apv 12-slot
    for(int i=0;i<12;i++) {
        double x1 = -470 + i*80;
        double x2 = -470 + i*80 + 60;
        double y1 = -710;
        double y2 = -690;
        TBox *apv = new TBox(
                to_canvas_coord(x1),
                to_canvas_coord(y1),
                to_canvas_coord(x2),
                to_canvas_coord(y2)
                );
        apv -> SetFillColor(2);
        apv -> Draw();
        // draw rms value
        text -> SetTextSize(0.02);
        char ss[10];
        sprintf(ss, "%2.1f", rms_12slot[i]);
        text -> DrawTextNDC(
                to_canvas_coord(x1),
                to_canvas_coord(y1+30),
                ss
                );
    }
    // apv 5-slot left side
    for(int i=0;i<5;i++) {
        double x1 = -540;
        double x2 = -525;
        double y1 = -580 + i*120;
        double y2 = -580 + i*120 + 100;
        TBox *apv = new TBox(
                to_canvas_coord(x1),
                to_canvas_coord(y1),
                to_canvas_coord(x2),
                to_canvas_coord(y2)
                );
        apv -> SetFillColor(2);
        apv -> Draw();
        // draw rms value
        text -> SetTextSize(0.02);
        char ss[10];
        sprintf(ss, "%2.1f", rms_5slot_left[i]);
        text -> DrawTextNDC(
                to_canvas_coord(x1-50),
                to_canvas_coord(y1+30),
                ss
                );
    }
    // apv 5-slot right side
    for(int i=0;i<5;i++) {
        double x1 = 525;
        double x2 = 540;
        double y1 = 580 - i*120;
        double y2 = 580 - i*120 - 100;
        TBox *apv = new TBox(
                to_canvas_coord(x1),
                to_canvas_coord(y1),
                to_canvas_coord(x2),
                to_canvas_coord(y2)
                );
        apv -> SetFillColor(2);
        apv -> Draw();
        text -> SetTextSize(0.02);
        char ss[10];
        sprintf(ss, "%2.1f", rms_5slot_right[i]);
        text -> DrawTextNDC(
                to_canvas_coord(x2+20),
                to_canvas_coord(y2+30),
                ss
                );
    }

    // top gas window
    TBox *top_window = new TBox(
            to_canvas_coord(-500),
            to_canvas_coord(-600),
            to_canvas_coord(500),
            to_canvas_coord(600)
            );
    top_window -> SetFillColor(45);
    top_window -> Draw();

    // left HV
    TBox *hv_left = new TBox(
            to_canvas_coord(-650),
            to_canvas_coord(30),
            to_canvas_coord(-550),
            to_canvas_coord(530)
            );
    hv_left -> SetFillColor(6);
    hv_left -> Draw();

    // right hv
    TBox *hv_right = new TBox(
            to_canvas_coord(550),
            to_canvas_coord(-30),
            to_canvas_coord(650),
            to_canvas_coord(-530)
            );
    hv_right -> SetFillColor(6);
    hv_right -> Draw();
}
