#include "csamplecaptureeventhandler.h"
#include "camera.h"
#include <QPainter>
#include <QDateTime>

void CSampleCaptureEventHandler::DoOnImageCaptured(CImageDataPointer& objImageDataPointer, void* pUserParam)
{
    Camera *cam = (Camera*)pUserParam;

    QImage *m_show_image = cam->image();
//    static QDateTime dateTime = QDateTime::currentDateTime();

    if (objImageDataPointer->GetStatus() == GX_FRAME_STATUS_SUCCESS) {
        //图像获取为完整帧，可以读取图像宽、高、数据格式等
        uint64_t nWidth = objImageDataPointer->GetWidth();
        uint64_t nHeight = objImageDataPointer->GetHeight();

//        qDebug() << __func__ << __LINE__ << nWidth << nHeight;

        GX_VALID_BIT_LIST emValidBits = GX_BIT_0_7;
        pBuffer = m_show_image->bits();

        memcpy(pBuffer,(BYTE*)objImageDataPointer->ConvertToRGB24(emValidBits, GX_RAW2RGB_NEIGHBOUR, false),nWidth * nHeight * 3);

        cam->pushImage();
    }
}
