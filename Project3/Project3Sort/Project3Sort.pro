TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    sortingcompetition.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    sortingcompetition.h

