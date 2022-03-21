#include "situpinterface.h"
#include <QDebug>
SitupInterface::SitupInterface()
{

}

SitupLib::SitupLib(const QString &libName)
    :SitupInterface(),
      AlgorithmLoadBase(libName)
{
    resolveFunction();
    initModel();
}

SitupLib::~SitupLib()
{

}

void SitupLib::resolveFunction ()
{
    qDebug() << "InitDetector";
    InitDetector = (FuncInitDetector)m_lib->resolve("detectorInit");
    if (InitDetector) {
        qDebug() << "parse successfully";
    } else {
        qDebug() << "parse failed";
    }
    qDebug() << "ResetDetector";
    ResetDetector = (FuncResetDetector)m_lib->resolve("detectorReset");
    if (ResetDetector) {
        qDebug() << "parse successfully";
    } else {
        qDebug() << "parse failed";
    }
    qDebug() << "CountSitup";
    CountSitup = (FuncCountSitup)m_lib->resolve("situpCount");
    if (CountSitup) {
        qDebug() << "parse successfully";
    } else {
        qDebug() << "parse failed";
    }
    qDebug() << "SetRect ";
    SetRect = (FuncSetRect)m_lib->resolve("setOff");
    if (SetRect) {
        qDebug() << "parse successfully";
    } else {
        qDebug() << "parse failed";
    }
}

void SitupLib::initModel()
{
    qDebug() << "init algo!";
    int ret = InitDetector(1280, 960);
    qDebug() << "init algo successfully!"<< ret;
    if (ret == 1) {
        qDebug() << "init algo successfully!" ;
        ResetDetector();
    } else {
        qDebug() << "initModel algo failed!";
    }
}


