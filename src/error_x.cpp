/*error_x
Subscribes to the pointcloud after passthrough and publishes the error in the X axis.

Author: Balakumar Sundaralingam
b.sundaralingam@utah.edu
*/
#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>
#include <std_msgs/Float32.h>
using namespace std;

ros::Publisher y_pub,x_pub;
float X=0,Y=0;
//void call_x(const std_msgs::Float32& c_x)
//{
//X=c_x.data;
//}
//void call_y(const std_msgs::Float32& c_y)
//{
//Y=c_y.data;
//}

void callback(const sensor_msgs::PointCloud2ConstPtr& input)
{
	pcl::PCLPointCloud2* cloud = new pcl::PCLPointCloud2;
    pcl::PointCloud<pcl::PointXYZ> filtered_cloud;
	pcl_conversions::toPCL(*input,*cloud);
	pcl::fromPCLPointCloud2(*cloud,filtered_cloud);
	/*float y1,y2;
	//float k=25;
	y1=filtered_cloud.points[0].y;
	y2=filtered_cloud.points[filtered_cloud.width-1].y;
	//float controller=k*(x1+x2);
	std_msgs::Float32 control_y;
	control_y.data=y1+y2;
	y_pub.publish(control_y);
	*/
	float x_error;
	//float j=25;
	for(int i=0;i<5;i++)
	{
     	x_error=x_error+filtered_cloud.points[(filtered_cloud.width/2)-5+i].x;
	}
	std_msgs::Float32 control_x;
	control_x.data=(x_error/5)-1;
	x_pub.publish(control_x);


	
}

int main(int argc,char** argv)
{
	ros::init(argc,argv,"feed_x_y");
	ros::NodeHandle n;
	ros::Subscriber pcl_sub=n.subscribe("laser_pcl",1,callback);
	//y_pub=n.advertise<std_msgs::Float32>("control_y",100);
	x_pub=n.advertise<std_msgs::Float32>("error/x",100);
	ros::spin();
	return(0);
}
