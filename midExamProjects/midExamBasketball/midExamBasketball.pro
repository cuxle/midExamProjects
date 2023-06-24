#-------------------------------------------------
#
# Project created by QtCreator 2021-09-22T17:33:59
#
#-------------------------------------------------

QT       += core gui multimedia network printsupport sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = midExamBasketball
TEMPLATE = app

SHARED_PATH = ../common

include($$SHARED_PATH/common.pri)
include($$PWD/pcl.pri)
#include(./libs/xlsx/qtxlsx.pri)

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

DEFINES += BASKETBALL
#DEFINES += TIAOSHENG

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    examregin.cpp \
    lidar/godleilaser.cpp \
    lidar/godleilasermsop.cpp \
    lidar/lidarBasketballAnalysis.cpp \
    lidarcloudview.cpp \
    qcustomplot.cpp \
    formfuncchoose.cpp \
    videowidget.cpp

HEADERS += \
    examregin.h \
    lidar/godleilaser.h \
    lidar/godleilasermsop.h \
    lidar/lidarBasketballAnalysis.h \
    lidarcloudview.h \
    qcustomplot.h \
    formfuncchoose.h \
    videowidget.h

FORMS += \
    formfuncchoose.ui

RESOURCES += \
    res.qrc

DISTFILES += \
    logo.rc

RC_FILE += logo.rc

