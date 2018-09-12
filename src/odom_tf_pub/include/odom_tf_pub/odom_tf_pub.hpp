#pragma once
#include <ros/ros.h>
#include <std_msgs/Float64MultiArray.h>
#include <nav_msgs/Odometry.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/TransformStamped.h>
#include <math.h>

class OdomTfPub
{
public:

  OdomTfPub(ros::NodeHandle &nh);


private:

  void velocityCallback(const std_msgs::Float64MultiArray::ConstPtr &msg);

  ros::Subscriber vel_sub;
  ros::Publisher odom_pub;

  tf::TransformBroadcaster broadcaster;
  nav_msgs::Odometry odom;
  geometry_msgs::TransformStamped odom_trans;

  ros::Time current_time;
  ros::Time previous_time;
  ros::Duration dt;

  float length = 0.254;
  float wheel_radius = 0.062484;

  float left_velocity;
  float right_velocity;


  float th = 0;
  float x = 0;
  float y = 0;


};
