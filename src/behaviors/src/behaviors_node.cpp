#include <ros/ros.h>
#include "behaviors.hpp"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "behaviors_node");

  ros::NodeHandle nh;

  behaviors::BehaviorMaster beh_master(nh);

  ros::Rate rate(50);

  while(ros::ok)
  {
    ros::spinOnce();

    rate.sleep();

  }

}
