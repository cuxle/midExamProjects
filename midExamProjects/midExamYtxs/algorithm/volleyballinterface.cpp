#include "volleyballinterface.h"
#include <QDebug>
VolleyballInterface::VolleyballInterface()
{

}

VolleyballLib::VolleyballLib(const QString &libName)
    :VolleyballInterface(),
      AlgorithmLoadBase(libName)
{
    resolveFunction();
    initModel();
}

VolleyballLib::~VolleyballLib()
{

}

void VolleyballLib::resolveFunction ()
{
    InitDetector = (FuncInitDetector)m_lib->resolve("detectorInit");
    if (InitDetector) {
        qDebug() << "parse successfully";
    } else {
        qDebug() << "parse failed";
    }

    ResetDetector = (FuncResetDetector)m_lib->resolve("detectorReset");
    if (ResetDetector) {
        qDebug() << "parse successfully";
    } else {
        qDebug() << "parse failed";
    }

    CountVolleyball = (FuncCountVolleyball)m_lib->resolve("volleyballCount");
    if (CountVolleyball) {
        qDebug() << "parse successfully";
    } else {
        qDebug() << "parse failed";
    }

    SetRect = (FuncSetRect)m_lib->resolve("setOff");
    if (SetRect) {
        qDebug() << "parse successfully";
    } else {
        qDebug() << "parse failed";
    }
}

void VolleyballLib::initModel()
{
    int ret = InitDetector(720, 1280);
    qDebug() << "init algo successfully!"<< ret;
    if (ret == 1) {
        qDebug() << "init algo successfully!" ;
        ResetDetector();
    } else {
        qDebug() << "initModel algo failed!";
    }
}


