#pragma once
// ShareMemory.h : ���ļ����������ڴ����ݶ��塢��Сȷ����λ�÷��䡢��Ϣ����
// Author : Jiejing.Ma
// Update : 2020/11/27
#ifndef ShareMemory_H
#define ShareMemory_H

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>  // cv::Canny()
#include <opencv2/opencv.hpp>

#include <Windows.h>

//=================================�����ڴ����ݶ���=================================
typedef struct {
    int width;
    int height;
    int type;
}ImgInf;       //ͼ����Ϣ
//=================================�����ڴ��Сȷ��=================================
// Ϊͼ�����ռ�
#define FRAME_NUMBER         1               // ͼ��·��
//#define FRAME_W              1280
//#define FRAME_H              1024
#define FRAME_W              1920
#define FRAME_H              1080
#define FRAME_W_H            FRAME_W*FRAME_H
// ͼ��ֱ��ʣ���ɫͼ��3ͨ����+ͼ����Ϣ�ṹ��
#define FRAME_SIZE           FRAME_W_H*sizeof(unsigned char)*3+sizeof(ImgInf)

#define MEMORY_SIZE          FRAME_NUMBER*FRAME_SIZE

//=================================�����ڴ���Ϣ����=================================
#define INITSUCCESS      0
#define CREATEMAPFAILED  1
#define MAPVIEWFAILED    2

class SHAREDMEMORY
{
public:
    SHAREDMEMORY();
    ~SHAREDMEMORY();
    void SendMat(cv::Mat img, char indexAddress);
    cv::Mat  ReceiveMat(char indexAddress);
    void SendStr(const char data[]);
    char* ReceiveStr();

public:
    int state;
private:
    HANDLE hShareMem;                               //�����ڴ���
    TCHAR sShareMemName[30] = TEXT("ShareMedia");   // �����ڴ�����
    LPCTSTR pBuf;
};

#endif // !ShareMemory_H#pragma once
