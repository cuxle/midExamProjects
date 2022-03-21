#ifndef ROPESKIPPINGINTERFACE_H
#define ROPESKIPPINGINTERFACE_H

#include "algorithmloadbase.h"

class RopeSkippingInterface
{
protected:
    typedef int(*FuncInitDetector)(char*); // 定义函数指针类型
    typedef void(*FuncResetDetector)();
    typedef int(*FuncCountSkipRope)(int, int, unsigned char*);
    typedef int(*FuncGetHumanPose)(int, int, unsigned char*, int*);
    typedef int (*Pose_Release)();

public:
    RopeSkippingInterface();

    FuncInitDetector InitDetector = nullptr;

    FuncResetDetector ResetDetector = nullptr;

    FuncCountSkipRope CountSkipRope = nullptr;

    FuncGetHumanPose GetHumanPose = nullptr;

    Pose_Release PoseRelease = nullptr;
};

class RopeSkippingLib : public RopeSkippingInterface, public AlgorithmLoadBase {
public:
    RopeSkippingLib(const QString &libName);
    ~RopeSkippingLib();
private:
    void resolveFunction ();
    void initModel();
};

#endif // ROPESKIPPINGINTERFACE_H
