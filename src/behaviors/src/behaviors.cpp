#include "behaviors.hpp"
#include <ros/ros.h>
namespace behaviors {

BehaviorMaster::BehaviorMaster(ros::NodeHandle &nh)
{
  goal_sub = nh.subscribe<move_base_msgs::MoveBaseActionGoal>("/move_base/goal", 100, &BehaviorMaster::goalCallback, this);
  goal_status_sub = nh.subscribe<actionlib_msgs::GoalStatusArray>("/move_base/status", 100, &BehaviorMaster::goalStatusCallback, this);
  goal_pub = nh.advertise<move_base_msgs::MoveBaseActionGoal>("move_base/goal", 100);
  cancel_pub = nh.advertise<actionlib_msgs::GoalID>("move_base/cancel", 100);
}

void BehaviorMaster::navigateWaypoints()
{
  for(auto &&waypoint : waypoints)
  {
    waypoint.header.stamp = ros::Time::now();
    waypoint.goal_id.id = waypoint_count;
    goal_pub.publish(waypoint);
    for(auto status : goal_statuses.status_list)
    {
      if(status.goal_id.id == waypoint.goal_id.id)
      {
        while(!status.SUCCEEDED)
        {
          continue;
        }
      }
    }
  }
}

void BehaviorMaster::setNewGoal(const move_base_msgs::MoveBaseActionGoal &goal)
{
  goal_pub.publish(goal);
}

void BehaviorMaster::cancelCurrentGoal()
{
  cancel_pub.publish(current_goal.goal_id);
}

void BehaviorMaster::addWaypointToQueue(const move_base_msgs::MoveBaseActionGoal &waypoint)
{
  waypoints.push_back(waypoint);
}


void BehaviorMaster::goalCallback(const move_base_msgs::MoveBaseActionGoal::ConstPtr &msg)
{
  current_goal = *msg;
}

void BehaviorMaster::goalStatusCallback(const actionlib_msgs::GoalStatusArray::ConstPtr &msg)
{
  goal_statuses = *msg;
}

}
