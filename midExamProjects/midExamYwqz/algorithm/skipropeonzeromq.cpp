#include "skipropeonzeromq.h"

#include <zmq.h>

#include <QDebug>
#include <QImage>
#include <QTimer>
#include "singleton.h"
#include "appconfig.h"
#include "ShareMemory.h"

SkipRopeOnZeroMq::SkipRopeOnZeroMq(QObject *parent)
    : QObject(parent)
{
    AppConfig &config = Singleton<AppConfig>::GetInstance();

    int p1x =  config.m_rectPoint1x;
    int p1y =  config.m_rectPoint1y;

    int p2x =  config.m_rectPoint2x;
    int p2y =  config.m_rectPoint2y;

    handleReginRectChanged(p1x, p2y, abs(p2y-p1y), abs(p2x-p1x));

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

        cv::Mat frame(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());

        QDateTime baseTime = QDateTime::currentDateTime();

        //        SHAREDMEMORY sharedmem;
        qDebug() << "handleReceiveImage:" << frame.cols << frame.rows;
        if (sharedmem.state == INITSUCCESS)
        {
            bool ding = false;

            addMaskForMat(frame);

            sharedmem.SendMat(frame, FRAME_NUMBER);

            std::string Model = "3";
            zmq_send(responder, Model.data(), 1, 0);
            char get_data[10] = { 0 };
            memset(get_data, 0x00, 10);
            zmq_recv(responder, get_data, 10, 0);

            if (get_data[0] == '-') {
                qDebug() << "skip rope run filed, restart couter program";
            } else {
//                qDebug() << __func__ << __LINE__ << get_data[0] << get_data[1];
                if(get_data[0] == '0' && get_data[1] != 0x00)
                {
//                    ding = true;
                } else {
                    // count 是当前帧传递后获得的计数返回值
                    // m_count 应该是一个全局的计数值，只有计数变化时才修改
                    int count = strtol(get_data, NULL, 10);
                    if(count > m_count)
                    {
                        ding = true;
                        m_count = count;
                    }
                }
            }

            if(ding) {
                //调用声音
                emit sigPlayDingSound();
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

void SkipRopeOnZeroMq::handleReceiveMat(const cv::Mat &image)
{
    //qDebug() << __func__ << __LINE__;
    if (m_bStartCount) {
        //        QImage img = image;
        cv::Mat mat;
        image.copyTo(mat);
//        qDebug() << __LINE__ << __func__;
//        qDebug() << mat.rows << mat.cols;

//        SHAREDMEMORY sharedmem;

        if (sharedmem.state == INITSUCCESS) {
            bool ding = false;
            addMaskForMat(mat);
//            qDebug() << __func__ << __LINE__;
            sharedmem.SendMat(mat, FRAME_NUMBER);

            std::string Model = "3";
            zmq_send(responder, Model.data(), 1, 0);
            char get_data[10] = { 0 };
            memset(get_data, 0x00, 10);
            zmq_recv(responder, get_data, 10, 0);

            if (get_data[0] == '-') {
                qDebug() << "skip rope run filed, restart couter program";
            } else {
                if(get_data[0] == '0' && get_data[1] != 0x00)
                {
//                    ding = true;
                } else {
                    // count 是当前帧传递后获得的计数返回值
                    // m_count 应该是一个全局的计数值，只有计数变化时才修改
                    int count = strtol(get_data, NULL, 10);
                    if(count > m_count)
                    {
                        ding = true;
                        m_count = count;
                    }
                }
            }

            if(ding) {
                //调用声音
                emit sigPlayDingSound();
            }
        }
        //m_count = m_ropeSkiplib->CountSkipRope(mat.rows, mat.cols, mat.data);
        std::cout << "skip count:" << m_count << std::endl;
        emit sigSkipCountChanged(m_count);
    }
}


void SkipRopeOnZeroMq::handleReginRectChanged(int p1x, int p1y, int height, int width)
{
    m_maskOrigin.setX(p1x);
    m_maskOrigin.setY(p1y);

    m_maskHeight = height;
    m_maskWidth = width;

    qDebug() << "x:" << p1x << " y:" << p1y << " height:" << height << " width:" << width;
}

void SkipRopeOnZeroMq::addMaskForMat(cv::Mat &mat)
{
    cv::Rect rect_mask(m_maskOrigin.x(), m_maskOrigin.y(), m_maskWidth, m_maskHeight);
    cv::Mat subImage = mat(rect_mask);
    // 设置为黑色
    subImage.setTo(0);
}
