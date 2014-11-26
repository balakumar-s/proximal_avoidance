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
void fl_e_callback(const std_msgs::Float32& flE);
void fr_e_callback(const std_msgs::Float32& frE);
void bl_e_callback(const std_msgs::Float32& blE);
void br_e_callback(const std_msgs::Float32& brE);
void control_function();

int main(int argc,char** argv)
{
	ros::init(argc,argv,"motor_input");
	ros::NodeHandle n;
	ros::Rate loop_rate(50);
	
	ros::Subscriber joy_sub=n.subscribe("joy",1,joyCallback);
	//if(swtch==1)
	//{
	ros::Subscriber fl_e_sub=n.subscribe("holobot/fl_error",100,fl_e_callback);
	ros::Subscriber fr_e_sub=n.subscribe("holobot/fr_error",100,fr_e_callback);
	ros::Subscriber bl_e_sub=n.subscribe("holobot/bl_error",100,bl_e_callback);
	ros::Subscriber br_e_sub=n.subscribe("holobot/br_error",100,br_e_callback);
	//}
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

void fl_e_callback(const std_msgs::Float32& flE)
{
	fl_e=flE.data;
}
void fr_e_callback(const std_msgs::Float32& frE)
{
	fr_e=frE.data;
}
void bl_e_callback(const std_msgs::Float32& blE)
{
	bl_e=blE.data;
}
void br_e_callback(const std_msgs::Float32& brE)
{
	br_e=brE.data;
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

	//ROS_INFO("control loop");
	std_msgs::Float32 fl,fr,bl,br;
	//if(swtch==1)
	//{
		if (joy_x_>k_high && ((joy_y_>k_low)&&(joy_y_<k_high)) && (k_low<joy_yaw_<k_high)&&swtch==1)
		{  		//ROS_INFO("moving forward");
			//forward
	 		key=1;

	 		fl.data=fl_e+joy_x;
	 		fr.data=fr_e+joy_x;
	 		bl.data=bl_e+joy_x;
	 		br.data=br_e+joy_x;
		}
		else if(joy_x_<k_low && ((joy_y_>k_low)&&(joy_y_<k_high)) && (k_low<joy_yaw_<k_high)&&swtch==1)
		{
		//reverse  
		  	key=2;

	 		fl.data=fl_e+joy_x;
	 		fr.data=fr_e+joy_x;
	 		bl.data=bl_e+joy_x;
	 		br.data=br_e+joy_x;
		}
		else if(((joy_x_>k_low)&&(joy_x_<k_high)) && (joy_y_>k_high) && (k_low<joy_yaw_<k_high)&&swtch==1)
		{
		//left  
		 	key=3;
			
			fl.data=fl_e+joy_y;
	 		fr.data=fr_e-joy_y;
	 		bl.data=bl_e-joy_y;
	 		br.data=br_e+joy_y;
		}
		else if(((joy_x_>k_low)&&(joy_x_<k_high)) && (joy_y_<k_low) && (k_low<joy_yaw_<k_high)&&swtch==1)
		{
		 //right  
		  	key=4;
		  	
		  	fl.data=fl_e+joy_y;
	 		fr.data=fr_e-joy_y;
	 		bl.data=bl_e-joy_y;
	 		br.data=br_e+joy_y;
		}
		else if((k_low<joy_x_<k_high) && (k_low<joy_y_<k_high) && (joy_yaw_>k_high)&&swtch==1)
		{
		 //CCW
		  	key=5;	
		  	fl.data=fl_e-joy_yaw;
	 		fr.data=fr_e+joy_yaw;
	 		bl.data=bl_e-joy_yaw;
	 		br.data=br_e+joy_yaw;
		}
		else if((k_low<joy_x_<k_high) && (k_low<joy_y_<k_high) && (joy_yaw_<k_low)&&swtch==1)
		{
		//CW
		  key=6;
		  	fl.data=fl_e-joy_yaw;
	 		fr.data=fr_e+joy_yaw;
	 		bl.data=bl_e-joy_yaw;
	 		br.data=br_e+joy_yaw;
		}
		else if((joy_x_>k_high) && (joy_y_>k_high) && (k_low<joy_yaw_<k_high)&&swtch==1)
		{
		//diagonal left_forward
			key=7;
		 	fl.data=fl_e+joy_y+joy_x;
		 	fr.data=fr_e;
		 	bl.data=bl_e;
		 	br.data=br_e+joy_y+joy_x;		
		}
		else if((joy_x_<k_low) && (joy_y_<k_low) && (k_low<joy_yaw_<k_high)&&swtch==1)
		{
		//diagonal right_reverse
		 key=8;
			fl.data=fl_e+joy_y+joy_x;
		 	fr.data=fr_e;
		 	bl.data=bl_e;
		 	br.data=br_e+joy_y+joy_x;			
			}
		else if((joy_x_>k_high) && (joy_y_<k_low) && (k_low<joy_yaw_<k_high)&&swtch==1)
		{
		//diagonal right_forward
		key=9;	
			fl.data=fl_e;//-joy_y;
	 		fr.data=fr_e-joy_y+joy_x;
	 		bl.data=bl_e-joy_y+joy_x;
	 		br.data=br_e;//+joy_y;

			
		}
		else if((joy_x_<k_low) && (joy_y_>k_high) && (k_low<joy_yaw_<k_high)&&swtch==1)
		{
		//diagonal left_reverse
		 key=10;

			fl.data=fl_e;//-joy_y;
		 	fr.data=fr_e-joy_y+joy_x;
		 	bl.data=bl_e-joy_y+joy_x;
		 	br.data=br_e;//+joy_y;
		}
		else if(swtch==1)
		{
			fl.data=fl_e;
			fr.data=fr_e;
			bl.data=bl_e;
			br.data=br_e;
		}
		
	
	if(swtch==0)
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

