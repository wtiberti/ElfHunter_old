###############################################
#        ElfHunter Project file               #
# Author: Walter Tiberti <wtuniv@gmail.com>   #
#                                             #
# This file is needed makefile re-generation  #
###############################################
TEMPLATE = app
TARGET =
DEPENDPATH += .
INCLUDEPATH += .

# Source code files
HEADERS += ElfHunterHexWidget.h \
           ElfHunterMainWidget.h \
           ElfHunterSideWidget.h \
           AboutWidget.h \
           ElfGenericHeader.h \
           ElfMultiHeader.h \
           ElfELFHeaderWidget.h \
           ElfProgHeaderWidget.h \
           ElfSectionHeaderWidget.h \
           ElfStringTable.h
SOURCES += elfhunter.cpp \
           ElfHunterHexWidget.cpp \
           ElfHunterMainWidget.cpp \
           ElfHunterSideWidget.cpp \
           AboutWidget.cpp \
           ElfGenericHeader.cpp \
           ElfMultiHeader.cpp \
           ElfELFHeaderWidget.cpp \
           ElfProgHeaderWidget.cpp \
           ElfSectionHeaderWidget.cpp \
           ElfStringTable.cpp

# KHE Interface need this
LIBS += -lkdecore
