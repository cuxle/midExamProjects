#include "lidarAnalysis.h"
#include "appconfig.h"
#include "singleton.h"
#include <QDebug>

lidarAnalysis::lidarAnalysis()
{
    // get settings parameter
    // 1. m_radius
    // 2
    // 2.1 ece.setClusterTolerance(0.5);
    // 2.2 ece.setMinClusterSize(5);
    // 2.3 ece.setMaxClusterSize(200);		//ece.setMaxClusterSize(20000);
    AppConfig &m_config = Singleton<AppConfig>::GetInstance();
    m_radius = m_config.m_radius;
    m_MinClusterSize = m_config.m_minClusterSize;
    m_MaxClusterSize = m_config.m_maxClusterSize;
    m_clusterTolerance = m_config.m_clusterTolerance;
    qDebug() << __func__ << __LINE__ << "m_radius:" << m_radius;
    qDebug() << __func__ << __LINE__ << "m_minClusterSize" << m_MinClusterSize;
    qDebug() << __func__ << __LINE__ << "m_maxClusterSize" << m_MaxClusterSize;
    qDebug() << __func__ << __LINE__ << "m_clusterTolerance:" << m_clusterTolerance;
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

int *lidarAnalysis::rand_rgb() {//随机产生颜色
	int *rgb = new int[3];
	rgb[0] = rand() % 255;
	rgb[1] = rand() % 255;
	rgb[2] = rand() % 255;
	return rgb;
}

//重置考试参数
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

//设置考试开始
bool lidarAnalysis::setExamStart(float x, float y)
{
	//如果标志位已经是考试中，则无需设置
	if (m_inExam == true)
	{
		return true;
	}
	else
	{
		if (getRegionID(x, y) > 0)
		{
			//学生越界犯规 无法开始考试
			return false;
		}
		else
        {
            m_inExam = true;
			return true;
		}
	}

}

//设置考试结束标志
bool lidarAnalysis::setExamEnd()
{
	//如果标志位已经是考试结束，则无需设置
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

//返回值 0:未开始考试  1：考试进行中 2：考试正常结束 3：考生犯规
int lidarAnalysis::tracking(PointXYZ ptPos)
{
    //在考试中才分析点的位置 不在考试区域内ptPos默认给个(0,-1)
    if (m_inExam)
    {
        int curID = getRegionID(ptPos.x, ptPos.y);

        //考生进入考试区域内才开始计时
        if (curID > 0 && m_prevRegionID == 0)
        {
            m_start = clock();
            m_prevRegionID = curID;
            m_stepIdx++;
        }

        //进入考试流程
        if (m_stepIdx > 0)
        {
            if (curID == 0)
            {
                //连续三帧出区域，表示考试结束
                if (m_OutCnt == 0)
                {
                    m_finish = clock();
                }

                //只有前一帧的坐标靠近边界区域时才开始计数 防止中间跟踪丢失3帧以上出现误判
                if (ptPos.y >= m_yBorderMax*0.8 || ptPos.x <= m_xBorderMin*0.6 || ptPos.x >= m_xBorderMax*0.6)
                {
                    m_OutCnt++;
                }

                if (m_OutCnt == 3)
                {
                    if (m_flagStatus[0] && m_flagStatus[1] && m_flagStatus[2] && m_flagStatus[3] && m_flagStatus[4])
                    {
                        //如果5个杆子都绕过了
                        m_duration = (double)(m_finish - m_start) / CLOCKS_PER_SEC;

                        if (abs(m_PointLast.y - m_yBorderMax) < abs(m_PointLast.x - m_xBorderMin) && abs(m_PointLast.y - m_yBorderMax) < abs(m_PointLast.x - m_xBorderMax))
                        {
                            //如果出有效区域前距离底线近 则正常考试结束
                            return 2;
                        }
                        else
                        {
                            //虽然绕过所有的杆 但是最后没有从底线出去
                            return 3;
                        }
                    }
                    else
                    {
                        //犯规结束
                        m_duration = (double)(m_finish - m_start) / CLOCKS_PER_SEC;
                        return 3;
                    }
                }
            }
            else if (curID < 3)
            {
                m_PointLast = ptPos; //备份一下在考试区域内的点位
                //在1-2区域内不必区分路径,考生仍然可以更换路径
                if (m_prevRegionID != curID)
                {
                    m_prevRegionID = curID;
                }
                m_OutCnt = 0;

            }
            else
            {
                m_PointLast = ptPos; //备份一下在考试区域内的点位
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

                //走不同的标准轨迹
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

	//用PCLPointCloud2解决问题
	PCLPointCloud2::Ptr cloud(new pcl::PCLPointCloud2());
	toPCLPointCloud2(*cloudPtr, *cloud);
	
	//体素化下采样
	VoxelGrid<pcl::PCLPointCloud2> vox;
	pcl::PCLPointCloud2::Ptr vox_cloud(new pcl::PCLPointCloud2());
	vox.setInputCloud(cloud);
	vox.setLeafSize(0.01, 0.01, 0.01);
	vox.filter(*vox_cloud);
//	cout << "After Voxel Grid：" << vox_cloud->fields.size() << endl;
	
	//去除噪声点
	StatisticalOutlierRemoval<pcl::PCLPointCloud2> sor;
	pcl::PCLPointCloud2::Ptr sor_cloud_filtered(new pcl::PCLPointCloud2());
	sor.setMeanK(10);
	sor.setInputCloud(vox_cloud);
	sor.setStddevMulThresh(0.2);
	sor.filter(*sor_cloud_filtered);
//	cout << "After Statistical Outlie rRemoval：" << sor_cloud_filtered->fields.size() << endl;

	//转换为原始格式输出
	PointCloud<PointXYZ>::Ptr sor_cloud(new PointCloud<PointXYZ>);
	fromPCLPointCloud2(*sor_cloud_filtered, *sor_cloud);
    qDebug() << "After Statistical Outlie rRemoval:" << sor_cloud->points.size();

	//如果反射点小于5, 认为区域内没有目标则返回一个默认的考试区域外坐标
	if (sor_cloud->points.size() < 5)
	{
		objDetected.push_back(PointXYZ(0.0f, -1.0f, 0.0f));
		return objDetected;
	}

	//欧式聚类
	vector<PointIndices>ece_inlier;
	search::KdTree<PointXYZ>::Ptr tree(new search::KdTree<PointXYZ>);
	EuclideanClusterExtraction<PointXYZ> ece;
	ece.setInputCloud(sor_cloud);
    ece.setClusterTolerance(m_clusterTolerance);	//ece.setClusterTolerance(0.02);
    ece.setMinClusterSize(m_MinClusterSize);		//ece.setMinClusterSize(100);
    ece.setMaxClusterSize(m_MaxClusterSize);		//ece.setMaxClusterSize(20000);
	ece.setSearchMethod(tree);
	ece.extract(ece_inlier);

	//聚类结果展示
//	int j = 0;
//	visualization::PCLVisualizer::Ptr viewer2(new visualization::PCLVisualizer("Result of EuclideanCluster"));
//	srand((unsigned)time(NULL));

	//如果聚类出来的满足要求的目标为0, 则返回一个区域外的默认值
    qDebug() << "number of objects:" << ece_inlier.size();
	if (ece_inlier.size() < 1)
	{
		objDetected.push_back(PointXYZ(0.0f, -1.0f, 0.0f));
		return objDetected;
	}

	for (int i = 0; i < ece_inlier.size(); i++)
	{
		PointCloud<PointXYZ>::Ptr cloud_copy(new PointCloud<PointXYZ>);
		vector<int> ece_inlier_ext = ece_inlier[i].indices;
		copyPointCloud(*sor_cloud, ece_inlier_ext, *cloud_copy);//按照索引提取点云数据
		
//		stringstream ss1;
//		ss1 << "D:\\" << "EuclideanCluster_clouds" << j << ".pcd";
//		io::savePCDFileASCII(ss1.str(), *ext_cloud);//欧式聚类结果写出
//		int *rgb1 = rand_rgb();
//		visualization::PointCloudColorHandlerCustom<PointXYZ>rgb2(cloud_copy, rgb1[0], rgb1[1], rgb1[2]);
//		delete[]rgb1;
//		viewer2->addPointCloud(cloud_copy, rgb2, ss1.str());
//		j++;

		//求质心
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

    // 2022.4.1 wei
    //前面不变，直到return objDetected;之前添加限定

    //对检测到的最大目标再次校验
    //根据距离加权系数约束检测目标的最小尺寸
    float fDist = abs(m_yBorderMax - objDetected[0].y);
    float fRatio = fDist / 5.0f * m_ratio + 1.0f;
    //如果检测到的目标小于加权后的最小目标值,则认为是虚假目标，进行滤除
    if (nPtMax < fRatio * m_MinClusterSize)
    {
        objDetected[0].x = 0.0f;
        objDetected[0].y = -1.0f;
        objDetected[0].z = 0.0f;
    }

    return objDetected;

}

/*
std::vector<PointXYZ> lidarAnalysis::objectDetection(PointCloud<PointXYZ>::Ptr cloudPtr)
{
	vector<PointXYZ> objDetected;
	int nPtMax = 0;

	//体素化下采样
	VoxelGrid<PointXYZ> vox;
	PointCloud<PointXYZ>::Ptr vox_cloud(new PointCloud<PointXYZ>);
	vox.setInputCloud(cloudPtr);
	vox.setLeafSize(0.01, 0.01, 0.01);
	vox.filter(*vox_cloud);
	cout << "After Voxel Grid：" << vox_cloud->points.size() << endl;

	//去除噪声点
	StatisticalOutlierRemoval<PointXYZ> sor;
	PointCloud<PointXYZ>::Ptr sor_cloud(new PointCloud<PointXYZ>);
	sor.setMeanK(10);
	sor.setInputCloud(vox_cloud);
	sor.setStddevMulThresh(0.2);
	sor.filter(*sor_cloud);
	cout << "After Statistical Outlie rRemoval：" << sor_cloud->points.size() << endl;

	//如果反射点小于5, 认为区域内没有目标则返回一个默认的考试区域外坐标
	if (sor_cloud->points.size() < 5)
	{
		objDetected.push_back(PointXYZ(0.0f, -1.0f, 0.0f));
		return objDetected;
	}

	//--------------------
	//平面分割（RANSAC）
	SACSegmentation<PointXYZ> sac;
	PointIndices::Ptr inliner(new PointIndices);
	ModelCoefficients::Ptr coefficients(new ModelCoefficients);
	PointCloud<PointXYZ>::Ptr sac_cloud(new PointCloud<PointXYZ>);
	sac.setInputCloud(sor_cloud);
	sac.setMethodType(SAC_RANSAC);
	sac.setModelType(SACMODEL_PLANE);
	sac.setMaxIterations(100);
	sac.setDistanceThreshold(0.02);

	//提取平面（展示并输出）
	PointCloud<PointXYZ>::Ptr ext_cloud(new PointCloud<PointXYZ>);
	PointCloud<PointXYZ>::Ptr ext_cloud_rest(new PointCloud<PointXYZ>);
	visualization::PCLVisualizer::Ptr viewer(new visualization::PCLVisualizer("3d view"));

	int i = sor_cloud->size(), j = 0;
	ExtractIndices<PointXYZ> ext;
	srand((unsigned)time(NULL));//刷新时间的种子节点需要放在循环体外面
	while (sor_cloud->size()>i*0.3)//当提取的点数小于总数的3/10时，跳出循环
	{
		ext.setInputCloud(sor_cloud);
		sac.segment(*inliner, *coefficients);
		if (inliner->indices.size() == 0)
		{
			break;
		}
		//按照索引提取点云*************
		ext.setIndices(inliner);
		ext.setNegative(false);
		ext.filter(*ext_cloud);
		ext.setNegative(true);
		ext.filter(*ext_cloud_rest);
		//*****************************
		*sor_cloud = *ext_cloud_rest;
		stringstream ss;
		ss << "D:\\" << "ext_plane_clouds" << j << ".pcd";//路径加文件名和后缀
		io::savePCDFileASCII(ss.str(), *ext_cloud);//提取的平面点云写出
		int *rgb = rand_rgb();//随机生成0-255的颜色值
		visualization::PointCloudColorHandlerCustom<PointXYZ>rgb1(ext_cloud, rgb[0], rgb[1], rgb[2]);//提取的平面不同彩色展示
		delete[]rgb;
		viewer->addPointCloud(ext_cloud, rgb1, ss.str());
		j++;
	}
	viewer->spinOnce(1000);
	//--------------------


	//欧式聚类
	vector<PointIndices>ece_inlier;
	search::KdTree<PointXYZ>::Ptr tree(new search::KdTree<PointXYZ>);
	EuclideanClusterExtraction<PointXYZ> ece;
	ece.setInputCloud(sor_cloud);
	ece.setClusterTolerance(0.5);	//ece.setClusterTolerance(0.02);
	ece.setMinClusterSize(5);		//ece.setMinClusterSize(100);
	ece.setMaxClusterSize(200);		//ece.setMaxClusterSize(20000);
	ece.setSearchMethod(tree);
	ece.extract(ece_inlier);

	//聚类结果展示
//	int j = 0;
//	visualization::PCLVisualizer::Ptr viewer2(new visualization::PCLVisualizer("Result of EuclideanCluster"));
//	srand((unsigned)time(NULL));

	//如果聚类出来的满足要求的目标为0, 则返回一个区域外的默认值
	cout << "number of objects：" << ece_inlier.size() << endl;
	if (ece_inlier.size() < 1)
	{
		objDetected.push_back(PointXYZ(0.0f, -1.0f, 0.0f));
		return objDetected;
	}

	for (int i = 0; i < ece_inlier.size(); i++)
	{
		PointCloud<PointXYZ>::Ptr cloud_copy(new PointCloud<PointXYZ>);
		vector<int> ece_inlier_ext = ece_inlier[i].indices;
		copyPointCloud(*sor_cloud, ece_inlier_ext, *cloud_copy);//按照索引提取点云数据

//		stringstream ss1;
//		ss1 << "D:\\" << "EuclideanCluster_clouds" << j << ".pcd";
//		io::savePCDFileASCII(ss1.str(), *ext_cloud);//欧式聚类结果写出
//		int *rgb1 = rand_rgb();
//		visualization::PointCloudColorHandlerCustom<PointXYZ>rgb2(cloud_copy, rgb1[0], rgb1[1], rgb1[2]);
//		delete[]rgb1;
//		viewer2->addPointCloud(cloud_copy, rgb2, ss1.str());
//		j++;

		//求质心
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
