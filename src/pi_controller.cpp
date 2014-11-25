//pi_controller.cpp
//subscribes to error/x and error/symmetry and applies a proportional + integral controller and publihes the velocities for individual motors.

//Author: Balakumar Sundaralingam
//b.sundralingam@utah.edu
#include <ros/ros.h>
#include <std_msgs/Float32.h>
using namespace std;
ros::Publisher fl_pub,fr_pub,bl_pub,br_pub;
float gain_x=350;
float gain_y=0;
float i_gain=0.00;
float gain_yaw=0;
float x_i_error=0;
float y_i_error=0;
float x_fl=0,x_fr=0,x_bl=0,x_br=0;
float y_fl=0,y_fr=0,y_bl=0,y_br=0;
float yaw_fl=0,yaw_fr=0,yaw_bl=0,yaw_br=0;

void x_callback(const std_msgs::Float32& feed_x);
void y_callback(const std_msgs::Float32& feed_y);
int main(int argc,char** argv)
{
	ros::init(argc,argv,"pi_controller");
	ros::NodeHandle n;
	ros::Subscriber c_x_sub=n.subscribe("error/x",1,x_callback);
	ros::Subscriber c_y_sub=n.subscribe("error/symmetry",1,y_callback);
	fl_pub=n.advertise<std_msgs::Float32>("holobot/fl_error",100);
	fr_pub=n.advertise<std_msgs::Float32>("holobot/fr_error",100);
	bl_pub=n.advertise<std_msgs::Float32>("holobot/bl_error",100);
	br_pub=n.advertise<std_msgs::Float32>("holobot/br_error",100);
	
	ros::spin();
	return(0);
}

void x_callback(const std_msgs::Float32& feed_x)
{
	float error=feed_x.data;
	x_i_error=x_i_error+i_gain*error;
	float input=gain_x*error+x_i_error;
	x_fl=x_fr=x_bl=x_br=input;
}
void y_callback(const std_msgs::Float32& feed_y)
{
	float error=feed_y.data;
	y_i_error=y_i_error+i_gain*error;
	float input=gain_y*error+y_i_error;
	//std_msgs::Float32 fl,fr,bl,br;
	y_fl=y_br=input;
	y_fr=y_bl=-input;
	yaw_fl=yaw_bl=-gain_yaw*error;
	yaw_fr=yaw_br=error*gain_yaw;
	//x_fl=0;x_fr=0;x_bl=0;x_br=0;



	std_msgs::Float32 fl,fr,bl,br;
	fl.data=x_fl+y_fl+yaw_fl;
	fr.data=x_fr+y_fr+yaw_fr;
	bl.data=x_bl+y_bl+yaw_bl;
	br.data=x_br+y_br+yaw_br;
	fl_pub.publish(fl);
	fr_pub.publish(fr);
	bl_pub.publish(bl);
	br_pub.publish(br);
}
