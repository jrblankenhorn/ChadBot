
void DifferentialDriver::CalcPWM(double velocity_R, double velocity_L)
{
  //calculate desired velocity
  velocity_right = (linear_x + angular_z / 2 );
  velocity_left = (linear_x - angular_z / 2 );
  current_time = micros();
  float dt = (current_time - previous_time) / 1000000;

  //average the velocities
  actual_left = velocity_L;
  actual_right = velocity_R;

  //calculate error
  error_left = velocity_left - actual_left;
  error_right = velocity_right - actual_right;

  //calculate integral
  integral_left += error_left * dt;
  integral_right += error_right * dt;

  //calculate derivative
  derivative_left = (error_left - last_error_left) / dt;
  derivative_right = (error_right - last_error_right) / dt;

  previous_time = current_time;

  //set last error
  last_error_left = error_left;
  last_error_right = error_right;

  //calculate output
  PWM_Left = kpL * error_left + kiL * integral_left + kdL * derivative_left;
  PWM_Right = kpR * error_right + kiR * integral_right + kdR * derivative_right;
  
  //set directions
  if (PWM_Left >= 0)
  {
    DIR_A_FL_D = 0;
    DIR_B_FL_D = 1;
    DIR_A_RL_D = 1;
    DIR_B_RL_D = 0;
  }

  if (PWM_Right >= 0)
  {
    DIR_A_FR_D = 1;
    DIR_B_FR_D = 0;
    DIR_A_RR_D = 0;
    DIR_B_RR_D = 1;
  }

  if (PWM_Left < 0)
  {
    PWM_Left = -PWM_Left;
    DIR_A_FL_D = 1;
    DIR_B_FL_D = 0;
    DIR_A_RL_D = 0;
    DIR_B_RL_D = 1;
  }

  if (PWM_Right < 0)
  {
    PWM_Right = -PWM_Right;
    DIR_A_FR_D = 0;
    DIR_B_FR_D = 1;
    DIR_A_RR_D = 1;
    DIR_B_RR_D = 0;
  }

  //keep within bounds
  if(PWM_Left > 255)
  {
    PWM_Left = 255;
  }

  if(PWM_Right > 255)
  {
    PWM_Right = 255;
  }


}


void DifferentialDriver::WritePWM()
{
  digitalWrite(DIR_A_FR, DIR_A_FR_D);
  digitalWrite(DIR_B_FR, DIR_B_FR_D);
  analogWrite(PWM_FR, PWM_Right);

  digitalWrite(DIR_A_RR, DIR_A_RR_D);
  digitalWrite(DIR_B_RR, DIR_B_RR_D);
  analogWrite(PWM_RR, PWM_Right);

  digitalWrite(DIR_A_FL, DIR_A_FL_D);
  digitalWrite(DIR_B_FL, DIR_B_FL_D);
  analogWrite(PWM_FL, PWM_Left);

  digitalWrite(DIR_A_RL, DIR_A_RL_D);
  digitalWrite(DIR_B_RL, DIR_B_RL_D);
  analogWrite(PWM_RL, PWM_Left);

}


