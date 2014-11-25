//error_symmetry.cpp
//Subscribes to the pointcloud and publishes the area difference between left and right of X-axis
//Author: Balakumar Sundaralingam
//b.sundralingam@utah.edu

#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>

using namespace std;
ros::Publisher error_yaw;
void callback(const sensor_msgs::PointCloud2ConstPtr& input_pcl);
float area_difference(pcl::PointCloud<pcl::PointXYZ> in_cloud);
int main(int argc,char** argv)
{
	ros::init(argc,argv,"error_symmetry");
	ros::NodeHandle n;
	ros::Subscriber pcl_sub=n.subscribe("laser_pcl",1,callback);
	error_yaw=n.advertise<std_msgs::Float32>("error/symmetry",100);
	ros::spin();
	return(0);
}
void callback(const sensor_msgs::PointCloud2ConstPtr& input_pcl)
{
	pcl::PCLPointCloud2* cloud=new pcl::PCLPointCloud2;
	pcl::PointCloud<pcl::PointXYZ> converted_cloud;
	pcl_conversions::toPCL(*input_pcl,*cloud);
	pcl::fromPCLPointCloud2(*cloud,converted_cloud);
	float a_diff=area_difference(converted_cloud);
	//float error=error_area(a_diff);
	
	std_msgs::Float32 error_pub;
	error_pub.data=a_diff;
	error_yaw.publish(error_pub);
}
float area_difference(pcl::PointCloud<pcl::PointXYZ> in_cloud)
{
	float area_right=0,area_left=0;
	for(int i=0;i<in_cloud.width;i++)
	{
		if(in_cloud[i].y>0)
		{
			area_left=area_left+in_cloud[i].y;
		}
		else
		{
			area_right=area_right+in_cloud[i].y;
		}
	}
	if(area_right>area_left/10)
	{
		//area_left=-area_left;
	}
	if(area_left>area_right/10)
	{
		//area_right=-area_right;
	}		
	float ar_diff=area_right+area_left;
	return(ar_diff);
}
