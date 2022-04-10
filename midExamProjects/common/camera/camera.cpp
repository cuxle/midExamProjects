#include "camera.h"
#include <QDebug>
#include <QImage>
#include <QTimer>
#include <QThread>
#include <opencv2/opencv.hpp>
#include "algorithm/ropeskipworker.h"


Camera::Camera(bool useOpencv, QObject *parent)
    :QObject(parent),
      m_openCvCamera(useOpencv)

{
    qRegisterMetaType<CameraState>("CameraState");
}

Camera::~Camera()
{
//    qDebug() << __func__;
//    closeCamera();
//    destoryCamera();
}

void Camera::openCamera()
{
    if (m_openCvCamera) {
        if (m_videoCapture->isOpened()) {
            m_videoCapture->release();
        }
        m_bIsOpen = m_videoCapture->open(1);

        // only open the first one device
        qDebug() << "m_bIsOpen :" << m_bIsOpen;

//            emit sigCameraOpened(true);
        emit sigCameraState(CameraOpened);

        m_opencvCameraTimer->start(40);
    } else {
        openDevice();
        if (bIsOpen()) {
            StartSnap(nullptr);
        } else {
            // send error msg;
        }
    }

}

void Camera::closeCamera()
{
    if (m_openCvCamera) {
        if (m_videoCapture->isOpened()) {
            m_videoCapture->release();
        }
        m_opencvCameraTimer->stop();
    } else {
        if (bIsSnap()) {
            StopSnap();
        }
        if (bIsOpen()) {
            CloseDevice();
        }
    }

}

void Camera::initCamera()
{
    if (m_openCvCamera) {
        m_videoCapture = QSharedPointer<cv::VideoCapture>(new cv::VideoCapture);
        m_opencvCameraTimer = new QTimer;
        connect(m_opencvCameraTimer, &QTimer::timeout, this, &Camera::hangleGrabFrameMat);
    } else {
        m_pCaptureEventHandler = new CSampleCaptureEventHandler();
        m_image = new QImage(m_nWidth, m_nHeight, QImage::Format_RGB888);

        // init camera lib
        try {
            IGXFactory::GetInstance().Init();
        } catch (CGalaxyException &e) {
            qDebug() << "Error Code:" << e.GetErrorCode();
            qDebug() << "Error Code Description:" << e.what();
        }
    }

}

void Camera::hangleGrabFrameMat()
{
    if (m_videoCapture.isNull()) return;
    bool readFrame = m_videoCapture->read(m_frameMat);
    qDebug() << __func__ << __LINE__ << readFrame;
    emit sigImageCaptureMat(m_frameMat);
}

void Camera::destoryCamera()
{
    closeCamera();
    if (m_openCvCamera) {
        delete m_opencvCameraTimer;
    } else {
        IGXFactory::GetInstance().Uninit();
        delete m_image;
        delete m_pCaptureEventHandler;
        this->deleteLater();
    }

}

void Camera::openDevice()
{
    GxIAPICPP::gxdeviceinfo_vector vectorDeviceInfo;
    IGXFactory::GetInstance().UpdateAllDeviceList(1000, vectorDeviceInfo);

    if (vectorDeviceInfo.size() == 0) {
        emit sigCameraState(CameraNotFound);
    }
    for (size_t i = 0; i < vectorDeviceInfo.size(); i++) {
        // if device is open already, vectorDeviceInfo size still will be 1
        // and call GetSN will crash

        gxstring strDeviceSN = vectorDeviceInfo[0].GetSN();

        bool bIsDeviceOpen   = false;      ///< 判断设备是否已打开标志
        bool bIsStreamOpen   = false;      ///< 判断设备流是否已打开标志
        int nDeviceIndex= i;
        try
        {
            if (m_bIsOpen ||  strDeviceSN == "") {
                throw std::exception("无效参数!");
            }

            m_strDeviceSN = strDeviceSN;
            m_nDeviceIndex  = nDeviceIndex;

            //打开设备
            m_objDevicePtr = IGXFactory::GetInstance().OpenDeviceBySN(strDeviceSN, GX_ACCESS_EXCLUSIVE);
            bIsDeviceOpen = true;
            qDebug() << strDeviceSN << __LINE__;
            //获取属性控制器
            m_objFeatureControlPtr = m_objDevicePtr->GetRemoteFeatureControl();

            //设置采集模式为连续采集
            m_objFeatureControlPtr->GetEnumFeature("AcquisitionMode")->SetValue("Continuous");

            //设置触发模式为关
            m_objFeatureControlPtr->GetEnumFeature("TriggerMode")->SetValue("Off");

            //是否支持Bayer格式
            m_bIsColorFilter = m_objFeatureControlPtr->IsImplemented("PixelColorFilter");
            qDebug() << "m_bIsColorFilter:" << m_bIsColorFilter;

            m_objFeatureControlPtr->GetEnumFeature("ExposureAuto")->SetValue("Off");
            gxstring s = m_objFeatureControlPtr->GetEnumFeature("ExposureAuto")->GetValue();
            std::cout << "ExposureAuto " << s << std::endl;
            QThread::msleep(100);

            m_objFeatureControlPtr->GetFloatFeature("ExposureTime")->SetValue(CAMERA_EXPOSE_TIME);
            double d = m_objFeatureControlPtr->GetFloatFeature("ExposureTime")->GetValue();
            qDebug() << "ExposureTime " << d;
            QThread::msleep(100);

            m_objFeatureControlPtr->GetEnumFeature("AcquisitionFrameRateMode")->SetValue("On");
             s = m_objFeatureControlPtr->GetEnumFeature("AcquisitionFrameRateMode")->GetValue();
            std::cout << "AcquisitionFrameRateMode " << s << std::endl;
            QThread::msleep(100);

            m_objFeatureControlPtr->GetFloatFeature("AcquisitionFrameRate")->SetValue(CAMERA_FRAME_RATE);
            d = m_objFeatureControlPtr->GetFloatFeature("AcquisitionFrameRate")->GetValue();
            qDebug() << "AcquisitionFrameRate:" << d;
            QThread::msleep(100);

            //Set Balance White Mode : Once 。设置白平衡，每次点击开始或者60秒重新计时的时候设置一次
            //Set Balance White Mode : Continuous 。设置白平衡，每次点击开始或者60秒重新计时的时候设置一次 - 20220225.春燕
            m_objFeatureControlPtr->GetEnumFeature("BalanceWhiteAuto")->SetValue(CAMERA_WIHTE_BALANCE);
            s = m_objFeatureControlPtr->GetEnumFeature("BalanceWhiteAuto")->GetValue();
            std::cout << "BalanceWhiteAuto " << s << std::endl;
            QThread::msleep(100);

            // Set Gain : Once。设置增益，每次点击开始或者60秒重新计时的时候设置一次
            m_objFeatureControlPtr->GetEnumFeature("GainSelector")->SetValue("AnalogAll");
            QThread::msleep(100);
            m_objFeatureControlPtr->GetEnumFeature("GainAuto")->SetValue(CAMERA_GAIN_MODE);
            s = m_objFeatureControlPtr->GetEnumFeature("GainAuto")->GetValue();
            QThread::msleep(100);
            std::cout << "GainAuto " << s << std::endl;


//            m_nWidth = (int64_t)m_objFeatureControlPtr->GetIntFeature("Width")->GetValue();
//            m_nHeight = (int64_t)m_objFeatureControlPtr->GetIntFeature("Height")->GetValue();

            //获取设备流个数
            int nCount = m_objDevicePtr->GetStreamCount();

            if (nCount > 0)
            {
                m_objStreamPtr = m_objDevicePtr->OpenStream(0);
                bIsStreamOpen = true;
                qDebug() << "bIsStreamOpen :" << bIsStreamOpen;
            }
            else
            {
                throw std::exception("未发现设备流!");
            }

            m_bIsOpen = true;

            // only open the first one device
            qDebug() << "m_bIsOpen :" << m_bIsOpen;

//            emit sigCameraOpened(true);
            emit sigCameraState(CameraOpened);
            break;
        }
        catch (CGalaxyException& e)
        {

            //判断设备流是否已打开
            if (bIsStreamOpen)
            {
                m_objStreamPtr->Close();
            }

            //判断设备是否已打开
            if (bIsDeviceOpen)
            {
                m_objDevicePtr->Close();
            }

            m_bIsOpen = false;

            throw e;

        }
        catch (std::exception& e)
        {
            //判断设备流是否已打开
            if (bIsStreamOpen)
            {
                m_objStreamPtr->Close();
            }

            //判断设备是否已打开
            if (bIsDeviceOpen)
            {
                m_objDevicePtr->Close();
            }

            m_bIsOpen = false;

            throw e;
        }
    }
}

//------------------------------------------------------------
/**
\brief   Close Device

\return  void
*/
//------------------------------------------------------------
void Camera::CloseDevice()
{
    if (!m_bIsOpen)
    {
        return;
    }

    try
    {
        //判断是否停止采集
        if (m_bIsSnap)
        {

            //发送停采命令
            if (m_objFeatureControlPtr.IsNull()) {
                return;
            }
            m_objFeatureControlPtr->GetCommandFeature("AcquisitionStop")->Execute();

            //关闭流层采集
            if (m_objStreamPtr.IsNull()) {
                return;
            }
            m_objStreamPtr->StopGrab();

            //注销回调函数
            m_objStreamPtr->UnregisterCaptureCallback();
        }
    }
    catch (CGalaxyException)
    {
        //do noting
    }

    try {
        //关闭流对象
        if (m_objStreamPtr.IsNull()) {
            return;
        }
        m_objStreamPtr->Close();
    } catch (CGalaxyException) {
        //do noting
    }

    try
    {
        //关闭设备
        if (m_objDevicePtr.IsNull()) {
            return;
        }
        m_objDevicePtr->Close();

    }
    catch (CGalaxyException)
    {
        //do noting
    }

    m_bIsSnap = false;
    m_bIsOpen = false;
//    emit sigCameraOpened(false);
    emit sigCameraState(CameraClosed);
}

//------------------------------------------------------------
/**
\brief   Start Snap

\return  void
*/
//------------------------------------------------------------
void Camera::StartSnap(QLabel *qtHandle)
{
    //判断设备是否已打开
    if (!m_bIsOpen)
    {
        return;
    }

    try
    {
        //注册回调函数
        if (m_objStreamPtr.IsNull()) {
            return;
        }
        m_objStreamPtr->RegisterCaptureCallback(m_pCaptureEventHandler, this);
        qDebug() << __func__ << __LINE__;
    } catch (CGalaxyException& e) {
        throw e;
    }

    try {
        //开启流层采集
        if (m_objStreamPtr.IsNull()) {
            return;
        }
        m_objStreamPtr->StartGrab();
        qDebug() << __func__ << __LINE__;
    } catch (CGalaxyException& e) {
        //注销回调函数
        m_objStreamPtr->UnregisterCaptureCallback();
        throw e;
    }

    try
    {
        //发送开采命令
        if (m_objFeatureControlPtr.IsNull()) {
            return;
        }
        qDebug() << __func__ << __LINE__;
        m_objFeatureControlPtr->GetCommandFeature("AcquisitionStart")->Execute();
        m_bIsSnap = true;
    }
    catch (CGalaxyException& e)
    {
        //关闭流层采集
        m_objStreamPtr->StopGrab();

        //注销回调函数
        m_objStreamPtr->UnregisterCaptureCallback();
        throw e;
    } catch (std::exception& e) {
        //关闭流层采集
        m_objStreamPtr->StopGrab();

        //注销回调函数
        m_objStreamPtr->UnregisterCaptureCallback();
        throw e;
    }

    if (m_bIsSnap) {
        if (m_objFeatureControlPtr.IsNull()) {
            return;
        }
//        m_objFeatureControlPtr->GetCommandFeature("AcquisitionStart")->Execute();
//        m_objFeatureControlPtr->GetEnumFeature("GainSelector")->SetValue("AnalogAll");
//        m_objFeatureControlPtr->GetEnumFeature("GainAuto")->SetValue("Continuous");

        // ENABLE white balance
//        m_objFeatureControlPtr->GetEnumFeature("BalanceWhiteAuto")->SetValue("Continuous");

//        m_objFeatureControlPtr->GetCommandFeature("AcquisitionStart")->Execute();
//        m_objFeatureControlPtr->GetEnumFeature("ExposureAuto")->SetValue("Off");
//        gxstring s = m_objFeatureControlPtr->GetEnumFeature("ExposureAuto")->GetValue();
//        std::cout << "ExposureAuto " << s << std::endl;
//        QThread::msleep(100);

//        m_objFeatureControlPtr->GetFloatFeature("ExposureTime")->SetValue(10000.0000);
//        double d = m_objFeatureControlPtr->GetFloatFeature("ExposureTime")->GetValue();
//        qDebug() << "ExposureTime " << d;
//        QThread::msleep(100);

//        m_objFeatureControlPtr->GetEnumFeature("AcquisitionFrameRateMode")->SetValue("On");
//         s = m_objFeatureControlPtr->GetEnumFeature("AcquisitionFrameRateMode")->GetValue();
//        std::cout << "AcquisitionFrameRateMode " << s << std::endl;
//        QThread::msleep(100);

//        m_objFeatureControlPtr->GetFloatFeature("AcquisitionFrameRate")->SetValue(25);
//        d = m_objFeatureControlPtr->GetFloatFeature("AcquisitionFrameRate")->GetValue();
//        qDebug() << "AcquisitionFrameRate:" << d;
//        QThread::msleep(100);

//        //Set Balance White Mode : Once 。设置白平衡，每次点击开始或者60秒重新计时的时候设置一次
//        //Set Balance White Mode : Continuous 。设置白平衡，每次点击开始或者60秒重新计时的时候设置一次 - 20220225.春燕
//        m_objFeatureControlPtr->GetEnumFeature("BalanceWhiteAuto")->SetValue("Continuous");
//        s = m_objFeatureControlPtr->GetEnumFeature("BalanceWhiteAuto")->GetValue();
//        std::cout << "BalanceWhiteAuto " << s << std::endl;
//        QThread::msleep(100);

//        // Set Gain : Once。设置增益，每次点击开始或者60秒重新计时的时候设置一次
//        m_objFeatureControlPtr->GetEnumFeature("GainSelector")->SetValue("AnalogAll");
//        QThread::msleep(100);
//        m_objFeatureControlPtr->GetEnumFeature("GainAuto")->SetValue("Once");
//        s = m_objFeatureControlPtr->GetEnumFeature("GainAuto")->GetValue();
//        QThread::msleep(100);
//        std::cout << "GainAuto " << s << std::endl;
////        string s = m_objFeatureControlPtr->GetEnumFeature("ExposureAuto")->GetValue();
    }
}


//------------------------------------------------------------
/**
\brief   Stop Snap

\return  void
*/
//------------------------------------------------------------
void Camera::StopSnap()
{
    //判断设备是否已打开
    if (!m_bIsOpen || !m_bIsSnap)
    {
        return;
    }

    try
    {
        //发送停采命令
        m_objFeatureControlPtr->GetCommandFeature("AcquisitionStop")->Execute();

        //关闭流层采集
        m_objStreamPtr->StopGrab();

        //注销回调函数
        m_objStreamPtr->UnregisterCaptureCallback();

        //帧率置0
        //m_objfps.Reset();

        m_bIsSnap = false;
    }
    catch (CGalaxyException& e)
    {
        throw e;

    }
    catch (std::exception& e)
    {
        throw e;

    }
}

bool Camera::bIsSnap() const
{
    return m_bIsSnap;
}

bool Camera::bIsOpen() const
{
    return m_bIsOpen;
}

void Camera::pushImage()
{
    if (m_openCvCamera) {
        return;
    } else {
        // send signal image captured
        emit sigImageCapture(*m_image);
    }
}

void Camera::updateCameraSettings()
{
    if (m_openCvCamera) {
        return;
    } else {
        if (!m_objFeatureControlPtr.IsNull()) {

            //Set Balance White Mode : Once 。设置白平衡，每次点击开始或者60秒重新计时的时候设置一次
            m_objFeatureControlPtr->GetEnumFeature("BalanceWhiteAuto")->SetValue("Continuous");
            gxstring s = m_objFeatureControlPtr->GetEnumFeature("BalanceWhiteAuto")->GetValue();
            std::cout << "BalanceWhiteAuto " << s << std::endl;

            // Set Gain : Once。设置增益，每次点击开始或者60秒重新计时的时候设置一次
            m_objFeatureControlPtr->GetEnumFeature("GainSelector")->SetValue("Continuous");
            m_objFeatureControlPtr->GetEnumFeature("GainAuto")->SetValue("Once");
            s = m_objFeatureControlPtr->GetEnumFeature("GainAuto")->GetValue();
            std::cout << "GainAuto " << s << std::endl;
        }

    }
}

QImage *Camera::image() const
{
    return m_image;
}
