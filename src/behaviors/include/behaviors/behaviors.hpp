#pragma once

#include <ros/ros.h>
#include <actionlib_msgs/GoalID.h>
#include <actionlib_msgs/GoalStatus.h>
#include <actionlib_msgs/GoalStatusArray.h>
#include <move_base_msgs/MoveBaseActionGoal.h>

namespace behaviors {

class BehaviorMaster
{
public:
  BehaviorMaster(ros::NodeHandle &nh);

private:
  void navigateWaypoints();
  void goalCallback(const move_base_msgs::MoveBaseActionGoal::ConstPtr &msg);
  void goalStatusCallback(const actionlib_msgs::GoalStatusArray::ConstPtr &msg);
  void setNewGoal(const move_base_msgs::MoveBaseActionGoal &goal);
  void cancelCurrentGoal();
  void addWaypointToQueue(const move_base_msgs::MoveBaseActionGoal &goal);

  ros::Subscriber goal_sub;
  ros::Subscriber goal_status_sub;
  ros::Publisher goal_pub;
  ros::Publisher cancel_pub;

  move_base_msgs::MoveBaseActionGoal current_goal;
  std::vector<move_base_msgs::MoveBaseActionGoal> waypoints = {};

  actionlib_msgs::GoalStatusArray goal_statuses;

  int waypoint_count = 0;


};
}
