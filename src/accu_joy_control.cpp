//motor_input.cpp
//Combines the controller input and joystick input
//Author: Balakumar Sundaralingam

#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <sensor_msgs/Joy.h>

float key=0;
float joy_gain=100;
float factor=10;
float k_high=15,k_low=5;

float fl_e=0,fr_e=0,bl_e=0,br_e=0;
int swtch=0;
float joy_x_=0,joy_y_=0,joy_yaw_=0,joy_x=0,joy_y=0,joy_yaw=0;
ros::Publisher fl_pub,fr_pub,bl_pub,br_pub;

void joyCallback(const sensor_msgs::Joy& joy_msg_in);
void control_function();

int main(int argc,char** argv)
{
	ros::init(argc,argv,"motor_input");
	ros::NodeHandle n;
	ros::Rate loop_rate(50);
	
	ros::Subscriber joy_sub=n.subscribe("joy",1,joyCallback);
	fl_pub=n.advertise<std_msgs::Float32>("holobot/fl",100);
	fr_pub=n.advertise<std_msgs::Float32>("holobot/fr",100);
	bl_pub=n.advertise<std_msgs::Float32>("holobot/bl",100);
	br_pub=n.advertise<std_msgs::Float32>("holobot/br",100);
	while(ros::ok())
	{
	control_function();
	
	ros::spinOnce();
	loop_rate.sleep();
	}
	return(0);
}


void joyCallback(const sensor_msgs::Joy& joy_msg_in)
{
	joy_x_=factor*(1+joy_msg_in.axes[1]);//left stick up-down
	joy_y_=factor*(1+joy_msg_in.axes[0]);//left stick left-right
	joy_yaw_=factor*(1+joy_msg_in.axes[2]);//right stick left-right
	
	joy_x=joy_gain*joy_msg_in.axes[1];//left stick up-down
	joy_y=joy_gain*joy_msg_in.axes[0];//left stick left-right
	joy_yaw=joy_gain*joy_msg_in.axes[2];//right stick left-right
	if(joy_msg_in.buttons[0]==1)
	{
		ROS_INFO("pressed A");
		swtch=1;
	}
	if(joy_msg_in.buttons[1]==1)
	{
		ROS_INFO("pressed B");
		swtch=0;
	}
	//ROS_INFO("obtained joystick values");
}

void control_function()
{

	float forw_back=joy_x;
	float left_right=joy_y;
	float cw_ccw=joy_yaw;
	std_msgs::Float32 fl,fr,bl,br;
	float x,y,z;
	x=abs(joy_x);
	y=abs(joy_y);
	z=abs(joy_yaw);
	int dead=0;
	if(x>25||y>25||z>25)
	{
		dead=1;
	//	ROS_INFO("dead %f",z);
	}
		
	if((swtch==1) && (dead==1))
	{
	//	ROS_INFO("frward");
	fl.data=+joy_x-joy_y-joy_yaw;
	fr.data=+joy_x+joy_y+joy_yaw;
	bl.data=+joy_x+joy_y-joy_yaw;
	br.data=+joy_x-joy_y+joy_yaw;
	}	
	else
	{
		fl.data=0;
		fr.data=0;
		bl.data=0;
		br.data=0;
	}
	fl_pub.publish(fl);
	fr_pub.publish(fr);
	bl_pub.publish(bl);
	br_pub.publish(br);
	//ROS_INFO("published");
}

