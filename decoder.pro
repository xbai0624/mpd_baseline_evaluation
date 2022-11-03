######################################################################
# Automatically generated by qmake (3.1) Sat Nov 7 17:18:28 2020
######################################################################

TEMPLATE = app
TARGET = raw_data_viewer

CONFIG += Qt
QT += core gui widgets

QMAKE_CXXFLAGS += -std=c++17
QMAKE_CXXFLAGS -= -std=gnu++11


# self headers
INCLUDEPATH += . ./include

# coda headers
INCLUDEPATH += ${CODA}/common/include
# coda libs
LIBS += -L${CODA}/Linux-x86_64/lib -levio

# root headers
#INCLUDEPATH += ${ROOTSYS}/include
# root libs
#LIBS += -L${ROOTSYS}/lib -lCore -lRIO -lNet \
#	-lHist -lGraf -lGraf3d -lGpad -lTree \
#    -lRint -lPostscript -lMatrix -lPhysics \
#	-lGui -lRGL

MOC_DIR = moc
OBJECTS_DIR = obj

# The following define makes your compiler warn you if you use any
# feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS DEBUG #MULTI_THREAD

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += include/EvioFileReader.h \
           include/EventParser.h \
           include/GeneralEvioStruct.h \
           include/MPDVMERawEventDecoder.h \
           include/MPDSSPRawEventDecoder.h \
           include/RolStruct.h \
           include/MPDDataStruct.h \
           include/AbstractRawDecoder.h \
           include/sspApvdec.h \
           include/Viewer.h \
           include/Analyzer.h \
           include/HistoItem.h \
           include/HistoView.h \
           include/HistoWidget.h \
           include/GEMReplay.h \
           include/APVStripMapping.h \
           include/GEMStruct.h \
           include/ConfigSetup.h \
           include/Globals.h \

SOURCES += src/EvioFileReader.cpp \ 
           src/EventParser.cpp \ 
           src/MPDVMERawEventDecoder.cpp \
           src/MPDSSPRawEventDecoder.cpp \
           src/AbstractRawDecoder.cpp \
           src/MPDDataStruct.cpp \
           src/main.cpp \
           src/Viewer.cpp \
           src/Analyzer.cpp \
           src/HistoItem.cpp \
           src/HistoView.cpp \
           src/HistoWidget.cpp \
           src/GEMReplay.cpp \
           src/APVStripMapping.cpp \
           src/Globals.cpp \
