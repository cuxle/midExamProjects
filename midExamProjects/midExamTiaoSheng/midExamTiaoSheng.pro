#-------------------------------------------------
#
# Project created by QtCreator 2021-09-22T17:33:59
#
#-------------------------------------------------

QT       += core gui multimedia network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = midExamTiaoSheng
TEMPLATE = app

SHARED_PATH = ../common

include($$SHARED_PATH/common.pri)


#include(./libs/xlsx/qtxlsx.pri)

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

DEFINES += TIAOSHENG

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    algorithm/ShareMemory.cpp \
    algorithm/algorithmloadbase.cpp \
    formfuncchoose.cpp \
    algorithm/skipropeonzeromq.cpp \
    socket/client.cpp \
    videowidget.cpp

HEADERS += \
    algorithm/ShareMemory.h \
    algorithm/algorithmloadbase.h \
    formfuncchoose.h \
    algorithm/skipropeonzeromq.h \
    socket/client.h \
    videowidget.h

FORMS += formfuncchoose.ui

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

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libs/zmq/libzmq/build2019/lib/ -llibzmq-mt-4_3_5
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libs/zmq/libzmq/build2019/lib/ -llibzmq-mt-4_3_5d
else:unix: LIBS += -L$$PWD/../libs/zmq/libzmq/build2019/lib/ -llibzmq-mt-4_3_5

INCLUDEPATH += $$PWD/../libs/zmq/libzmq/include
DEPENDPATH += $$PWD/../libs/zmq/libzmq/include
