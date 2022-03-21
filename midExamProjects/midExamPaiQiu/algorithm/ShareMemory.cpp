#pragma once 
// ShareMemory.cpp : ���ļ�������Ϣ����SHAREDMEMOR���ʵ��
// Author : MJJ
// Update : 2020/11/27
#ifndef ShareMemory_CPP
#define ShareMemory_CPP

#include "ShareMemory.h"
#include <iostream>

using namespace cv;
using namespace std;

/*************************************************************************************
FuncName  :SHAREDMEMORY::~SHAREDMEMORY()
Desc      :���캯�����������ڴ�
Input     :None
Output    :None
**************************************************************************************/
SHAREDMEMORY::SHAREDMEMORY() {
    hShareMem = CreateFileMapping(
        INVALID_HANDLE_VALUE,  // use paging file
        NULL,                  //default security
        PAGE_READWRITE,        //read/write access
        0,                     // maximum object size(high-order DWORD)
        MEMORY_SIZE,           //maximum object size(low-order DWORD)
        sShareMemName);        //name of mapping object

    if (hShareMem) {
        //  ӳ�������ͼ���õ������ڴ�ָ�룬��������
        pBuf = (LPTSTR)MapViewOfFile(
            hShareMem,           //handle to map object
            FILE_MAP_ALL_ACCESS, // read/write permission
            0,
            0,
            MEMORY_SIZE);
        cout << "memory size:" << MEMORY_SIZE << endl;

        // ��ӳ��ʧ���˳�
        if (pBuf == NULL)
        {
            std::cout << "Could not map view of framebuffer file." << GetLastError() << std::endl;
            CloseHandle(hShareMem);
            state = MAPVIEWFAILED;
        }
    }
    else
    {
        std::cout << "Could not create file mapping object." << GetLastError() << std::endl;
        state = CREATEMAPFAILED;
    }
    state = INITSUCCESS;
}

/*************************************************************************************
FuncName  :SHAREDMEMORY::~SHAREDMEMORY()
Desc      :���������ͷ�
Input     :None
Output    :None
**************************************************************************************/
SHAREDMEMORY::~SHAREDMEMORY() {
    std::cout << "unmap shared addr." << std::endl;
    UnmapViewOfFile(pBuf); //�ͷţ�
    CloseHandle(hShareMem);
}

/*************************************************************************************
FuncName  :void SHAREDMEMORY::SendMat(cv::Mat img, char indexAddress)
Desc      :����Mat����
Input     :
    Mat img               ����ͼ��
    char indexAddress     �����ڴ�����ʼλ�ã���ֻ��һ·��Ƶ����ƫ��
Output    :None
**************************************************************************************/
void SHAREDMEMORY::SendMat(cv::Mat img, char indexAddress) {
    ImgInf img_head;
    img_head.width = img.cols;
    img_head.height = img.rows;
    img_head.type = img.type();

    if (img_head.type == CV_64FC1) {
        memcpy((char*)pBuf + indexAddress, &img_head, sizeof(ImgInf));
        memcpy((char*)pBuf + indexAddress + sizeof(ImgInf),        // Address of dst
            img.data,                                              // Src data
            img.cols * img.rows * img.channels() * sizeof(double)  // size of data
        );
    }
    else
    {
        memcpy((char*)pBuf + indexAddress, &img_head, sizeof(ImgInf));
        memcpy((char*)pBuf + indexAddress + sizeof(ImgInf),        // Address of dst
            img.data,                                              // Src data
            img.cols * img.rows * img.channels()                   // size of data
        );
    }
    cout << "write shared mem successful." << endl;
}


/*************************************************************************************
FuncName  :cv::Mat SHAREDMEMORY::ReceiveMat(char indexAddress)
Desc      :����Mat����
Input     :
    char indexAddress     �����ڴ�����ʼλ�ã���ֻ��һ·��Ƶ����ƫ��
Output    :Matͼ��
**************************************************************************************/
cv::Mat SHAREDMEMORY::ReceiveMat(char indexAddress)
{
    ImgInf img_head;
    cv::Mat img;
    memcpy(&img_head, (char*)pBuf + indexAddress, sizeof(ImgInf));
    img.create(img_head.height, img_head.width, img_head.type);
    if (img_head.type == CV_64FC1)
    {
        memcpy(img.data, (char*)pBuf + indexAddress + sizeof(ImgInf), img.cols * img.rows * img.channels() * sizeof(double));
    }
    else
    {
        memcpy(img.data, (char*)pBuf + indexAddress + sizeof(ImgInf), img.cols * img.rows * img.channels());
    }
    return img;
}

/*************************************************************************************
FuncName  :void SHAREDMEMORY::SendStr(cv::Mat img, char indexAddress)
Desc      :����str����
Input     :
    Mat img               ����ͼ��
    char indexAddress     �����ڴ�����ʼλ�ã���ֻ��һ·��Ƶ����ƫ��
Output    :None
**************************************************************************************/
void SHAREDMEMORY::SendStr(const char data[]) {
    memcpy((char*)pBuf, data, sizeof(data));
    cout << "write shared mem successful." << endl;
    getchar();
}

/*************************************************************************************
FuncName  :void SHAREDMEMORY::ReceiveStr()
Desc      :����str����
Input     :None
Output    :��ȡ���ַ���
**************************************************************************************/
char* SHAREDMEMORY::ReceiveStr() {
    char* str = (char*)pBuf;
    cout << "receive is:" << str << endl;
    return str;
}
#endif // !ShareMemory_CPP