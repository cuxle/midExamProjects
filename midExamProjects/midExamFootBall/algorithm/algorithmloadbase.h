#ifndef ALGORITHMLOADBASE_H
#define ALGORITHMLOADBASE_H

#include <QLibrary>

class AlgorithmLoadBase
{
public:
    AlgorithmLoadBase(const QString &libName);
    virtual ~AlgorithmLoadBase();

protected:
    QLibrary *m_lib = nullptr;
};

#endif // ALGORITHMLOADBASE_H
