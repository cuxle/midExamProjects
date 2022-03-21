#ifndef SITUPINTERFACE_H
#define SITUPINTERFACE_H
#include "algorithmloadbase.h"

class SitupInterface
{
protected:
    typedef int(*FuncInitDetector)(int, int); // 定义函数指针类型
    typedef void(*FuncResetDetector)();
    typedef int(*FuncCountSitup)(int, int, unsigned char*, bool *bUp, bool *bDown);
    typedef int(*FuncSetRect)(int, int, int, int, int, int, int, int, int, int);


public:
    SitupInterface();

    FuncInitDetector InitDetector = nullptr;

    FuncResetDetector ResetDetector = nullptr;

    FuncCountSitup CountSitup = nullptr;

    FuncSetRect SetRect = nullptr;


};

class SitupLib : public SitupInterface, public AlgorithmLoadBase {
public:
    SitupLib(const QString &libName);
    ~SitupLib();
private:
    void resolveFunction ();
    void initModel();
};

#endif // SITUPINTERFACE_H
