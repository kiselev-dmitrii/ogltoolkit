TEMPLATE = app
CONFIG += console
CONFIG -= qt

INCLUDEPATH = ../..

SOURCES += main.cpp \
           ../../lib/Framework/TreeNode.cpp \
           ../../lib/Utils/StringUtils.cpp

HEADERS += \
           ../../lib/Framework/TreeNode.h \
           ../../lib/Utils/StringUtils.h \
           ../../lib/Utils/Debug.h \
