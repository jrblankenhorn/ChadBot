#include <ros.h>
#include "Encoders.h"


class Odom{

public:
  
  //each wheel velocity
  float velocity_R = 0;
  float velocity_L = 0;

  //previous thetas
  float previous_theta_R = 0;
  float previous_theta_L = 0;
 
  
  void CalculateOdom(Encoder E1, Encoder E2);
  void PublishVelocities(ros::Publisher velocities_pub);
  
private:
  
  //wheel radius
  float wheel_radius = 0.062484;

  //length_ of distance between wheels / 2
  float length_ = 0.254;

  //times
  float current_time;
  float previous_time = micros();
  
  //encoder positions
  float E1_P;
  float E2_P;
  float E3_P;
  float E4_P;

  //scale for stuff
  float Scale_E1 = 12000;
  float Scale_E2 = -12000;


};






