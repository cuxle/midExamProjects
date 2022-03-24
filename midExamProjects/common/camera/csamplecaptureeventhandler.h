#ifndef CSAMPLECAPTUREEVENTHANDLER_H
#define CSAMPLECAPTUREEVENTHANDLER_H

#include "GalaxyIncludes.h"
//#include "mainwindow.h"
#include <QDebug>
#include <cstring>

class CSampleCaptureEventHandler : public ICaptureEventHandler
{
public:
    BYTE* pBuffer;
    quint64 m_counter = 0;
    void DoOnImageCaptured(CImageDataPointer& objImageDataPointer, void* pUserParam);

};

#endif // CSAMPLECAPTUREEVENTHANDLER_H
