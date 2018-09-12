

void Odom::CalculateOdom(Encoder E1, Encoder E2)
{
  //read the encoders
  E1_P = - E1.read();//FR
  E3_P = - E2.read();//FL

  //get current time
  current_time = micros();

  //get current angle of wheels
  float theta_R = E1_P / Scale_E1 * 2 * PI;
  float theta_L = E3_P / Scale_E2 * 2 * PI;

  //get change in time
  float dt = (current_time - previous_time) / 1000000;

  //calculate stuff
  float d_th_R = theta_R - previous_theta_R;
  float d_th_L = theta_L - previous_theta_L;
  velocity_R = d_th_R * wheel_radius / dt;
  velocity_L = d_th_L * wheel_radius / dt;

  previous_theta_R = theta_R;
  previous_theta_L = theta_L;
  previous_time = current_time;
}

void Odom::PublishVelocities(ros::Publisher velocities_pub)
{
  std_msgs::Float64MultiArray velocities;
  velocities.data_length = 2;
  float velocities_array[2];
  velocities_array[0] = velocity_R;
  velocities_array[1] = velocity_L;
  velocities.data = velocities_array;
  velocities_pub.publish(&velocities);
}

