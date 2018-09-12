#include <ros/ros.h>
#include "odom_tf_pub.hpp"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "odom_stuff_node");

  ros::NodeHandle nh;

  OdomTfPub odom(nh);

  while(ros::ok)
  {
    ros::spin();
  }

}
