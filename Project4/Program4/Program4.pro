TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ../node.cpp \
    node.cpp \
    linkedlist.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    ../node.h \
    node.h \
    linkedlist.h

