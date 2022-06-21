#ifndef VIEWER_H
#define VIEWER_H

#include "Analyzer.h"
#include "GEMReplay.h"
#include "APVStripMapping.h"
#include "HistoWidget.h"

#include <QMainWindow>
#include <QPushButton>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QMenu>
#include <QMenuBar>
#include <QString>
#include <QLineEdit>
#include <QTextEdit>

#include <vector>
#include <string>
#include <deque>

class Viewer : public QWidget
{
    Q_OBJECT

public:
    Viewer(QWidget *parent = 0);
    ~Viewer() {}

    void InitGui();
    void AddMenuBar();

    void InitLayout();
    void InitCtrlInterface();
    void InitLeftTab();
    void ClearLeftTab();
    void InitLeftView();
    void InitRightView();

    // init detector analyzers
    void InitAnalyzer();

    bool FileExist(const char* path);

    // setters
    void SetNumberOfTabs();

public slots:
    void SetFile(const QString &);
    void SetFileSplit(const QString &);
    void SetRootFileOutputPath(const QString &);
    void SetPedestalOutputPath(const QString &);
    void SetPedestalMaxEvents(const QString &);
    void DrawEvent(int);
    void DrawGEMRawHistos(int);
    void OpenFile();
    void GeneratePedestal_obsolete();
    void GeneratePedestal();
    void Replay();

private:
    // layout
    QVBoxLayout *pMainLayout;
    QHBoxLayout *pDrawingLayout;
    QVBoxLayout *pLeftLayout;
    QVBoxLayout *pRightLayout;

    // contents to show
    QWidget *pDrawingArea;                  // whole drawing area (left + right)
    QWidget *pLeft;                         // left area
    QWidget *pRight;                        // right area
    QTabWidget *pLeftTab = nullptr;         // tab for the left side area
    std::vector<HistoWidget*> vTabCanvas;   // tab contents, use self-implemented HistoWidgets
    QWidget *pRightCtrlInterface;           // the control interface on right side

    QWidget *pRightCanvas;                  // a place holder for QMainCanvas (root)

    // menu bar
    QMenu *pMenu;
    QMenuBar *pMenuBar;
    // open file (line input)
    QLineEdit *file_indicator;
    // print info on the gui
    QTextEdit *pLogBox;

    // number of tabs
    int nTab = 12;

    // GEM analzyer
    Analyzer *pAnalyzer;
    // evio file to be analyzed
    std::string fFile = "data/gem_cleanroom_1440.evio.0";
    // pedestal save default path
    std::string fPedestalSavePath = "Rootfiles/1440.root";
    uint32_t fPedestalMaxEvents = 5000;

    // gem replay
    GEMReplay *pGEMReplay;
    std::string fRootFileSavePath = "./gem_replay.root";
    int fFileSplit = -1;

private:
    // section for viewer status
    int event_number_checked = 0;
    size_t max_cache_events = 110;
    std::deque<std::map<APVAddress, std::vector<int>>> event_cache;
};

#endif
