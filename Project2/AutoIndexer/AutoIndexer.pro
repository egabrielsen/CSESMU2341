TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    page.cpp \
    word.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    page.h \
    word.h

