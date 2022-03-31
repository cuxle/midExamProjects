#include "lidarAnalysis.h"

lidarAnalysis::lidarAnalysis()
{

}

lidarAnalysis::~lidarAnalysis()
{

}

float lidarAnalysis::dist(PointXYZ pt1, PointXYZ pt2)
{
	float distance = sqrt((pt1.x - pt2.x) * (pt1.x - pt2.x) + (pt1.y - pt2.y) * (pt1.y - pt2.y));
	return distance;
}

bool lidarAnalysis::normalizeData(PointCloud<PointXYZ>::Ptr cloudPtr)
{
	std::vector<pcl::PointXYZ, Eigen::aligned_allocator<pcl::PointXYZ> > pointsArr;

	float ratio = 30.0f / abs(m_yMax - m_yMin);
	m_xBorderMax = (m_xMax - m_xMin) * ratio / 2.0f;
	m_xBorderMin = -m_xBorderMax;

	for (int i = 0; i < cloudPtr->points.size(); i++)
	{
		if (cloudPtr->points[i].x > m_xMin && cloudPtr->points[i].x < m_xMax && cloudPtr->points[i].y > m_yMin && cloudPtr->points[i].y < m_yMax && cloudPtr->points[i].z > m_zMin && cloudPtr->points[i].z < m_zMax)
		{
			PointXYZ tempXYZ = cloudPtr->points[i];
			tempXYZ.x = (tempXYZ.x - (m_xMax + m_xMin) / 2.0f) * ratio;
			tempXYZ.y = (tempXYZ.y - m_yMin) * ratio;

			if (dist(tempXYZ, m_flag1) > m_radius && dist(tempXYZ, m_flag2) > m_radius && dist(tempXYZ, m_flag3) > m_radius && dist(tempXYZ, m_flag4) > m_radius && dist(tempXYZ, m_flag5) > m_radius)
			{
				pointsArr.push_back(tempXYZ);
			}
		}
	}
	cloudPtr->points.resize(0);
	cloudPtr->points = pointsArr;
	cloudPtr->width = 1;
	cloudPtr->height = cloudPtr->points.size();

	return true;
}

bool lidarAnalysis::removePtsOutOfRegion(float xMin, float xMax, float yMin, float yMax, vector<float> pts)
{

	return true;
}

bool lidarAnalysis::setTestRegion(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax)
{
	m_xMin = xMin;
	m_xMax = xMax;
	m_yMin = yMin;
	m_yMax = yMax;
	m_zMin = zMin;
	m_zMax = zMax;

	return true;
}

int *lidarAnalysis::rand_rgb() {//���������ɫ
	int *rgb = new int[3];
	rgb[0] = rand() % 255;
	rgb[1] = rand() % 255;
	rgb[2] = rand() % 255;
	return rgb;
}

//���ÿ��Բ���
bool lidarAnalysis::resetExamParams()
{
	m_prevRegionID = 0;
	m_PointLast = PointXYZ(0.0f, 0.0f, 0.0f);
	m_duration = 0.0;
	m_inExam = false;
	m_stepIdx = 0;
	m_OutCnt = 0;
	m_trailIdx = 0;
	m_flagStatus[0] = false;
	m_flagStatus[1] = false;
	m_flagStatus[2] = false;
	m_flagStatus[3] = false;
	m_flagStatus[4] = false;
	return true;
}

//���ÿ��Կ�ʼ
bool lidarAnalysis::setExamStart(float x, float y)
{
	//�����־λ�Ѿ��ǿ����У�����������
	if (m_inExam == true)
	{
		return true;
	}
	else
	{
		if (getRegionID(x, y) > 0)
		{
			//ѧ��Խ�緸�� �޷���ʼ����
			return false;
		}
		else
		{
			

			m_inExam = true;
			return true;
		}
	}

}

//���ÿ��Խ�����־
bool lidarAnalysis::setExamEnd()
{
	//�����־λ�Ѿ��ǿ��Խ���������������
	if (m_inExam == false)
	{
		return true;
	}
	else
	{
		m_finish = clock();
		m_duration = (double)(m_finish - m_start) / CLOCKS_PER_SEC;
		m_inExam = false;
		return true;
	}
}

int lidarAnalysis::getRegionID(float x, float y)
{
	if (x < m_xBorderMin || x > m_xBorderMax || y < m_yBorderMin || y > m_yBorderMax)
	{
		return 0;
	}

	int areaID = y / 5;
	if (x >= 0)
	{
		areaID = areaID * 2 + 2;
	}
	else
	{
		areaID = areaID * 2 + 1;
	}

	return areaID;
}

//����ֵ 0:δ��ʼ����  1�����Խ����� 2�������������� 3����������
int lidarAnalysis::tracking(PointXYZ ptPos)
{
	//�ڿ����вŷ������λ�� ���ڿ���������ptPosĬ�ϸ���(0,-1)
	if (m_inExam)
	{
		int curID = getRegionID(ptPos.x, ptPos.y);

		//�������뿼�������ڲſ�ʼ��ʱ
		if (curID > 0 && m_prevRegionID == 0)
		{
			m_start = clock();
			m_prevRegionID = curID;
			m_stepIdx++;
		}

		//���뿼������
		if (m_stepIdx > 0)
		{
			if (curID == 0)
			{
				//������֡�����򣬱�ʾ���Խ���
				if (m_OutCnt == 0)
				{
					m_finish = clock();
				}
				m_OutCnt++;

				if (m_OutCnt == 3)
				{
					if (m_flagStatus[0] && m_flagStatus[1] && m_flagStatus[2] && m_flagStatus[3] && m_flagStatus[4])
					{
						//���5�����Ӷ��ƹ���
						m_duration = (double)(m_finish - m_start) / CLOCKS_PER_SEC;

						if (abs(m_PointLast.y - m_yBorderMax) < abs(m_PointLast.x - m_xBorderMin) && abs(m_PointLast.y - m_yBorderMax) < abs(m_PointLast.x - m_xBorderMax))
						{
							//�������Ч����ǰ������߽� ���������Խ���
							return 2;
						}
						else
						{
							//��Ȼ�ƹ����еĸ� �������û�дӵ��߳�ȥ
							return 3;
						}
					}
					else
					{
						//�������
						m_duration = (double)(m_finish - m_start) / CLOCKS_PER_SEC;
						return 3;
					}
				}
			}
			else if (curID < 3)
			{
				m_PointLast = ptPos; //����һ���ڿ��������ڵĵ�λ
				//��1-2�����ڲ�������·��,������Ȼ���Ը���·��
				if (m_prevRegionID != curID)
				{
					m_prevRegionID = curID;
				}
				m_OutCnt = 0;

			}
			else
			{
				m_PointLast = ptPos; //����һ���ڿ��������ڵĵ�λ
				if (curID == 4 && m_stepIdx == 1)
				{
					m_trailIdx = 1;
					m_stepIdx++;
				}
				else if (curID == 3 && m_stepIdx == 1)
				{
					m_trailIdx = 2;
					m_stepIdx++;
				}

				//�߲�ͬ�ı�׼�켣
				if (m_trailIdx == 1)
				{
					if (m_prevRegionID != curID)
					{
						if (m_prevRegionID == trail1[m_stepIdx - 1] && curID == trail1[m_stepIdx])
						{
							m_flagStatus[m_stepIdx / 2 - 1] = true;
							m_prevRegionID = curID;
							m_stepIdx++;
						}
					}
				}
				else if (m_trailIdx == 2)
				{
					if (m_prevRegionID != curID)
					{
						if (m_prevRegionID == trail2[m_stepIdx - 1] && curID == trail2[m_stepIdx])
						{
							m_flagStatus[m_stepIdx / 2 - 1] = true;
							m_prevRegionID = curID;
							m_stepIdx++;
						}
					}
				}
				m_OutCnt = 0;
			}
			return 1;
		}
		else
		{
			return 0;
		}
	}
}

std::vector<PointXYZ> lidarAnalysis::objectDetection(PointCloud<PointXYZ>::Ptr cloudPtr)
{
	vector<PointXYZ> objDetected;
	int nPtMax = 0;

	//��PCLPointCloud2�������
	PCLPointCloud2::Ptr cloud(new pcl::PCLPointCloud2());
	toPCLPointCloud2(*cloudPtr, *cloud);
	
	//���ػ��²���
	VoxelGrid<pcl::PCLPointCloud2> vox;
	pcl::PCLPointCloud2::Ptr vox_cloud(new pcl::PCLPointCloud2());
	vox.setInputCloud(cloud);
	vox.setLeafSize(0.01, 0.01, 0.01);
	vox.filter(*vox_cloud);
//	cout << "After Voxel Grid��" << vox_cloud->fields.size() << endl;
	
	//ȥ��������
	StatisticalOutlierRemoval<pcl::PCLPointCloud2> sor;
	pcl::PCLPointCloud2::Ptr sor_cloud_filtered(new pcl::PCLPointCloud2());
	sor.setMeanK(10);
	sor.setInputCloud(vox_cloud);
	sor.setStddevMulThresh(0.2);
	sor.filter(*sor_cloud_filtered);
//	cout << "After Statistical Outlie rRemoval��" << sor_cloud_filtered->fields.size() << endl;

	//ת��Ϊԭʼ��ʽ���
	PointCloud<PointXYZ>::Ptr sor_cloud(new PointCloud<PointXYZ>);
	fromPCLPointCloud2(*sor_cloud_filtered, *sor_cloud);
	cout << "After Statistical Outlie rRemoval��" << sor_cloud->points.size() << endl;

	//��������С��5, ��Ϊ������û��Ŀ���򷵻�һ��Ĭ�ϵĿ�������������
	if (sor_cloud->points.size() < 5)
	{
		objDetected.push_back(PointXYZ(0.0f, -1.0f, 0.0f));
		return objDetected;
	}

	//ŷʽ����
	vector<PointIndices>ece_inlier;
	search::KdTree<PointXYZ>::Ptr tree(new search::KdTree<PointXYZ>);
	EuclideanClusterExtraction<PointXYZ> ece;
	ece.setInputCloud(sor_cloud);
	ece.setClusterTolerance(0.5);	//ece.setClusterTolerance(0.02);
	ece.setMinClusterSize(5);		//ece.setMinClusterSize(100);
	ece.setMaxClusterSize(200);		//ece.setMaxClusterSize(20000);
	ece.setSearchMethod(tree);
	ece.extract(ece_inlier);

	//������չʾ
//	int j = 0;
//	visualization::PCLVisualizer::Ptr viewer2(new visualization::PCLVisualizer("Result of EuclideanCluster"));
//	srand((unsigned)time(NULL));

	//����������������Ҫ���Ŀ��Ϊ0, �򷵻�һ���������Ĭ��ֵ
	cout << "number of objects��" << ece_inlier.size() << endl;
	if (ece_inlier.size() < 1)
	{
		objDetected.push_back(PointXYZ(0.0f, -1.0f, 0.0f));
		return objDetected;
	}

	for (int i = 0; i < ece_inlier.size(); i++)
	{
		PointCloud<PointXYZ>::Ptr cloud_copy(new PointCloud<PointXYZ>);
		vector<int> ece_inlier_ext = ece_inlier[i].indices;
		copyPointCloud(*sor_cloud, ece_inlier_ext, *cloud_copy);//����������ȡ��������
		
//		stringstream ss1;
//		ss1 << "D:\\" << "EuclideanCluster_clouds" << j << ".pcd";
//		io::savePCDFileASCII(ss1.str(), *ext_cloud);//ŷʽ������д��
//		int *rgb1 = rand_rgb();
//		visualization::PointCloudColorHandlerCustom<PointXYZ>rgb2(cloud_copy, rgb1[0], rgb1[1], rgb1[2]);
//		delete[]rgb1;
//		viewer2->addPointCloud(cloud_copy, rgb2, ss1.str());
//		j++;

		//������
		PointXYZ centroid = PointXYZ(0.0f, 0.0f, 0.0f);
		for (int cnt = 0; cnt < cloud_copy->points.size(); cnt++)
		{
			centroid.x += cloud_copy->points[cnt].x;
			centroid.y += cloud_copy->points[cnt].y;
			centroid.z += cloud_copy->points[cnt].z;
		}
		centroid.x = centroid.x / cloud_copy->points.size();
		centroid.y = centroid.y / cloud_copy->points.size();
		centroid.z = centroid.z / cloud_copy->points.size();

		if (i > 0)
		{
			if (nPtMax < cloud_copy->points.size())
			{
				nPtMax = cloud_copy->points.size();
				PointXYZ temp = objDetected[0];
				objDetected[0] = centroid;
				objDetected.push_back(temp);
			}
			else
			{
				objDetected.push_back(centroid);
			}

		}
		else
		{
			nPtMax = cloud_copy->points.size();
			objDetected.push_back(centroid);
		}
	}

//	viewer2->spin();
	cout << "nPtMax: " << nPtMax << endl;
	return objDetected;

}

/*
std::vector<PointXYZ> lidarAnalysis::objectDetection(PointCloud<PointXYZ>::Ptr cloudPtr)
{
	vector<PointXYZ> objDetected;
	int nPtMax = 0;

	//���ػ��²���
	VoxelGrid<PointXYZ> vox;
	PointCloud<PointXYZ>::Ptr vox_cloud(new PointCloud<PointXYZ>);
	vox.setInputCloud(cloudPtr);
	vox.setLeafSize(0.01, 0.01, 0.01);
	vox.filter(*vox_cloud);
	cout << "After Voxel Grid��" << vox_cloud->points.size() << endl;

	//ȥ��������
	StatisticalOutlierRemoval<PointXYZ> sor;
	PointCloud<PointXYZ>::Ptr sor_cloud(new PointCloud<PointXYZ>);
	sor.setMeanK(10);
	sor.setInputCloud(vox_cloud);
	sor.setStddevMulThresh(0.2);
	sor.filter(*sor_cloud);
	cout << "After Statistical Outlie rRemoval��" << sor_cloud->points.size() << endl;

	//��������С��5, ��Ϊ������û��Ŀ���򷵻�һ��Ĭ�ϵĿ�������������
	if (sor_cloud->points.size() < 5)
	{
		objDetected.push_back(PointXYZ(0.0f, -1.0f, 0.0f));
		return objDetected;
	}

	//--------------------
	//ƽ��ָRANSAC��
	SACSegmentation<PointXYZ> sac;
	PointIndices::Ptr inliner(new PointIndices);
	ModelCoefficients::Ptr coefficients(new ModelCoefficients);
	PointCloud<PointXYZ>::Ptr sac_cloud(new PointCloud<PointXYZ>);
	sac.setInputCloud(sor_cloud);
	sac.setMethodType(SAC_RANSAC);
	sac.setModelType(SACMODEL_PLANE);
	sac.setMaxIterations(100);
	sac.setDistanceThreshold(0.02);

	//��ȡƽ�棨չʾ�������
	PointCloud<PointXYZ>::Ptr ext_cloud(new PointCloud<PointXYZ>);
	PointCloud<PointXYZ>::Ptr ext_cloud_rest(new PointCloud<PointXYZ>);
	visualization::PCLVisualizer::Ptr viewer(new visualization::PCLVisualizer("3d view"));

	int i = sor_cloud->size(), j = 0;
	ExtractIndices<PointXYZ> ext;
	srand((unsigned)time(NULL));//ˢ��ʱ������ӽڵ���Ҫ����ѭ��������
	while (sor_cloud->size()>i*0.3)//����ȡ�ĵ���С��������3/10ʱ������ѭ��
	{
		ext.setInputCloud(sor_cloud);
		sac.segment(*inliner, *coefficients);
		if (inliner->indices.size() == 0)
		{
			break;
		}
		//����������ȡ����*************
		ext.setIndices(inliner);
		ext.setNegative(false);
		ext.filter(*ext_cloud);
		ext.setNegative(true);
		ext.filter(*ext_cloud_rest);
		//*****************************
		*sor_cloud = *ext_cloud_rest;
		stringstream ss;
		ss << "D:\\" << "ext_plane_clouds" << j << ".pcd";//·�����ļ����ͺ�׺
		io::savePCDFileASCII(ss.str(), *ext_cloud);//��ȡ��ƽ�����д��
		int *rgb = rand_rgb();//�������0-255����ɫֵ
		visualization::PointCloudColorHandlerCustom<PointXYZ>rgb1(ext_cloud, rgb[0], rgb[1], rgb[2]);//��ȡ��ƽ�治ͬ��ɫչʾ
		delete[]rgb;
		viewer->addPointCloud(ext_cloud, rgb1, ss.str());
		j++;
	}
	viewer->spinOnce(1000);
	//--------------------


	//ŷʽ����
	vector<PointIndices>ece_inlier;
	search::KdTree<PointXYZ>::Ptr tree(new search::KdTree<PointXYZ>);
	EuclideanClusterExtraction<PointXYZ> ece;
	ece.setInputCloud(sor_cloud);
	ece.setClusterTolerance(0.5);	//ece.setClusterTolerance(0.02);
	ece.setMinClusterSize(5);		//ece.setMinClusterSize(100);
	ece.setMaxClusterSize(200);		//ece.setMaxClusterSize(20000);
	ece.setSearchMethod(tree);
	ece.extract(ece_inlier);

	//������չʾ
//	int j = 0;
//	visualization::PCLVisualizer::Ptr viewer2(new visualization::PCLVisualizer("Result of EuclideanCluster"));
//	srand((unsigned)time(NULL));

	//����������������Ҫ���Ŀ��Ϊ0, �򷵻�һ���������Ĭ��ֵ
	cout << "number of objects��" << ece_inlier.size() << endl;
	if (ece_inlier.size() < 1)
	{
		objDetected.push_back(PointXYZ(0.0f, -1.0f, 0.0f));
		return objDetected;
	}

	for (int i = 0; i < ece_inlier.size(); i++)
	{
		PointCloud<PointXYZ>::Ptr cloud_copy(new PointCloud<PointXYZ>);
		vector<int> ece_inlier_ext = ece_inlier[i].indices;
		copyPointCloud(*sor_cloud, ece_inlier_ext, *cloud_copy);//����������ȡ��������

//		stringstream ss1;
//		ss1 << "D:\\" << "EuclideanCluster_clouds" << j << ".pcd";
//		io::savePCDFileASCII(ss1.str(), *ext_cloud);//ŷʽ������д��
//		int *rgb1 = rand_rgb();
//		visualization::PointCloudColorHandlerCustom<PointXYZ>rgb2(cloud_copy, rgb1[0], rgb1[1], rgb1[2]);
//		delete[]rgb1;
//		viewer2->addPointCloud(cloud_copy, rgb2, ss1.str());
//		j++;

		//������
		PointXYZ centroid = PointXYZ(0.0f, 0.0f, 0.0f);
		for (int cnt = 0; cnt < cloud_copy->points.size(); cnt++)
		{
			centroid.x += cloud_copy->points[cnt].x;
			centroid.y += cloud_copy->points[cnt].y;
			centroid.z += cloud_copy->points[cnt].z;
		}
		centroid.x = centroid.x / cloud_copy->points.size();
		centroid.y = centroid.y / cloud_copy->points.size();
		centroid.z = centroid.z / cloud_copy->points.size();

		if (i > 0)
		{
			if (nPtMax < cloud_copy->points.size())
			{
				nPtMax = cloud_copy->points.size();
				PointXYZ temp = objDetected[0];
				objDetected[0] = centroid;
				objDetected.push_back(temp);
			}
			else
			{
				objDetected.push_back(centroid);
			}

		}
		else
		{
			nPtMax = cloud_copy->points.size();
			objDetected.push_back(centroid);
		}
	}

	//	viewer2->spin();
	cout << "nPtMax: " << nPtMax << endl;
	return objDetected;

}
*/