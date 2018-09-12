#include <odom_tf_pub.hpp>

OdomTfPub::OdomTfPub(ros::NodeHandle &nh)
{
  vel_sub = nh.subscribe<std_msgs::Float64MultiArray>("/wheel_velocities", 100, &OdomTfPub::velocityCallback, this);
  odom_pub = nh.advertise<nav_msgs::Odometry>("/odom", 50);
}

void OdomTfPub::velocityCallback(const std_msgs::Float64MultiArray::ConstPtr &msg)
{
  right_velocity = msg->data[0];
  left_velocity = msg->data[1];

  current_time = ros::Time::now();
  dt = current_time - previous_time;
  float vx = (right_velocity + left_velocity) / 2;
  float vy = 0;
  float vth = (right_velocity - left_velocity) * wheel_radius / length * 2 * M_PI;
  float delta_x = (vx * cos(th) - vy * sin(th)) * dt.toSec();
  float delta_y = (vx * sin(th) + vy * cos(th)) * dt.toSec();
  float delta_th = vth * dt.toSec();
  x += delta_x;
  y += delta_y;
  th += delta_th;

  //quaternion and odom tf stuff
  geometry_msgs::Quaternion odom_quat;
  odom_quat =  tf::createQuaternionMsgFromYaw(th);
  odom_trans.transform.translation.x = x;
  odom_trans.transform.translation.y = y;
  odom_trans.transform.translation.z = 0.0;
  odom_trans.transform.rotation = odom_quat;

  //set the position
  odom.pose.pose.position.x = x;
  odom.pose.pose.position.y = y;
  odom.pose.pose.position.z = 0.0;
  odom.pose.pose.orientation = odom_quat;
  odom.pose.covariance =          {0.001, 0, 0, 0, 0, 0,
                                   0, 0.001, 0, 0, 0, 0,
                                   0, 0, 99999, 0, 0, 0,
                                   0, 0, 0, 99999, 0, 0,
                                   0, 0, 0, 0, 99999, 0,
                                   0, 0, 0, 0, 0, 0.001};
  //and twist msg
  odom.twist.twist.linear.x = vx;
  odom.twist.twist.linear.y = 0;
  odom.twist.twist.angular.z = vth;

  //pub
  odom_trans.header.stamp = ros::Time::now();
  odom_trans.header.frame_id = "/odom";
  odom_trans.child_frame_id = "/base_link";
  broadcaster.sendTransform(odom_trans);
  odom.header.stamp = ros::Time::now();
  odom.header.frame_id = "odom";
  odom.child_frame_id = "base_link";
  odom_pub.publish(odom);

  previous_time = current_time;
}






