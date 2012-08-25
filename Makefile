#############################################################################
# Makefile for building: ElfHunter
# Generated by qmake (2.01a) (Qt 4.7.0) on: Sat Aug 25 14:46:28 2012
# Project:  ElfHunter.pro
# Template: app
# Command: /usr/bin/qmake -o Makefile ElfHunter.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -m64 -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -m64 -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/lib64/qt/mkspecs/linux-g++-64 -I. -I/usr/lib64/qt/include/QtCore -I/usr/lib64/qt/include/QtGui -I/usr/lib64/qt/include -I. -I.
LINK          = g++
LFLAGS        = -m64 -Wl,-O1 -Wl,-rpath,/usr/lib64/qt/lib
LIBS          = $(SUBLIBS)  -L/usr/lib64/qt/lib -lkdecore -lQtGui -L/usr/lib64/qt/lib -L/usr/X11R6/lib64 -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = elfhunter.cpp \
		ElfHunterHexWidget.cpp \
		ElfHunterMainWidget.cpp \
		ElfHunterSideWidget.cpp \
		AboutWidget.cpp \
		ElfGenericHeader.cpp \
		ElfMultiHeader.cpp \
		ElfELFHeaderWidget.cpp \
		ElfProgHeaderWidget.cpp \
		ElfSectionHeaderWidget.cpp \
		ElfStringTable.cpp moc_ElfHunterHexWidget.cpp \
		moc_ElfHunterMainWidget.cpp \
		moc_ElfHunterSideWidget.cpp \
		moc_ElfGenericHeader.cpp \
		moc_ElfMultiHeader.cpp \
		moc_ElfELFHeaderWidget.cpp \
		moc_ElfProgHeaderWidget.cpp \
		moc_ElfSectionHeaderWidget.cpp \
		moc_ElfStringTable.cpp
OBJECTS       = elfhunter.o \
		ElfHunterHexWidget.o \
		ElfHunterMainWidget.o \
		ElfHunterSideWidget.o \
		AboutWidget.o \
		ElfGenericHeader.o \
		ElfMultiHeader.o \
		ElfELFHeaderWidget.o \
		ElfProgHeaderWidget.o \
		ElfSectionHeaderWidget.o \
		ElfStringTable.o \
		moc_ElfHunterHexWidget.o \
		moc_ElfHunterMainWidget.o \
		moc_ElfHunterSideWidget.o \
		moc_ElfGenericHeader.o \
		moc_ElfMultiHeader.o \
		moc_ElfELFHeaderWidget.o \
		moc_ElfProgHeaderWidget.o \
		moc_ElfSectionHeaderWidget.o \
		moc_ElfStringTable.o
DIST          = /usr/lib64/qt/mkspecs/common/g++.conf \
		/usr/lib64/qt/mkspecs/common/unix.conf \
		/usr/lib64/qt/mkspecs/common/linux.conf \
		/usr/lib64/qt/mkspecs/qconfig.pri \
		/usr/lib64/qt/mkspecs/modules/qt_phonon.pri \
		/usr/lib64/qt/mkspecs/modules/qt_webkit_version.pri \
		/usr/lib64/qt/mkspecs/features/qt_functions.prf \
		/usr/lib64/qt/mkspecs/features/qt_config.prf \
		/usr/lib64/qt/mkspecs/features/exclusive_builds.prf \
		/usr/lib64/qt/mkspecs/features/default_pre.prf \
		/usr/lib64/qt/mkspecs/features/release.prf \
		/usr/lib64/qt/mkspecs/features/default_post.prf \
		/usr/lib64/qt/mkspecs/features/warn_on.prf \
		/usr/lib64/qt/mkspecs/features/qt.prf \
		/usr/lib64/qt/mkspecs/features/unix/thread.prf \
		/usr/lib64/qt/mkspecs/features/moc.prf \
		/usr/lib64/qt/mkspecs/features/resources.prf \
		/usr/lib64/qt/mkspecs/features/uic.prf \
		/usr/lib64/qt/mkspecs/features/yacc.prf \
		/usr/lib64/qt/mkspecs/features/lex.prf \
		/usr/lib64/qt/mkspecs/features/include_source_dir.prf \
		ElfHunter.pro
QMAKE_TARGET  = ElfHunter
DESTDIR       = 
TARGET        = ElfHunter

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: ElfHunter.pro  /usr/lib64/qt/mkspecs/linux-g++-64/qmake.conf /usr/lib64/qt/mkspecs/common/g++.conf \
		/usr/lib64/qt/mkspecs/common/unix.conf \
		/usr/lib64/qt/mkspecs/common/linux.conf \
		/usr/lib64/qt/mkspecs/qconfig.pri \
		/usr/lib64/qt/mkspecs/modules/qt_phonon.pri \
		/usr/lib64/qt/mkspecs/modules/qt_webkit_version.pri \
		/usr/lib64/qt/mkspecs/features/qt_functions.prf \
		/usr/lib64/qt/mkspecs/features/qt_config.prf \
		/usr/lib64/qt/mkspecs/features/exclusive_builds.prf \
		/usr/lib64/qt/mkspecs/features/default_pre.prf \
		/usr/lib64/qt/mkspecs/features/release.prf \
		/usr/lib64/qt/mkspecs/features/default_post.prf \
		/usr/lib64/qt/mkspecs/features/warn_on.prf \
		/usr/lib64/qt/mkspecs/features/qt.prf \
		/usr/lib64/qt/mkspecs/features/unix/thread.prf \
		/usr/lib64/qt/mkspecs/features/moc.prf \
		/usr/lib64/qt/mkspecs/features/resources.prf \
		/usr/lib64/qt/mkspecs/features/uic.prf \
		/usr/lib64/qt/mkspecs/features/yacc.prf \
		/usr/lib64/qt/mkspecs/features/lex.prf \
		/usr/lib64/qt/mkspecs/features/include_source_dir.prf \
		/usr/lib64/qt/lib/libQtGui.prl \
		/usr/lib64/qt/lib/libQtCore.prl
	$(QMAKE) -o Makefile ElfHunter.pro
/usr/lib64/qt/mkspecs/common/g++.conf:
/usr/lib64/qt/mkspecs/common/unix.conf:
/usr/lib64/qt/mkspecs/common/linux.conf:
/usr/lib64/qt/mkspecs/qconfig.pri:
/usr/lib64/qt/mkspecs/modules/qt_phonon.pri:
/usr/lib64/qt/mkspecs/modules/qt_webkit_version.pri:
/usr/lib64/qt/mkspecs/features/qt_functions.prf:
/usr/lib64/qt/mkspecs/features/qt_config.prf:
/usr/lib64/qt/mkspecs/features/exclusive_builds.prf:
/usr/lib64/qt/mkspecs/features/default_pre.prf:
/usr/lib64/qt/mkspecs/features/release.prf:
/usr/lib64/qt/mkspecs/features/default_post.prf:
/usr/lib64/qt/mkspecs/features/warn_on.prf:
/usr/lib64/qt/mkspecs/features/qt.prf:
/usr/lib64/qt/mkspecs/features/unix/thread.prf:
/usr/lib64/qt/mkspecs/features/moc.prf:
/usr/lib64/qt/mkspecs/features/resources.prf:
/usr/lib64/qt/mkspecs/features/uic.prf:
/usr/lib64/qt/mkspecs/features/yacc.prf:
/usr/lib64/qt/mkspecs/features/lex.prf:
/usr/lib64/qt/mkspecs/features/include_source_dir.prf:
/usr/lib64/qt/lib/libQtGui.prl:
/usr/lib64/qt/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -o Makefile ElfHunter.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/ElfHunter1.0.0 || $(MKDIR) .tmp/ElfHunter1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/ElfHunter1.0.0/ && $(COPY_FILE) --parents ElfHunterHexWidget.h ElfHunterMainWidget.h ElfHunterSideWidget.h AboutWidget.h ElfGenericHeader.h ElfMultiHeader.h ElfELFHeaderWidget.h ElfProgHeaderWidget.h ElfSectionHeaderWidget.h ElfStringTable.h .tmp/ElfHunter1.0.0/ && $(COPY_FILE) --parents elfhunter.cpp ElfHunterHexWidget.cpp ElfHunterMainWidget.cpp ElfHunterSideWidget.cpp AboutWidget.cpp ElfGenericHeader.cpp ElfMultiHeader.cpp ElfELFHeaderWidget.cpp ElfProgHeaderWidget.cpp ElfSectionHeaderWidget.cpp ElfStringTable.cpp .tmp/ElfHunter1.0.0/ && (cd `dirname .tmp/ElfHunter1.0.0` && $(TAR) ElfHunter1.0.0.tar ElfHunter1.0.0 && $(COMPRESS) ElfHunter1.0.0.tar) && $(MOVE) `dirname .tmp/ElfHunter1.0.0`/ElfHunter1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/ElfHunter1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_ElfHunterHexWidget.cpp moc_ElfHunterMainWidget.cpp moc_ElfHunterSideWidget.cpp moc_ElfGenericHeader.cpp moc_ElfMultiHeader.cpp moc_ElfELFHeaderWidget.cpp moc_ElfProgHeaderWidget.cpp moc_ElfSectionHeaderWidget.cpp moc_ElfStringTable.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_ElfHunterHexWidget.cpp moc_ElfHunterMainWidget.cpp moc_ElfHunterSideWidget.cpp moc_ElfGenericHeader.cpp moc_ElfMultiHeader.cpp moc_ElfELFHeaderWidget.cpp moc_ElfProgHeaderWidget.cpp moc_ElfSectionHeaderWidget.cpp moc_ElfStringTable.cpp
moc_ElfHunterHexWidget.cpp: ElfHunterHexWidget.h
	/usr/lib64/qt/bin/moc $(DEFINES) $(INCPATH) ElfHunterHexWidget.h -o moc_ElfHunterHexWidget.cpp

moc_ElfHunterMainWidget.cpp: ElfHunterSideWidget.h \
		ElfProgHeaderWidget.h \
		ElfGenericHeader.h \
		ElfSectionHeaderWidget.h \
		ElfStringTable.h \
		ElfHunterHexWidget.h \
		AboutWidget.h \
		ElfHunterMainWidget.h
	/usr/lib64/qt/bin/moc $(DEFINES) $(INCPATH) ElfHunterMainWidget.h -o moc_ElfHunterMainWidget.cpp

moc_ElfHunterSideWidget.cpp: ElfProgHeaderWidget.h \
		ElfGenericHeader.h \
		ElfSectionHeaderWidget.h \
		ElfStringTable.h \
		ElfHunterSideWidget.h
	/usr/lib64/qt/bin/moc $(DEFINES) $(INCPATH) ElfHunterSideWidget.h -o moc_ElfHunterSideWidget.cpp

moc_ElfGenericHeader.cpp: ElfGenericHeader.h
	/usr/lib64/qt/bin/moc $(DEFINES) $(INCPATH) ElfGenericHeader.h -o moc_ElfGenericHeader.cpp

moc_ElfMultiHeader.cpp: ElfGenericHeader.h \
		ElfMultiHeader.h
	/usr/lib64/qt/bin/moc $(DEFINES) $(INCPATH) ElfMultiHeader.h -o moc_ElfMultiHeader.cpp

moc_ElfELFHeaderWidget.cpp: ElfELFHeaderWidget.h
	/usr/lib64/qt/bin/moc $(DEFINES) $(INCPATH) ElfELFHeaderWidget.h -o moc_ElfELFHeaderWidget.cpp

moc_ElfProgHeaderWidget.cpp: ElfGenericHeader.h \
		ElfProgHeaderWidget.h
	/usr/lib64/qt/bin/moc $(DEFINES) $(INCPATH) ElfProgHeaderWidget.h -o moc_ElfProgHeaderWidget.cpp

moc_ElfSectionHeaderWidget.cpp: ElfGenericHeader.h \
		ElfSectionHeaderWidget.h
	/usr/lib64/qt/bin/moc $(DEFINES) $(INCPATH) ElfSectionHeaderWidget.h -o moc_ElfSectionHeaderWidget.cpp

moc_ElfStringTable.cpp: ElfGenericHeader.h \
		ElfStringTable.h
	/usr/lib64/qt/bin/moc $(DEFINES) $(INCPATH) ElfStringTable.h -o moc_ElfStringTable.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
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
compiler_clean: compiler_moc_header_clean 

####### Compile

elfhunter.o: elfhunter.cpp ElfHunterMainWidget.h \
		ElfHunterSideWidget.h \
		ElfProgHeaderWidget.h \
		ElfGenericHeader.h \
		ElfSectionHeaderWidget.h \
		ElfStringTable.h \
		ElfHunterHexWidget.h \
		AboutWidget.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o elfhunter.o elfhunter.cpp

ElfHunterHexWidget.o: ElfHunterHexWidget.cpp ElfHunterHexWidget.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ElfHunterHexWidget.o ElfHunterHexWidget.cpp

ElfHunterMainWidget.o: ElfHunterMainWidget.cpp ElfHunterMainWidget.h \
		ElfHunterSideWidget.h \
		ElfProgHeaderWidget.h \
		ElfGenericHeader.h \
		ElfSectionHeaderWidget.h \
		ElfStringTable.h \
		ElfHunterHexWidget.h \
		AboutWidget.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ElfHunterMainWidget.o ElfHunterMainWidget.cpp

ElfHunterSideWidget.o: ElfHunterSideWidget.cpp ElfHunterSideWidget.h \
		ElfProgHeaderWidget.h \
		ElfGenericHeader.h \
		ElfSectionHeaderWidget.h \
		ElfStringTable.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ElfHunterSideWidget.o ElfHunterSideWidget.cpp

AboutWidget.o: AboutWidget.cpp AboutWidget.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o AboutWidget.o AboutWidget.cpp

ElfGenericHeader.o: ElfGenericHeader.cpp ElfGenericHeader.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ElfGenericHeader.o ElfGenericHeader.cpp

ElfMultiHeader.o: ElfMultiHeader.cpp ElfMultiHeader.h \
		ElfGenericHeader.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ElfMultiHeader.o ElfMultiHeader.cpp

ElfELFHeaderWidget.o: ElfELFHeaderWidget.cpp ElfELFHeaderWidget.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ElfELFHeaderWidget.o ElfELFHeaderWidget.cpp

ElfProgHeaderWidget.o: ElfProgHeaderWidget.cpp ElfProgHeaderWidget.h \
		ElfGenericHeader.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ElfProgHeaderWidget.o ElfProgHeaderWidget.cpp

ElfSectionHeaderWidget.o: ElfSectionHeaderWidget.cpp ElfSectionHeaderWidget.h \
		ElfGenericHeader.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ElfSectionHeaderWidget.o ElfSectionHeaderWidget.cpp

ElfStringTable.o: ElfStringTable.cpp ElfStringTable.h \
		ElfGenericHeader.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ElfStringTable.o ElfStringTable.cpp

moc_ElfHunterHexWidget.o: moc_ElfHunterHexWidget.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_ElfHunterHexWidget.o moc_ElfHunterHexWidget.cpp

moc_ElfHunterMainWidget.o: moc_ElfHunterMainWidget.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_ElfHunterMainWidget.o moc_ElfHunterMainWidget.cpp

moc_ElfHunterSideWidget.o: moc_ElfHunterSideWidget.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_ElfHunterSideWidget.o moc_ElfHunterSideWidget.cpp

moc_ElfGenericHeader.o: moc_ElfGenericHeader.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_ElfGenericHeader.o moc_ElfGenericHeader.cpp

moc_ElfMultiHeader.o: moc_ElfMultiHeader.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_ElfMultiHeader.o moc_ElfMultiHeader.cpp

moc_ElfELFHeaderWidget.o: moc_ElfELFHeaderWidget.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_ElfELFHeaderWidget.o moc_ElfELFHeaderWidget.cpp

moc_ElfProgHeaderWidget.o: moc_ElfProgHeaderWidget.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_ElfProgHeaderWidget.o moc_ElfProgHeaderWidget.cpp

moc_ElfSectionHeaderWidget.o: moc_ElfSectionHeaderWidget.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_ElfSectionHeaderWidget.o moc_ElfSectionHeaderWidget.cpp

moc_ElfStringTable.o: moc_ElfStringTable.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_ElfStringTable.o moc_ElfStringTable.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

