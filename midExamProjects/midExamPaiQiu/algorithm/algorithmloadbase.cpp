#include "algorithmloadbase.h"
#include <QDebug>

AlgorithmLoadBase::AlgorithmLoadBase(const QString &libName)
    :m_lib(new QLibrary())
{
    // set file name
    // load lib
    m_lib->setFileName(libName);
    m_lib->load();
    if (m_lib->isLoaded()) {
        qDebug() << __FUNCTION__ << __LINE__ << "load lib " << libName << "success";
    } else {
        qDebug() << __FUNCTION__ << __LINE__ << "load lib " << libName << "failed";
    }
}

AlgorithmLoadBase::~AlgorithmLoadBase()
{
    if (m_lib->isLoaded()) {
        m_lib->unload();
    }
    delete m_lib;
}
