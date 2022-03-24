#-------------------------------------------------
#
# Project created by QtCreator 2021-09-22T17:33:59
#
#-------------------------------------------------

QT       += core gui multimedia network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = midExamYtxs
TEMPLATE = app


SHARED_PATH = ../common

include($$SHARED_PATH/common.pri)


DEFINES += YTXS

#include(./libs/xlsx/qtxlsx.pri)

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
    algorithm/ShareMemory.cpp \
    algorithm/algorithmloadbase.cpp \
    #algorithm/ropeskippinginterface.cpp \
    #algorithm/ropeskipworker.cpp \
    #appconfig.cpp \
    #camera/camera.cpp \
    #camera/csamplecaptureeventhandler.cpp \
    #datamanager.cpp \
    #examprojectbasicinfo.cpp \
    #localstudenttablemodel.cpp \
    #log/Logger.cpp \
    #logindialog.cpp \
        main.cpp \
    #maincounter.cpp \
    #    mainwindow.cpp \
    #formlogin.cpp \
    formfuncchoose.cpp \
    #networkServer/networkserver.cpp \
    #schoollisttablemodel.cpp \
    #scoremanagemodel.cpp \
    #settingdialog.cpp \
    algorithm/skipropeonzeromq.cpp \
    #socket/client.cpp \
    #student.cpp \
    #studentmanager.cpp \
    #videomanage/mat2qtformatmethod.cpp \
    #videomanage/videocaptureworker.cpp \
    #videoReplay/videoreplayworker.cpp \
    videowidget.cpp

HEADERS += \
    #TmpStudent.h \
    algorithm/ShareMemory.h \
    algorithm/algorithmloadbase.h \
    #algorithm/ropeskippinginterface.h \
    #algorithm/ropeskipworker.h \
    #appconfig.h \
    #camera/camera.h \
    #camera/csamplecaptureeventhandler.h \
    #datamanager.h \
    #defines.h \
    #examprojectbasicinfo.h \
    #localstudenttablemodel.h \
    #log/Logger.h \
    #logindialog.h \
    #maincounter.h \
    #    mainwindow.h \
    #formlogin.h \
    formfuncchoose.h \
    #networkServer/networkserver.h \
    #schoollisttablemodel.h \
    #scoremanagemodel.h \
    #settingdialog.h \
    #singleton.h \
    algorithm/skipropeonzeromq.h \
    #socket/client.h \
    #student.h \
    #studentmanager.h \
    #videomanage/mat2qtformatmethod.h \
    #videomanage/videocaptureworker.h \
    #videoReplay/videoreplayworker.h \
    videowidget.h
    #libs/videoWrite/videoWriterFFmpeg.h

FORMS += \
    #logindialog.ui \
    #    mainwindow.ui \
    #formlogin.ui \
    formfuncchoose.ui
    #settingdialog.ui

RESOURCES += \
    res.qrc

INCLUDEPATH += "D:\ProgramData\DahengImaging\GalaxySDK\Samples\C++SDK\inc"

unix|win32: LIBS += -LD:/ProgramData/DahengImaging/GalaxySDK/Samples/C++SDK/lib/x64/ -lGxIAPICPPEx

INCLUDEPATH += D:/ProgramData/DahengImaging/GalaxySDK/Samples/C++SDK/lib/x64
DEPENDPATH += D:/ProgramData/DahengImaging/GalaxySDK/Samples/C++SDK/lib/x64

#win32:CONFIG(release, debug|release): LIBS += -LD:/QtbAK/opencv3410/opencv/build/x64/vc15/lib/ -lopencv_world3410
#else:win32:CONFIG(debug, debug|release): LIBS += -LD:/QtbAK/opencv3410/opencv/build/x64/vc15/lib/ -lopencv_world3410d
#else:unix: LIBS += -LD:/QtbAK/opencv3410/opencv/build/x64/vc15/lib/ -lopencv_world3410

#INCLUDEPATH += D:/QtbAK/opencv3410/opencv/build/include
#DEPENDPATH += D:/QtbAK/opencv3410/opencv/build/include

#win32:CONFIG(release, debug|release): LIBS += -LD:/opencv/build/x64/vc15/lib/ -lopencv_world3410
#else:win32:CONFIG(debug, debug|release): LIBS += -LD:/opencv/build/x64/vc15/lib/ -lopencv_world3410d
#else:unix: LIBS += -LD:/opencv/build/x64/vc15/lib/ -lopencv_world3410

#INCLUDEPATH += D:/opencv/build/include
#DEPENDPATH += D:/opencv/build/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libs/zmq/libzmq/build2019/lib/ -llibzmq-mt-4_3_5
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libs/zmq/libzmq/build2019/lib/ -llibzmq-mt-4_3_5d
else:unix: LIBS += -L$$PWD/../libs/zmq/libzmq/build2019/lib/ -llibzmq-mt-4_3_5

INCLUDEPATH += $$PWD/../libs/zmq/libzmq/include
DEPENDPATH += $$PWD/../libs/zmq/libzmq/include

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

