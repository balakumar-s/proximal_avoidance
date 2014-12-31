#include <ros/ros.h>
#include <tf/transform_broadcaster.h>


int main(int argc, char** argv)
{
  ros::init(argc, argv, "tf_vrep_holobot");
  ros::NodeHandle node;
  static tf::TransformBroadcaster br;
  tf::Transform transform;
  transform.setOrigin( tf::Vector3(0,0,0.0) );
  tf::Quaternion q;
  q.setRPY(0, 0,0);
  transform.setRotation(q);
  while(ros::ok())
  {
  br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "holobot","base_link"));
  }
  return 0;
};