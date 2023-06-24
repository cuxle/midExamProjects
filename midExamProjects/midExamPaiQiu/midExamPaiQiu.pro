#-------------------------------------------------
#
# Project created by QtCreator 2021-09-22T17:33:59
#
#-------------------------------------------------

QT       += core gui multimedia network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = midExamPaiQiu
TEMPLATE = app

SHARED_PATH = ../common

include($$SHARED_PATH/common.pri)

DEFINES += PAIQIU

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    algorithm/algorithmloadbase.cpp \
    algorithm/volleyballinterface.cpp \
    algorithm/volleyballworker.cpp \
    formfuncchoose.cpp \
    videowidget.cpp

HEADERS += \
    algorithm/algorithmloadbase.h \
    algorithm/volleyballinterface.h \
    algorithm/volleyballworker.h \
    formfuncchoose.h \
    videowidget.h

FORMS += \
    formfuncchoose.ui

RESOURCES += \
    res.qrc

INCLUDEPATH += "D:\ProgramData\DahengImaging\GalaxySDK\Samples\C++SDK\inc"

unix|win32: LIBS += -LD:/ProgramData/DahengImaging/GalaxySDK/Samples/C++SDK/lib/x64/ -lGxIAPICPPEx

INCLUDEPATH += D:/ProgramData/DahengImaging/GalaxySDK/Samples/C++SDK/lib/x64
DEPENDPATH += D:/ProgramData/DahengImaging/GalaxySDK/Samples/C++SDK/lib/x64

INCLUDEPATH += $$PWD/../libs/videoWrite/FFmpeg/include
INCLUDEPATH += $$PWD/../libs/videoWrite

LIBS += -L$$PWD/../libs/videoWrite/FFmpeg/lib -lavcodec
LIBS += -L$$PWD/../libs/videoWrite/FFmpeg/lib -lavdevice
LIBS += -L$$PWD/../libs/videoWrite/FFmpeg/lib -lavfilter
LIBS += -L$$PWD/../libs/videoWrite/FFmpeg/lib -lavformat
LIBS += -L$$PWD/../libs/videoWrite/FFmpeg/lib -lavutil
LIBS += -L$$PWD/../libs/videoWrite/FFmpeg/lib -lpostproc
LIBS += -L$$PWD/../libs/videoWrite/FFmpeg/lib -lswresample
LIBS += -L$$PWD/../libs/videoWrite/FFmpeg/lib -lswscale
LIBS += -L$$PWD/../libs/videoWrite -lmatch2

DISTFILES += \
    logo.rc


RC_FILE += logo.rc

