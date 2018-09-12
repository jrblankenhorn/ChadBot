
#include <ros.h>
#include <std_msgs/Float64MultiArray.h>
#include "DifferentialDriver.h"
#include "Odom.h"

DifferentialDriver diff;
ros::NodeHandle nh;
Odom odom;

void velocityCallback(const geometry_msgs::Twist &msg)
{
  diff.linear_x = msg.linear.x;
  diff.angular_z = msg.angular.z;

}

ros::Subscriber<geometry_msgs::Twist> vel_sub("cmd_vel", &velocityCallback);
std_msgs::Float64MultiArray velocities;
ros::Publisher velocities_pub("wheel_velocities", &velocities);

void setup()
{
  nh.getHardware()->setBaud(115200);
  nh.initNode();
  nh.subscribe(vel_sub);
  nh.advertise(velocities_pub);
  setupMotorDriver();
}

void loop()
{
  nh.spinOnce();
  odom.CalculateOdom(E1, E2);
  odom.PublishVelocities(velocities_pub);
  diff.CalcPWM(odom.velocity_R, odom.velocity_L);
  diff.WritePWM();
}


