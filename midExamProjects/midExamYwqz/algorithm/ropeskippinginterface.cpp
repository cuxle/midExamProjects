#include "ropeskippinginterface.h"
#include <QDebug>
#include <QFile>
#include <QDir>

RopeSkippingInterface::RopeSkippingInterface()
{

}

RopeSkippingLib::RopeSkippingLib(const QString &libName)
    :RopeSkippingInterface(),
      AlgorithmLoadBase(libName)
{
    resolveFunction();
    initModel();
}

RopeSkippingLib::~RopeSkippingLib()
{
    int ret = PoseRelease();
    if (ret == 0) {
        qDebug() << "release google lib failed";
    } else {
        qDebug() << "release google lib successfully";
    }
}

void RopeSkippingLib::resolveFunction ()
{
    InitDetector = (FuncInitDetector)m_lib->resolve("InitDetector");
    if (InitDetector) {
        qDebug() << "parse successfully";
    } else {
        qDebug() << "parse failed";
    }

    ResetDetector = (FuncResetDetector)m_lib->resolve("ResetDetector");
    if (ResetDetector) {
        qDebug() << "parse successfully";
    } else {
        qDebug() << "parse failed";
    }

    CountSkipRope = (FuncCountSkipRope)m_lib->resolve("CountSkipRope");
    if (CountSkipRope) {
        qDebug() << "parse successfully";
    } else {
        qDebug() << "parse failed";
    }

    GetHumanPose = (FuncGetHumanPose)m_lib->resolve("GetHumanPose");
    if (GetHumanPose) {
        qDebug() << "parse successfully";
    } else {
        qDebug() << "parse failed";
    }

    PoseRelease = (Pose_Release)m_lib->resolve("POSE_RELEASE");
    if (PoseRelease) {
        qDebug() << "parse successfully";
    } else {
        qDebug() << "parse failed";
    }
}

void RopeSkippingLib::initModel()
{
    QFile file;
    file.setFileName("pose_tracking_cpu.pbtxt");

    int ret = InitDetector((char*)"pose_tracking_cpu.pbtxt");
    if (ret == 1) {
        qDebug() << "init algo successfully!" ;
        ResetDetector();
    } else {
        qDebug() << "init algo failed!";
    }
}


