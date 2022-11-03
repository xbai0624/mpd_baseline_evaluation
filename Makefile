#############################################################################
# Makefile for building: raw_data_viewer
# Generated by qmake (3.1) (Qt 5.15.2)
# Project:  decoder.pro
# Template: app
# Command: /usr/bin/qmake-qt5 -o Makefile decoder.pro
#############################################################################

MAKEFILE      = Makefile

EQ            = =

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_DEPRECATED_WARNINGS -DDEBUG -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB
CFLAGS        = -pipe -O2 -D_REENTRANT -Wall -Wextra -fPIC $(DEFINES)
CXXFLAGS      = -pipe -std=c++17 -O2 -std=gnu++11 -D_REENTRANT -Wall -Wextra -fPIC $(DEFINES)
INCPATH       = -I. -I. -Iinclude -I${CODA}/common/include -I/usr/include/qt5 -I/usr/include/qt5/QtWidgets -I/usr/include/qt5/QtGui -I/usr/include/qt5/QtCore -Imoc -I/../lib64/qt5/mkspecs/linux-g++
QMAKE         = /usr/bin/qmake-qt5
DEL_FILE      = rm -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
COPY          = cp -f
COPY_FILE     = cp -f
COPY_DIR      = cp -f -R
INSTALL_FILE  = install -m 644 -p
INSTALL_PROGRAM = install -m 755 -p
INSTALL_DIR   = cp -f -R
QINSTALL      = /usr/bin/qmake-qt5 -install qinstall
QINSTALL_PROGRAM = /usr/bin/qmake-qt5 -install qinstall -exe
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
TAR           = tar -cf
COMPRESS      = gzip -9f
DISTNAME      = raw_data_viewer1.0.0
DISTDIR = /home/xinzhan/test/mpd_baseline_evaluation/obj/raw_data_viewer1.0.0
LINK          = g++
LFLAGS        = -Wl,-O1
LIBS          = $(SUBLIBS) -L${CODA}/Linux-x86_64/lib -levio /usr/lib64/libQt5Widgets.so /usr/lib64/libQt5Gui.so /usr/lib64/libQt5Core.so -lGL -lpthread   
AR            = ar cqs
RANLIB        = 
SED           = sed
STRIP         = strip

####### Output directory

OBJECTS_DIR   = obj/

####### Files

SOURCES       = src/EvioFileReader.cpp \
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
		src/SRSRawEventDecoder.cpp moc/moc_Viewer.cpp \
		moc/moc_HistoWidget.cpp
OBJECTS       = obj/EvioFileReader.o \
		obj/EventParser.o \
		obj/MPDVMERawEventDecoder.o \
		obj/MPDSSPRawEventDecoder.o \
		obj/AbstractRawDecoder.o \
		obj/MPDDataStruct.o \
		obj/main.o \
		obj/Viewer.o \
		obj/Analyzer.o \
		obj/HistoItem.o \
		obj/HistoView.o \
		obj/HistoWidget.o \
		obj/GEMReplay.o \
		obj/APVStripMapping.o \
		obj/Globals.o \
		obj/SRSRawEventDecoder.o \
		obj/moc_Viewer.o \
		obj/moc_HistoWidget.o
DIST          = /../lib64/qt5/mkspecs/features/spec_pre.prf \
		/usr/lib64/qt5/mkspecs/common/unix.conf \
		/usr/lib64/qt5/mkspecs/common/linux.conf \
		/usr/lib64/qt5/mkspecs/common/sanitize.conf \
		/usr/lib64/qt5/mkspecs/common/gcc-base.conf \
		/usr/lib64/qt5/mkspecs/common/gcc-base-unix.conf \
		/usr/lib64/qt5/mkspecs/common/g++-base.conf \
		/usr/lib64/qt5/mkspecs/common/g++-unix.conf \
		/../lib64/qt5/mkspecs/qconfig.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_accessibility_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_bootstrap_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_concurrent.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_concurrent_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_core.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_core_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_dbus.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_dbus_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_devicediscovery_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_edid_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_egl_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_eglfs_kms_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_eglfsdeviceintegration_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_eventdispatcher_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_fb_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_fontdatabase_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_glx_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_gui.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_gui_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_input_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_kms_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_linuxaccessibility_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_network.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_network_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_opengl.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_opengl_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_openglextensions.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_openglextensions_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_platformcompositor_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_printsupport.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_printsupport_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_service_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_sql.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_sql_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_testlib.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_testlib_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_theme_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_widgets.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_widgets_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_xcb_qpa_lib_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_xkbcommon_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_xml.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_xml_private.pri \
		/../lib64/qt5/mkspecs/features/qt_functions.prf \
		/../lib64/qt5/mkspecs/features/qt_config.prf \
		/../lib64/qt5/mkspecs/linux-g++/qmake.conf \
		/../lib64/qt5/mkspecs/features/spec_post.prf \
		.qmake.stash \
		/../lib64/qt5/mkspecs/features/exclusive_builds.prf \
		/../lib64/qt5/mkspecs/features/toolchain.prf \
		/../lib64/qt5/mkspecs/features/default_pre.prf \
		/../lib64/qt5/mkspecs/features/resolve_config.prf \
		/../lib64/qt5/mkspecs/features/default_post.prf \
		/../lib64/qt5/mkspecs/features/qt.prf \
		/../lib64/qt5/mkspecs/features/resources_functions.prf \
		/../lib64/qt5/mkspecs/features/resources.prf \
		/../lib64/qt5/mkspecs/features/moc.prf \
		/../lib64/qt5/mkspecs/features/unix/opengl.prf \
		/../lib64/qt5/mkspecs/features/uic.prf \
		/../lib64/qt5/mkspecs/features/unix/thread.prf \
		/../lib64/qt5/mkspecs/features/warn_on.prf \
		/../lib64/qt5/mkspecs/features/qmake_use.prf \
		/../lib64/qt5/mkspecs/features/file_copies.prf \
		/../lib64/qt5/mkspecs/features/testcase_targets.prf \
		/../lib64/qt5/mkspecs/features/exceptions.prf \
		/../lib64/qt5/mkspecs/features/yacc.prf \
		/../lib64/qt5/mkspecs/features/lex.prf \
		decoder.pro include/EvioFileReader.h \
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
		include/SRSRawEventDecoder.h src/EvioFileReader.cpp \
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
		src/SRSRawEventDecoder.cpp
QMAKE_TARGET  = raw_data_viewer
DESTDIR       = 
TARGET        = raw_data_viewer


first: all
####### Build rules

raw_data_viewer:  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: decoder.pro /../lib64/qt5/mkspecs/linux-g++/qmake.conf /../lib64/qt5/mkspecs/features/spec_pre.prf \
		/usr/lib64/qt5/mkspecs/common/unix.conf \
		/usr/lib64/qt5/mkspecs/common/linux.conf \
		/usr/lib64/qt5/mkspecs/common/sanitize.conf \
		/usr/lib64/qt5/mkspecs/common/gcc-base.conf \
		/usr/lib64/qt5/mkspecs/common/gcc-base-unix.conf \
		/usr/lib64/qt5/mkspecs/common/g++-base.conf \
		/usr/lib64/qt5/mkspecs/common/g++-unix.conf \
		/../lib64/qt5/mkspecs/qconfig.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_accessibility_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_bootstrap_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_concurrent.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_concurrent_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_core.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_core_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_dbus.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_dbus_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_devicediscovery_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_edid_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_egl_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_eglfs_kms_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_eglfsdeviceintegration_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_eventdispatcher_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_fb_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_fontdatabase_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_glx_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_gui.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_gui_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_input_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_kms_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_linuxaccessibility_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_network.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_network_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_opengl.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_opengl_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_openglextensions.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_openglextensions_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_platformcompositor_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_printsupport.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_printsupport_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_service_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_sql.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_sql_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_testlib.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_testlib_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_theme_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_widgets.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_widgets_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_xcb_qpa_lib_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_xkbcommon_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_xml.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_xml_private.pri \
		/../lib64/qt5/mkspecs/features/qt_functions.prf \
		/../lib64/qt5/mkspecs/features/qt_config.prf \
		/../lib64/qt5/mkspecs/linux-g++/qmake.conf \
		/../lib64/qt5/mkspecs/features/spec_post.prf \
		.qmake.stash \
		/../lib64/qt5/mkspecs/features/exclusive_builds.prf \
		/../lib64/qt5/mkspecs/features/toolchain.prf \
		/../lib64/qt5/mkspecs/features/default_pre.prf \
		/../lib64/qt5/mkspecs/features/resolve_config.prf \
		/../lib64/qt5/mkspecs/features/default_post.prf \
		/../lib64/qt5/mkspecs/features/qt.prf \
		/../lib64/qt5/mkspecs/features/resources_functions.prf \
		/../lib64/qt5/mkspecs/features/resources.prf \
		/../lib64/qt5/mkspecs/features/moc.prf \
		/../lib64/qt5/mkspecs/features/unix/opengl.prf \
		/../lib64/qt5/mkspecs/features/uic.prf \
		/../lib64/qt5/mkspecs/features/unix/thread.prf \
		/../lib64/qt5/mkspecs/features/warn_on.prf \
		/../lib64/qt5/mkspecs/features/qmake_use.prf \
		/../lib64/qt5/mkspecs/features/file_copies.prf \
		/../lib64/qt5/mkspecs/features/testcase_targets.prf \
		/../lib64/qt5/mkspecs/features/exceptions.prf \
		/../lib64/qt5/mkspecs/features/yacc.prf \
		/../lib64/qt5/mkspecs/features/lex.prf \
		decoder.pro
	$(QMAKE) -o Makefile decoder.pro
/../lib64/qt5/mkspecs/features/spec_pre.prf:
/usr/lib64/qt5/mkspecs/common/unix.conf:
/usr/lib64/qt5/mkspecs/common/linux.conf:
/usr/lib64/qt5/mkspecs/common/sanitize.conf:
/usr/lib64/qt5/mkspecs/common/gcc-base.conf:
/usr/lib64/qt5/mkspecs/common/gcc-base-unix.conf:
/usr/lib64/qt5/mkspecs/common/g++-base.conf:
/usr/lib64/qt5/mkspecs/common/g++-unix.conf:
/../lib64/qt5/mkspecs/qconfig.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_accessibility_support_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_bootstrap_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_concurrent.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_concurrent_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_core.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_core_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_dbus.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_dbus_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_devicediscovery_support_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_edid_support_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_egl_support_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_eglfs_kms_support_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_eglfsdeviceintegration_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_eventdispatcher_support_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_fb_support_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_fontdatabase_support_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_glx_support_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_gui.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_gui_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_input_support_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_kms_support_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_linuxaccessibility_support_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_network.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_network_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_opengl.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_opengl_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_openglextensions.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_openglextensions_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_platformcompositor_support_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_printsupport.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_printsupport_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_service_support_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_sql.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_sql_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_testlib.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_testlib_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_theme_support_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_widgets.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_widgets_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_xcb_qpa_lib_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_xkbcommon_support_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_xml.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_xml_private.pri:
/../lib64/qt5/mkspecs/features/qt_functions.prf:
/../lib64/qt5/mkspecs/features/qt_config.prf:
/../lib64/qt5/mkspecs/linux-g++/qmake.conf:
/../lib64/qt5/mkspecs/features/spec_post.prf:
.qmake.stash:
/../lib64/qt5/mkspecs/features/exclusive_builds.prf:
/../lib64/qt5/mkspecs/features/toolchain.prf:
/../lib64/qt5/mkspecs/features/default_pre.prf:
/../lib64/qt5/mkspecs/features/resolve_config.prf:
/../lib64/qt5/mkspecs/features/default_post.prf:
/../lib64/qt5/mkspecs/features/qt.prf:
/../lib64/qt5/mkspecs/features/resources_functions.prf:
/../lib64/qt5/mkspecs/features/resources.prf:
/../lib64/qt5/mkspecs/features/moc.prf:
/../lib64/qt5/mkspecs/features/unix/opengl.prf:
/../lib64/qt5/mkspecs/features/uic.prf:
/../lib64/qt5/mkspecs/features/unix/thread.prf:
/../lib64/qt5/mkspecs/features/warn_on.prf:
/../lib64/qt5/mkspecs/features/qmake_use.prf:
/../lib64/qt5/mkspecs/features/file_copies.prf:
/../lib64/qt5/mkspecs/features/testcase_targets.prf:
/../lib64/qt5/mkspecs/features/exceptions.prf:
/../lib64/qt5/mkspecs/features/yacc.prf:
/../lib64/qt5/mkspecs/features/lex.prf:
decoder.pro:
qmake: FORCE
	@$(QMAKE) -o Makefile decoder.pro

qmake_all: FORCE


all: Makefile raw_data_viewer

dist: distdir FORCE
	(cd `dirname $(DISTDIR)` && $(TAR) $(DISTNAME).tar $(DISTNAME) && $(COMPRESS) $(DISTNAME).tar) && $(MOVE) `dirname $(DISTDIR)`/$(DISTNAME).tar.gz . && $(DEL_FILE) -r $(DISTDIR)

distdir: FORCE
	@test -d $(DISTDIR) || mkdir -p $(DISTDIR)
	$(COPY_FILE) --parents $(DIST) $(DISTDIR)/
	$(COPY_FILE) --parents /../lib64/qt5/mkspecs/features/data/dummy.cpp $(DISTDIR)/
	$(COPY_FILE) --parents include/EvioFileReader.h include/EventParser.h include/GeneralEvioStruct.h include/MPDVMERawEventDecoder.h include/MPDSSPRawEventDecoder.h include/RolStruct.h include/MPDDataStruct.h include/AbstractRawDecoder.h include/sspApvdec.h include/Viewer.h include/Analyzer.h include/HistoItem.h include/HistoView.h include/HistoWidget.h include/GEMReplay.h include/APVStripMapping.h include/GEMStruct.h include/ConfigSetup.h include/Globals.h include/SRSRawEventDecoder.h $(DISTDIR)/
	$(COPY_FILE) --parents src/EvioFileReader.cpp src/EventParser.cpp src/MPDVMERawEventDecoder.cpp src/MPDSSPRawEventDecoder.cpp src/AbstractRawDecoder.cpp src/MPDDataStruct.cpp src/main.cpp src/Viewer.cpp src/Analyzer.cpp src/HistoItem.cpp src/HistoView.cpp src/HistoWidget.cpp src/GEMReplay.cpp src/APVStripMapping.cpp src/Globals.cpp src/SRSRawEventDecoder.cpp $(DISTDIR)/


clean: compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


distclean: clean 
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) .qmake.stash
	-$(DEL_FILE) Makefile


####### Sub-libraries

mocclean: compiler_moc_header_clean compiler_moc_objc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_objc_header_make_all compiler_moc_source_make_all

check: first

benchmark: first

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_moc_predefs_make_all: moc/moc_predefs.h
compiler_moc_predefs_clean:
	-$(DEL_FILE) moc/moc_predefs.h
moc/moc_predefs.h: /../lib64/qt5/mkspecs/features/data/dummy.cpp
	g++ -pipe -std=c++17 -O2 -std=gnu++11 -dM -E -o moc/moc_predefs.h /../lib64/qt5/mkspecs/features/data/dummy.cpp

compiler_moc_header_make_all: moc/moc_Viewer.cpp moc/moc_HistoWidget.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc/moc_Viewer.cpp moc/moc_HistoWidget.cpp
moc/moc_Viewer.cpp: include/Viewer.h \
		include/Analyzer.h \
		include/EvioFileReader.h \
		include/EventParser.h \
		include/GeneralEvioStruct.h \
		include/AbstractRawDecoder.h \
		include/MPDDataStruct.h \
		include/MPDVMERawEventDecoder.h \
		include/RolStruct.h \
		include/MPDSSPRawEventDecoder.h \
		include/SRSRawEventDecoder.h \
		include/GEMReplay.h \
		include/APVStripMapping.h \
		include/GEMStruct.h \
		include/HistoWidget.h \
		include/HistoView.h \
		include/HistoItem.h \
		include/ConfigSetup.h \
		moc/moc_predefs.h \
		/../lib64/qt5/bin/moc
	/../lib64/qt5/bin/moc $(DEFINES) --include /home/xinzhan/test/mpd_baseline_evaluation/moc/moc_predefs.h -I/../lib64/qt5/mkspecs/linux-g++ -I/home/xinzhan/test/mpd_baseline_evaluation -I/home/xinzhan/test/mpd_baseline_evaluation -I/home/xinzhan/test/mpd_baseline_evaluation/include -I'/home/xinzhan/test/mpd_baseline_evaluation/${CODA}/common/include' -I/usr/include/qt5 -I/usr/include/qt5/QtWidgets -I/usr/include/qt5/QtGui -I/usr/include/qt5/QtCore -I/usr/include/c++/4.8.5 -I/usr/include/c++/4.8.5/x86_64-redhat-linux -I/usr/include/c++/4.8.5/backward -I/usr/lib/gcc/x86_64-redhat-linux/4.8.5/include -I/usr/local/include -I/usr/include include/Viewer.h -o moc/moc_Viewer.cpp

moc/moc_HistoWidget.cpp: include/HistoWidget.h \
		include/HistoView.h \
		include/HistoItem.h \
		include/ConfigSetup.h \
		include/MPDDataStruct.h \
		moc/moc_predefs.h \
		/../lib64/qt5/bin/moc
	/../lib64/qt5/bin/moc $(DEFINES) --include /home/xinzhan/test/mpd_baseline_evaluation/moc/moc_predefs.h -I/../lib64/qt5/mkspecs/linux-g++ -I/home/xinzhan/test/mpd_baseline_evaluation -I/home/xinzhan/test/mpd_baseline_evaluation -I/home/xinzhan/test/mpd_baseline_evaluation/include -I'/home/xinzhan/test/mpd_baseline_evaluation/${CODA}/common/include' -I/usr/include/qt5 -I/usr/include/qt5/QtWidgets -I/usr/include/qt5/QtGui -I/usr/include/qt5/QtCore -I/usr/include/c++/4.8.5 -I/usr/include/c++/4.8.5/x86_64-redhat-linux -I/usr/include/c++/4.8.5/backward -I/usr/lib/gcc/x86_64-redhat-linux/4.8.5/include -I/usr/local/include -I/usr/include include/HistoWidget.h -o moc/moc_HistoWidget.cpp

compiler_moc_objc_header_make_all:
compiler_moc_objc_header_clean:
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_predefs_clean compiler_moc_header_clean 

####### Compile

obj/EvioFileReader.o: src/EvioFileReader.cpp include/EvioFileReader.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/EvioFileReader.o src/EvioFileReader.cpp

obj/EventParser.o: src/EventParser.cpp include/EventParser.h \
		include/GeneralEvioStruct.h \
		include/AbstractRawDecoder.h \
		include/MPDDataStruct.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/EventParser.o src/EventParser.cpp

obj/MPDVMERawEventDecoder.o: src/MPDVMERawEventDecoder.cpp include/MPDVMERawEventDecoder.h \
		include/RolStruct.h \
		include/MPDDataStruct.h \
		include/AbstractRawDecoder.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/MPDVMERawEventDecoder.o src/MPDVMERawEventDecoder.cpp

obj/MPDSSPRawEventDecoder.o: src/MPDSSPRawEventDecoder.cpp include/MPDSSPRawEventDecoder.h \
		include/AbstractRawDecoder.h \
		include/MPDDataStruct.h \
		include/RolStruct.h \
		include/sspApvdec.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/MPDSSPRawEventDecoder.o src/MPDSSPRawEventDecoder.cpp

obj/AbstractRawDecoder.o: src/AbstractRawDecoder.cpp include/AbstractRawDecoder.h \
		include/MPDDataStruct.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/AbstractRawDecoder.o src/AbstractRawDecoder.cpp

obj/MPDDataStruct.o: src/MPDDataStruct.cpp include/MPDDataStruct.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/MPDDataStruct.o src/MPDDataStruct.cpp

obj/main.o: src/main.cpp include/Viewer.h \
		include/Analyzer.h \
		include/EvioFileReader.h \
		include/EventParser.h \
		include/GeneralEvioStruct.h \
		include/AbstractRawDecoder.h \
		include/MPDDataStruct.h \
		include/MPDVMERawEventDecoder.h \
		include/RolStruct.h \
		include/MPDSSPRawEventDecoder.h \
		include/SRSRawEventDecoder.h \
		include/GEMReplay.h \
		include/APVStripMapping.h \
		include/GEMStruct.h \
		include/HistoWidget.h \
		include/HistoView.h \
		include/HistoItem.h \
		include/ConfigSetup.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/main.o src/main.cpp

obj/Viewer.o: src/Viewer.cpp include/Viewer.h \
		include/Analyzer.h \
		include/EvioFileReader.h \
		include/EventParser.h \
		include/GeneralEvioStruct.h \
		include/AbstractRawDecoder.h \
		include/MPDDataStruct.h \
		include/MPDVMERawEventDecoder.h \
		include/RolStruct.h \
		include/MPDSSPRawEventDecoder.h \
		include/SRSRawEventDecoder.h \
		include/GEMReplay.h \
		include/APVStripMapping.h \
		include/GEMStruct.h \
		include/HistoWidget.h \
		include/HistoView.h \
		include/HistoItem.h \
		include/ConfigSetup.h \
		include/Globals.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/Viewer.o src/Viewer.cpp

obj/Analyzer.o: src/Analyzer.cpp include/Analyzer.h \
		include/EvioFileReader.h \
		include/EventParser.h \
		include/GeneralEvioStruct.h \
		include/AbstractRawDecoder.h \
		include/MPDDataStruct.h \
		include/MPDVMERawEventDecoder.h \
		include/RolStruct.h \
		include/MPDSSPRawEventDecoder.h \
		include/SRSRawEventDecoder.h \
		include/ConfigSetup.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/Analyzer.o src/Analyzer.cpp

obj/HistoItem.o: src/HistoItem.cpp include/HistoItem.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/HistoItem.o src/HistoItem.cpp

obj/HistoView.o: src/HistoView.cpp include/HistoView.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/HistoView.o src/HistoView.cpp

obj/HistoWidget.o: src/HistoWidget.cpp include/HistoWidget.h \
		include/HistoView.h \
		include/HistoItem.h \
		include/ConfigSetup.h \
		include/MPDDataStruct.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/HistoWidget.o src/HistoWidget.cpp

obj/GEMReplay.o: src/GEMReplay.cpp include/GEMReplay.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/GEMReplay.o src/GEMReplay.cpp

obj/APVStripMapping.o: src/APVStripMapping.cpp include/APVStripMapping.h \
		include/GEMStruct.h \
		include/MPDDataStruct.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/APVStripMapping.o src/APVStripMapping.cpp

obj/Globals.o: src/Globals.cpp include/Globals.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/Globals.o src/Globals.cpp

obj/SRSRawEventDecoder.o: src/SRSRawEventDecoder.cpp include/SRSRawEventDecoder.h \
		include/MPDDataStruct.h \
		include/AbstractRawDecoder.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/SRSRawEventDecoder.o src/SRSRawEventDecoder.cpp

obj/moc_Viewer.o: moc/moc_Viewer.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_Viewer.o moc/moc_Viewer.cpp

obj/moc_HistoWidget.o: moc/moc_HistoWidget.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_HistoWidget.o moc/moc_HistoWidget.cpp

####### Install

install:  FORCE

uninstall:  FORCE

FORCE:

