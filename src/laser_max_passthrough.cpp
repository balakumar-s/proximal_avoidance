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

laser_geometry::LaserProjection projector_;
ros::Publisher pcl_pub;
sensor_msgs::PointCloud2 cloud,pass_cloud;

void callback (const sensor_msgs::LaserScan::ConstPtr& scan_in)
{
		
	//convert laserscan to PCL2
    projector_.projectLaser(*scan_in, cloud);
    //initiating all the variables
    pcl::PCLPointCloud2* cloud_from_sensor = new pcl::PCLPointCloud2;
    pcl::PointCloud<pcl::PointXYZ>::Ptr input_cloud_pcl (new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered (new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr centroid_pcl (new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PCLPointCloud2* centroid_pclpoint=new pcl::PCLPointCloud2;
    sensor_msgs::PointCloud2 output_centroid;

	pcl_conversions::toPCL(cloud,*cloud_from_sensor);
	pcl::fromPCLPointCloud2(*cloud_from_sensor,*input_cloud_pcl);
	//input_cloud_pcl is the input sensor data which is PCL1 and can be used 
	//with point cloud libraries.

	//passthrough filter
	//pcl::io::savePCDFileASCII("/home/bala/Dropbox/matlab/test.pcd",*input_cloud_pcl);
	pcl::PassThrough<pcl::PointXYZ> pass;
	pass.setInputCloud(input_cloud_pcl);
	pass.setFilterFieldName("x");
	pass.setFilterLimits(-1.5,2);
	//pass.setKeepOrganized (true); 
	//pass.setUserFilterValue(4);
	pass.filter(*cloud_filtered);

	pcl::PassThrough<pcl::PointXYZ> pass_y;
	pass_y.setInputCloud(cloud_filtered);
	pass_y.setFilterFieldName("y");
	pass_y.setFilterLimits(-3,3);
  	//pass_y.setKeepOrganized (true); 
	//pass_y.setUserFilterValue(4);
	pass_y.filter(*cloud_filtered);

	
	//pcl::io::savePCDFileASCII("/home/bala/Dropbox/matlab/test_pass.pcd",*cloud_filtered);



	//convert PCL1 to sensor_msgs and publish as a ros topic.
	pcl::toPCLPointCloud2(*cloud_filtered,*centroid_pclpoint);
  	pcl_conversions::fromPCL(*centroid_pclpoint,output_centroid);
    pcl_pub.publish(output_centroid);
  
}
int main(int argc,char**argv)
{
	ros::init(argc,argv,"laser_to_pcl");
	ros::NodeHandle n;
	pcl_pub=n.advertise<sensor_msgs::PointCloud2>("laser_pcl",1);
    ros::Subscriber laser_sub = n.subscribe("scan",1,callback);
	ros::spin();
    return(0);
}
