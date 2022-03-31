#ifndef VOLLEYBALLINTERFACE_H
#define VOLLEYBALLINTERFACE_H
#include "algorithm/algorithmloadbase.h"

class VolleyballInterface
{
protected:
    typedef int(*FuncInitDetector)(int, int); // 定义函数指针类型
    typedef void(*FuncResetDetector)();
    typedef int(*FuncCountVolleyball)(int, int, unsigned char*);
    typedef int(*FuncSetRect)(int, int, int, int);


public:
    VolleyballInterface();

    FuncInitDetector InitDetector = nullptr;

    FuncResetDetector ResetDetector = nullptr;

    FuncCountVolleyball CountVolleyball = nullptr;

    FuncSetRect SetRect = nullptr;


};

class VolleyballLib : public VolleyballInterface, public AlgorithmLoadBase {
public:
    VolleyballLib(const QString &libName);
    ~VolleyballLib();
private:
    void resolveFunction ();
    void initModel();
};

#endif // VOLLEYBALLINTERFACE_H
