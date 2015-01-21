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
int lft=0,fw=0,bck=0,rt=0,cw=0,ccw=0,dir=0;
float fl_e=0,fr_e=0,bl_e=0,br_e=0;
int swtch=0;
float joy_x_=0,joy_y_=0,joy_yaw_=0,joy_x=0,joy_y=0,joy_yaw=0;
ros::Publisher fl_pub,fr_pub,bl_pub,br_pub;
int tim=0;
void joyCallback(const sensor_msgs::Joy& joy_msg_in);
void control_function();

int main(int argc,char** argv)
{
	if(argc==1)
	{
		tim=1;
	}
	else
	{
		tim=atoi(argv[1]);
		
	}
	ros::init(argc,argv,"motor_input");
	ros::NodeHandle n;
	ros::Rate loop_rate(1000);
	//tim=argv;
	
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
	if(joy_msg_in.buttons[7]==1)
	{
		ROS_INFO("start %d",tim);
		swtch=1;
	}
	if(joy_msg_in.buttons[6]==1)
	{
		ROS_INFO("stop");
		swtch=0;
	}
	if(joy_msg_in.buttons[3]==1)
	{
		ROS_INFO("forward");
		fw=1;
		bck=0;
		lft=0;
		rt=0;
		cw=0;
		ccw=0;
		dir=1;


	}
	if(joy_msg_in.buttons[2]==1)
	{
		ROS_INFO("left");
		fw=1;
		bck=0;
		lft=0;
		rt=0;
		cw=0;
		ccw=0;
		dir=3;
	}
	if(joy_msg_in.buttons[0]==1)
	{
		ROS_INFO("back");
		fw=1;
		bck=0;
		lft=0;
		rt=0;
		cw=0;
		ccw=0;
		dir=2;
	}
	if(joy_msg_in.buttons[1]==1)
	{
		ROS_INFO("right");
		fw=1;
		bck=0;
		lft=0;
		rt=0;
		cw=0;
		ccw=0;
		dir=4;
	}

	if(joy_msg_in.buttons[5]==1)
	{
		ROS_INFO("CW");
		fw=1;
		bck=0;
		lft=0;
		rt=0;
		cw=0;
		ccw=0;
		dir=5;
	}
	if(joy_msg_in.buttons[4]==1)
	{
		ROS_INFO("CCW");
		fw=1;
		bck=0;
		lft=0;
		rt=0;
		cw=0;
		ccw=0;
		dir=6;
	}
}

void control_function()
{

	float forw_back=joy_x;
	float left_right=joy_y;
	float cw_ccw=joy_yaw;
	std_msgs::Float32 fl,fr,bl,br;
	if(swtch==1)
	{
		switch (dir)
		{
		case 0:
		
			fl.data=0;
			fr.data=0;
			bl.data=0;
			br.data=0;
			fl_pub.publish(fl);
			fr_pub.publish(fr);
			bl_pub.publish(bl);
			br_pub.publish(br);
			
		break;
		case 1:
		
			fl.data=-100;
			fr.data=-100;
			bl.data=-100;
			br.data=-100;
			fl_pub.publish(fl);
			fr_pub.publish(fr);
			bl_pub.publish(bl);
			br_pub.publish(br);
			ros::Duration(tim).sleep();
			dir=0;
		break;
		case 2:
		
			fl.data=100;
			fr.data=100;
			bl.data=100;
			br.data=100;
			fl_pub.publish(fl);
			fr_pub.publish(fr);
			bl_pub.publish(bl);
			br_pub.publish(br);
			ros::Duration(tim).sleep();
			dir=0;
		break;
		case 3:
		
			fl.data=100;
			fr.data=-100;
			bl.data=-100;
			br.data=100;
			fl_pub.publish(fl);
			fr_pub.publish(fr);
			bl_pub.publish(bl);
			br_pub.publish(br);
			ros::Duration(tim).sleep();
			dir=0;
		break;
		case 4:
		
			fl.data=-100;
			fr.data=100;
			bl.data=100;
			br.data=-100;
			fl_pub.publish(fl);
			fr_pub.publish(fr);
			bl_pub.publish(bl);
			br_pub.publish(br);
			ros::Duration(tim).sleep();
			dir=0;
		break;
		case 5:
		
			fl.data=-100;
			fr.data=100;
			bl.data=-100;
			br.data=100;
			fl_pub.publish(fl);
			fr_pub.publish(fr);
			bl_pub.publish(bl);
			br_pub.publish(br);
			ros::Duration(tim).sleep();
			dir=0;
		break;
		case 6:
		
			fl.data=100;
			fr.data=-100;
			bl.data=100;
			br.data=-100;
			fl_pub.publish(fl);
			fr_pub.publish(fr);
			bl_pub.publish(bl);
			br_pub.publish(br);
			ros::Duration(tim).sleep();
			dir=0;
		break;

	}
	}
	else
	{
		fl.data=0;
		fr.data=0;
		bl.data=0;
		br.data=0;
		fl_pub.publish(fl);
		fr_pub.publish(fr);
		bl_pub.publish(bl);
		br_pub.publish(br);
	}

 }

