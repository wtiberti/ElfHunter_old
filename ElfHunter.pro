###################################################
#        ElfHunter Project file                   #
# Author: Walter Tiberti <wtuniv@gmail.com>       #
#                                                 #
# This file is needed for makefile re-generation  #
###################################################
TEMPLATE = app
TARGET =
DEPENDPATH += .

# TODO using environment variables to detect path
INCLUDEPATH += . /usr/include/okteta1

# Source code files
HEADERS += ElfAuxTypes.h \
           SelectionInfo.h \
           ElfHunterWindow.h \
           ElfHunterHexWidget.h \
           ElfHunterMainWidget.h \
           ElfHunterSideWidget.h \
           AboutWidget.h \
           ElfGenericHeader.h \
           ElfMultiHeader.h \
           ElfELFHeaderWidget.h \
           ElfProgHeaderWidget.h \
           ElfSectionHeaderWidget.h \
           ElfStringTable.h \
           ElfSymTable.h \
           ElfHunterRelTable.h \
           ElfHunterExec.h \
           ElfHunterConfStruct.h
SOURCES += elfhunter.cpp \
           ElfHunterWindow.cpp \
           ElfHunterHexWidget.cpp \
           ElfHunterMainWidget.cpp \
           ElfHunterSideWidget.cpp \
           AboutWidget.cpp \
           ElfGenericHeader.cpp \
           ElfMultiHeader.cpp \
           ElfELFHeaderWidget.cpp \
           ElfProgHeaderWidget.cpp \
           ElfSectionHeaderWidget.cpp \
           ElfStringTable.cpp \
           ElfSymTable.cpp \
           ElfHunterRelTable.cpp \
           ElfHunterExec.cpp

# Okteta widget need these
LIBS += -lokteta1core -lokteta1gui -lQtXml

# Resources (icons)
RESOURCES += ElfHunter.qrc
