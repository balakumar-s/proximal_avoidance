//laser_passthrough.cpp
//Subscribes to laserscan and publishes a pointcloud with a passthrough limits
//Author: Balakumar Sundaralingam

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <sensor_msgs/PointCloud2.h>
#include <laser_geometry/laser_geometry.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/filters/passthrough.h>

#define THRESH 6
laser_geometry::LaserProjection projector_;
ros::Publisher pcl_pub;
sensor_msgs::PointCloud2 cloud;
void callback (const sensor_msgs::LaserScan::ConstPtr& scan_in)
{
		
	sensor_msgs::LaserScan filtered_scan;
	filtered_scan=*scan_in;
	int i=0;
	int readings=(filtered_scan.angle_max-filtered_scan.angle_min)/filtered_scan.angle_increment;
	while(i<readings)
	{
		if(filtered_scan.ranges[i]>THRESH)
		{
			filtered_scan.ranges[i]=THRESH;
		}
		i++;
	}
	//convert laserscan to PCL2
    projector_.projectLaser(filtered_scan, cloud);
    pcl_pub.publish(cloud);
  
}
int main(int argc,char**argv)
{
	ros::init(argc,argv,"laser_to_pcl");
	ros::NodeHandle n;
	pcl_pub=n.advertise<sensor_msgs::PointCloud2>("laser_pcl",1);
    ros::Subscriber laser_sub = n.subscribe("/vrep/scan",1,callback);
	ros::spin();
    return(0);
}
