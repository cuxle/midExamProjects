#pragma once
#ifndef __lidarAnalysis__
#define __lidarAnalysis__

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

class lidarAnalysis
{
public:
	//����궨�߽�����
	float m_xMin = 0.0f;
	float m_xMax = 10.0f;
	float m_yMin = 0.0f;
	float m_yMax = 30.0f;
	float m_zMin = -0.5f;
	float m_zMax = 1.0f;

	//��һ����ı߽�
	float m_xBorderMin = -5.0f;
	float m_xBorderMax = 5.0f;
	float m_yBorderMin = 0.0f;
	float m_yBorderMax = 30.0f;

	PointXYZ m_flag1 = PointXYZ(0.0f, 5.0f, 2.0f);
	PointXYZ m_flag2 = PointXYZ(0.0f, 10.0f, 2.0f);
	PointXYZ m_flag3 = PointXYZ(0.0f, 15.0f, 2.0f);
	PointXYZ m_flag4 = PointXYZ(0.0f, 20.0f, 2.0f);
	PointXYZ m_flag5 = PointXYZ(0.0f, 25.0f, 2.0f);
	float m_radius = 0.2f;

	//ǰ������ID
	int m_prevRegionID = 0;
//	int m_currentRegionID = 0;
//	int m_nextRegionID = 0;

	//��һ֡��λ
	PointXYZ m_PointLast = PointXYZ(0.0f, 0.0f, 0.0f);

	//���Կ�ʼ����ʱ��
	clock_t m_start, m_finish;

	//���Լ�ʱ
	double m_duration;

	//����״̬��ʶ  �����ʼ���� inExam = true  ������Խ��� inExam = false
	bool m_inExam = false;


	//��������
	int m_stepIdx = 0;
	int m_OutCnt = 0;

	//��׼���Թ켣
	int m_trailIdx = 0; //1: trail1  2:trail2
	int trail1[12] = { 1, 2, 4, 3, 5, 6, 8, 7, 9, 10, 12, 11 };
	int trail2[12] = { 2, 1, 3, 4, 6, 5, 7, 8, 10, 9, 11, 12 };
	bool m_flagStatus[5] = {false, false, false, false, false };


	lidarAnalysis();
	virtual ~lidarAnalysis();

	float dist(PointXYZ pt1, PointXYZ pt2);
	bool setTestRegion(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);
	bool normalizeData(PointCloud<PointXYZ>::Ptr cloudPtr);

	//���ÿ��Կ�ʼ������־
	bool setExamStart(float x, float y);
	bool setExamEnd();
	bool resetExamParams();

	std::vector<PointXYZ> objectDetection(PointCloud<PointXYZ>::Ptr cloudPtr);
	int *lidarAnalysis::rand_rgb();


	bool removePtsOutOfRegion(float xMin, float xMax, float yMin, float yMax, vector<float> pts);

	int tracking(PointXYZ ptPos);	//����ֵ 0:δ��ʼ����  1�����Խ����� 2�������������� 3����������


	//��ȡ��ǰ��������ID
	int getRegionID(float x, float y);

};



#endif