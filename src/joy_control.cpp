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

	//ROS_INFO("control loop");
	std_msgs::Float32 fl,fr,bl,br;
	//if(swtch==1)
	//{
		if (joy_x_>k_high && ((joy_y_>k_low)&&(joy_y_<k_high)) && (k_low<joy_yaw_<k_high)&&swtch==1)
		{  		//ROS_INFO("moving forward");
			//forward
	 		key=1;

	 		fl.data=joy_x;
	 		fr.data=joy_x;
	 		bl.data=joy_x;
	 		br.data=joy_x;
		}
		else if(joy_x_<k_low && ((joy_y_>k_low)&&(joy_y_<k_high)) && (k_low<joy_yaw_<k_high)&&swtch==1)
		{
		//reverse  
		  	key=2;

	 		fl.data=joy_x;
	 		fr.data=joy_x;
	 		bl.data=joy_x;
	 		br.data=joy_x;
		}
		else if(((joy_x_>k_low)&&(joy_x_<k_high)) && (joy_y_>k_high) && (k_low<joy_yaw_<k_high)&&swtch==1)
		{
		//left  
		 	key=3;
			
			fl.data=-joy_y;
	 		fr.data=joy_y;
	 		bl.data=joy_y;
	 		br.data=-joy_y;
		}
		else if(((joy_x_>k_low)&&(joy_x_<k_high)) && (joy_y_<k_low) && (k_low<joy_yaw_<k_high)&&swtch==1)
		{
		 //right  
		  	key=4;
		  	
		  	fl.data=-joy_y;
	 		fr.data=joy_y;
	 		bl.data=joy_y;
	 		br.data=-joy_y;
		}
		else if((k_low<joy_x_<k_high) && (k_low<joy_y_<k_high) && (joy_yaw_>k_high)&&swtch==1)
		{
		 //CCW
		  	key=5;	
		  	fl.data=-joy_yaw;
	 		fr.data=joy_yaw;
	 		bl.data=-joy_yaw;
	 		br.data=joy_yaw;
		}
		else if((k_low<joy_x_<k_high) && (k_low<joy_y_<k_high) && (joy_yaw_<k_low)&&swtch==1)
		{
		//CW
		  key=6;
		  	fl.data=-joy_yaw;
	 		fr.data=joy_yaw;
	 		bl.data=-joy_yaw;
	 		br.data=joy_yaw;
		}
		else if((joy_x_>k_high) && (joy_y_>k_high) && (k_low<joy_yaw_<k_high)&&swtch==1)
		{
		//diagonal left_forward
			key=7;
		float velocity=joy_y+joy_x;
		 if(velocity>100)
		 {
		 	velocity=100;
		 }
		 if(velocity<-100)
		 {
		 	velocity=-100;
		 }
			fl.data=0;//-joy_y;
	 		fr.data=velocity;
	 		bl.data=velocity;
	 		br.data=0;//+joy_y;	
		}
		else if((joy_x_<k_low) && (joy_y_<k_low) && (k_low<joy_yaw_<k_high)&&swtch==1)
		{
		//diagonal right_reverse
		 key=8;
		 float velocity=joy_y+joy_x;
		 if(velocity>100)
		 {
		 	velocity=100;
		 }
		 if(velocity<-100)
		 {
		 	velocity=-100;
		 }

			fl.data=0;//-joy_y;
		 	fr.data=velocity;
		 	bl.data=velocity;
		 	br.data=0;//+joy_y;		
			}
		else if((joy_x_>k_high) && (joy_y_<k_low) && (k_low<joy_yaw_<k_high)&&swtch==1)
		{
		//diagonal right_forward
		key=9;	
		float velocity=-joy_y+joy_x;
		 if(velocity>100)
		 {
		 	velocity=100;
		 }
		 if(velocity<-100)
		 {
		 	velocity=-100;
		 }


		 	fl.data=velocity;
		 	fr.data=0;
		 	bl.data=0;
		 	br.data=velocity;	
		 	

			
		}
		else if((joy_x_<k_low) && (joy_y_>k_high) && (k_low<joy_yaw_<k_high)&&swtch==1)
		{
		//diagonal left_reverse
		 key=10;
		 float velocity=-joy_y+joy_x;
		 if(velocity>100)
		 {
		 	velocity=100;
		 }
		 if(velocity<-100)
		 {
		 	velocity=-100;
		 }
		 
			fl.data=velocity;
		 	fr.data=0;
		 	bl.data=0;
		 	br.data=velocity;	

		}
		else if(swtch==1)
		{
			fl.data=0;
			fr.data=0;
			bl.data=0;
			br.data=0;
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

