#pragma once
// ShareMemory.h :
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

//==================================================================
typedef struct {
    int width;
    int height;
    int type;
}ImgInf; 
//==================================================================
// 
#define FRAME_NUMBER         1 
#define FRAME_W              1280
#define FRAME_H              1024
#define FRAME_W_H            FRAME_W*FRAME_H
// 
#define FRAME_SIZE           FRAME_W_H*sizeof(unsigned char)*3+sizeof(ImgInf)

#define MEMORY_SIZE          FRAME_NUMBER*FRAME_SIZE

//==================================================================
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
    HANDLE hShareMem;                               //
    TCHAR sShareMemName[30] = TEXT("ShareMedia");   //
    LPCTSTR pBuf;
};

#endif // !ShareMemory_H#pragma once
