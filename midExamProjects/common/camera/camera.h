#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
#include "GalaxyIncludes.h"
#include "csamplecaptureeventhandler.h"
#include "camerasetting.h"

class RopeSkipWorker;
class QImage;
class QTimer;
class QLabel;

enum CameraState {
    CameraOpened,
    CameraNotFound,
    CameraClosed
};

class Camera : public QObject
{
    Q_OBJECT
public:
    Camera(QObject *parent = nullptr);
    ~Camera();

    QImage *image() const;

    bool bIsOpen() const;

    void pushImage();

    void updateCameraSettings();

public slots:
    void initCamera();
    void destoryCamera();

    void openCamera();
    void closeCamera();

signals:
    void sigImageCapture(const QImage &img);
//    void sigCameraOpened(bool);
    void sigCameraState(CameraState);

private slots:
    void handleSendImage();

private:
    void openDevice();
    void StartSnap(QLabel *qtHandle);
    void StopSnap();
    void CloseDevice();

    bool bIsSnap() const;


    // basic camera type
    CGXStreamPointer m_objStreamPtr;
    CGXDevicePointer m_objDevicePtr;
    CGXFeatureControlPointer m_objFeatureControlPtr;

    GxIAPICPP::gxstring m_strDeviceSN;
    int m_nDeviceIndex;

    // handlers
    ICaptureEventHandler *m_pCaptureEventHandler;


    QImage *m_image = nullptr;

    // QObject interface
    int m_nWidth = FRAME_WIDTH;
    int m_nHeight = FRAME_HEIGHT;

    bool m_bIsOpen = false;
    bool m_bIsSnap = false;
    bool m_bIsColorFilter = false;    
};

#endif // CAMERA_H
