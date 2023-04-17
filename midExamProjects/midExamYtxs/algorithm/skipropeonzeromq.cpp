#include "skipropeonzeromq.h"

#include <zmq.h>
#include <string.h>
#include <QDebug>
#include <QImage>
#include "ShareMemory.h"
#include <singleton.h>
#include <appconfig.h>
#include "utils.h"

SkipRopeOnZeroMq::SkipRopeOnZeroMq(QObject *parent)
    : QObject(parent)
{

}

SkipRopeOnZeroMq::~SkipRopeOnZeroMq()
{
    //unregisterClient();
}

void SkipRopeOnZeroMq::init()
{
    contex = zmq_ctx_new();
    responder = zmq_socket(contex, ZMQ_REQ);
    int ret = zmq_connect(responder, "tcp://localhost:5552");

    contex1 = zmq_ctx_new();
    responder1 = zmq_socket(contex1, ZMQ_REP);
    int ret1 = zmq_connect(responder1, "tcp://localhost:5553");

    if (ret == 0 && ret1 == 0) {
        qDebug() << "connect local server successfully";
        memset(get_data, 0x00, 10);
        zmq_recv(responder1, get_data, 10, 0);
        qDebug() << "server run successfully";
        qDebug() << "Start result:" << get_data;

        emit sigContinueRun();

        zmq_send(responder1, "1", 1, 0);

        registerClient();

        // set off
        AppConfig &config = Singleton<AppConfig>::GetInstance();
        int offSet = config.m_rectPoint2y;
        setOff(offSet);

        resetCount();
    } else {
        qDebug() << "connect local server failed";
    }

}

void SkipRopeOnZeroMq::handleDestroyObject()
{
    unregisterClient();
    zmq_disconnect(responder, "tcp://localhost:5552");
    zmq_close(responder);

    zmq_disconnect(responder1, "tcp://localhost:5553");
    zmq_close(responder1);

    this->deleteLater();
}

// 输入的ydown是矩形框的下边缘的y坐标
// 返回值是0说明设置成功；返回值是1说明设置失败。
void SkipRopeOnZeroMq::setOff(int ydown)
{
    if(ydown < 100 || ydown > 1000)
    {
        qDebug() << "ydwon is out of range";
        return;
    }

    std::string message = std::to_string(5000+ydown);

    zmq_send(responder, message.data(), 4, 0);
    memset(get_data, 0x00, 10);
    zmq_recv(responder, get_data, 10, 0);
    if (get_data[0] == '1') {
        qDebug() << "detector init successfully";
    }
    else if (get_data[0] == '-') {
        qDebug() << "detector init failed";
    }
}

void SkipRopeOnZeroMq::registerClient()
{
    //std::string Model = "1";
    Model = "1";
    zmq_send(responder, Model.data(), 1, 0);
    memset(get_data, 0x00, 10);

    // Note: if not connected to python server,
    // the below code will block, while the main thread cannot destruct this class
    // and the appconfig cannot destruct, so the setting cannot be saved
    zmq_recv(responder, get_data, 10, 0);

    if (get_data[0] == '1') {
        qDebug() << "detector init successfully";
    }
    else if (get_data[0] == '-') {
        qDebug() << "detector init failed";
    }
}

void SkipRopeOnZeroMq::unregisterClient()
{
    Model = "4";
    zmq_send(responder, Model.data(), 1, 0);
//    char get_data[10] = { 0 };
    memset(get_data, 0x00, 10);
    zmq_recv(responder, get_data, 10, 0);
    if (get_data[0] == '1') {
        qDebug() << "unregisterClient init successfully";
    }
    else if (get_data[0] == '-') {
        qDebug() << "unregisterClient init failed";
    }
}

void SkipRopeOnZeroMq::startCount(bool bIsCounting)
{
    qDebug() <<__func__ << __LINE__ << m_bStartCount;
    m_bStartCount = bIsCounting;   
}

void SkipRopeOnZeroMq::resetCount()
{
//    m_ropeSkiplib->ResetDetector();
    m_count = 0;
    m_lastCount = 0;
    std::cout<<"开始技术特征初始化"<<std::endl;
//    std::string
    Model = "2";
    //if (responder == nullptr) return;
    zmq_send(responder, Model.data(), 1, 0);
//    char get_data[10] = { 0 };
    memset(get_data, 0x00, 10);
    zmq_recv(responder, get_data, 10, 0);
    if (get_data[0] == '1') {
        qDebug() << "计数特征初始化成功！";
    }
    else if (get_data[0] == '-') {
        qDebug() << "计数特征初始化失败，重新初始化！";
    }
}

void SkipRopeOnZeroMq::handleReceiveImage(const QImage &image)
{
    if (m_bStartCount) {
        //        QImage img = image;

        qDebug() << __func__ <<__LINE__ << image.height() << image.width();

        cv::Mat frame(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());

        QDateTime baseTime = QDateTime::currentDateTime();

//        SHAREDMEMORY sharedmem;

        if (sharedmem.state == INITSUCCESS)
        {

            sharedmem.SendMat(frame, FRAME_NUMBER);

            std::string Model = "3";
            zmq_send(responder, Model.data(), 1, 0);

            char get_data[10] = { 0 };
            memset(get_data, 0x00, 10);

            zmq_recv(responder, get_data, 10, 0);

            if (get_data[0] == '-') {
//                qDebug() << "skip rope run filed, restart couter program";
            }
            else{
                m_count = strtol(get_data, NULL, 10);
            }
        }
        emit sigSkipCountChanged(m_count);

//        m_count = m_ropeSkiplib->CountSkipRope(frame.rows, frame.cols, std::move(frame.data));
//        qDebug() << "skip rope cost time in ms:" << -QDateTime::currentDateTime().msecsTo(baseTime);

//        qDebug() << "lastcout " << m_lastCount << "count:" << m_count;
//        if (m_count - m_lastCount >= 10) {
//            m_lastCount = m_count;
//            emit sigSkipCountChanged(m_count);
//        }


   }
}

void SkipRopeOnZeroMq::handleReceiveMat(cv::Mat image)
{
    //qDebug() << __func__ << __LINE__;
    if (m_bStartCount) {
        //        QImage img = image;
        cv::Mat mat;
        image.copyTo(mat);

        qDebug() << __LINE__ << __func__<< mat.rows << mat.cols;

//        SHAREDMEMORY sharedmem;

        if (sharedmem.state == INITSUCCESS)
        {
            sharedmem.SendMat(image, FRAME_NUMBER);

            std::string Model = "3";
            zmq_send(responder, Model.data(), 1, 0);
            char get_data[10] = { 0 };
            memset(get_data, 0x00, 10);
            zmq_recv(responder, get_data, 10, 0);
            if (get_data[0] == '-') {
                qDebug() << "skip rope run filed, restart couter program";
            }
            else{
                m_count = strtol(get_data, NULL, 10);
            }
        }
        //m_count = m_ropeSkiplib->CountSkipRope(mat.rows, mat.cols, mat.data);
        std::cout << "skip count:" << m_count << std::endl;
        emit sigSkipCountChanged(m_count);
    }
}
