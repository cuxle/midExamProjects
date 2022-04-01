#pragma once
#ifndef __lidarBasketballAnalysis__
#define __lidarBasketballAnalysis__

#include <vector>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/segmentation/extract_clusters.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/ModelCoefficients.h>

#include <time.h>

using namespace std;
using namespace pcl;

class lidarBasketballAnalysis
{	
public:
	//标准篮球场尺寸 28m * 15m
	float m_xMin = 0.0f;
	float m_xMax = 15.0f;
	float m_yMin = 0.0f;
	float m_yMax = 28.0f;
	float m_zMin = -0.5f;
	float m_zMax = 1.0f;
	float m_xBorderMin = -7.5f;
	float m_xBorderMax = 7.5f;
	float m_yBorderMin = 0.0f;
	float m_yBorderMax = 28.0f;

	//Flag position
	//----------------------------------------
	//         |           |         |    |
	//    8    |     9     |   10    |   5.8m
	//         |           |         |    |
	//--------(F5)-------(F6)--------|--------
	//         |           |         |
	//    5    |     6     |    7    |
	//         |           |         |
	//--------(F3)-------(F4)--------|
	//         |           |         |
	//    2    |     3     |    4    |
	//         |           |         |
	//--------(F1)-------(F2)--------|--------
	//                               |    |
	//               1               |   5.8m
	//                               |    |
	//-------------(0,0)----------------------start line
	PointXYZ m_flag1 = PointXYZ(-0.9f,  5.8f, 1.2f);
	PointXYZ m_flag2 = PointXYZ( 0.9f,  5.8f, 1.2f);
	PointXYZ m_flag3 = PointXYZ(-0.9f, 14.0f, 1.2f);
	PointXYZ m_flag4 = PointXYZ( 0.9f, 14.0f, 1.2f);
	PointXYZ m_flag5 = PointXYZ(-0.9f, 22.2f, 1.2f);
	PointXYZ m_flag6 = PointXYZ( 0.9f, 22.2f, 1.2f);

	//标志杆消隐区域
	float m_radius = 0.2f;
    float m_clusterTolerance = 0.5;
    int m_MinClusterSize = 6;
    int m_MaxClusterSize = 1000;
    //最小目标尺寸与距离加权系数
    float m_ratio = 1.0f;


	//前后区域ID
	int m_prevRegionID = 0;
//	int m_currentRegionID = 0;
//	int m_nextRegionID = 0;

	//上一帧点位
	PointXYZ m_PointLast = PointXYZ(0.0f, 0.0f, 0.0f);

	//考试开始结束时间
	clock_t m_start, m_finish;

	//考试计时
	double m_duration;

	//考试状态标识  点击开始考试 inExam = true  点击考试结束 inExam = false
	bool m_inExam = false;


	//步骤索引
	int m_stepIdx = 0;

	//出区域计数
	int m_OutCnt = 0;

	//标准考试轨迹(绕"8"字)
	int m_trailIdx = 0; //1: trail1  2:trail2
	int trail1[17] = {1, 4, 3, 2, 5, 6, 7, 10, 9, 8, 5, 6, 7, 4, 3, 2, 1};
	int trail2[17] = {1, 2, 3, 4, 7, 6, 5, 8, 9, 10, 7, 6, 5, 2, 3, 4, 1};

	bool m_flagStatus[6] = {false, false, false, false, false, false };
	int m_flagStatusIdx1[6] = { 1, 2, 5, 4, 3, 0 };
	int m_flagStatusIdx2[6] = { 0, 3, 4, 5, 2, 1 };


	lidarBasketballAnalysis();
	virtual ~lidarBasketballAnalysis();

	float dist(PointXYZ pt1, PointXYZ pt2);
	bool setTestRegion(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);
	bool normalizeData(PointCloud<PointXYZ>::Ptr cloudPtr);

	//设置考试开始结束标志
	bool setExamStart(float x, float y);
	bool setExamEnd();
	bool resetExamParams();

	std::vector<PointXYZ> objectDetection(PointCloud<PointXYZ>::Ptr cloudPtr);
	int *lidarBasketballAnalysis::rand_rgb();


//	bool removePtsOutOfRegion(float xMin, float xMax, float yMin, float yMax, vector<float> pts);

	int tracking(PointXYZ ptPos);	//返回值 0:未开始考试  1：考试进行中 2：考试正常结束 3：考生犯规


	//获取当前所在区域ID
	int getRegionID(float x, float y);

};



#endif
