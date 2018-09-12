#include <ros.h>
#include <geometry_msgs/Twist.h>

//motor pins
#define PWM_FR 8
#define DIR_A_FR 13
#define DIR_B_FR 12

#define PWM_RR 9
#define DIR_A_RR 11
#define DIR_B_RR 10

#define PWM_FL 7
#define DIR_A_FL 6
#define DIR_B_FL 5

#define PWM_RL 2
#define DIR_A_RL 3
#define DIR_B_RL 4



void setupMotorDriver()
{
  pinMode(PWM_FR, OUTPUT);
  pinMode(DIR_A_FR, OUTPUT);
  pinMode(DIR_B_FR, OUTPUT);

  pinMode(PWM_RR, OUTPUT);
  pinMode(DIR_A_RR, OUTPUT);
  pinMode(DIR_B_RR, OUTPUT);

  pinMode(PWM_FL, OUTPUT);
  pinMode(DIR_A_FL, OUTPUT);
  pinMode(DIR_B_FL, OUTPUT);

  pinMode(PWM_RL, OUTPUT);
  pinMode(DIR_A_RL, OUTPUT);
  pinMode(DIR_B_RL, OUTPUT);
}


class DifferentialDriver {

  public:


    //variables to take the inputs of the stuff
    double linear_x = 0;
    double angular_z = 0;

    //calculcate PWM
    void CalcPWM(double velocity_R, double velocity_L);

    //write PWM outputs
    void WritePWM();



  private:

    float previous_time = micros();
    float current_time;
    //define left and right wheel pwm signals
    double PWM_Left;
    double PWM_Right;

    //and directions
    int DIR_A_FL_D = 0;
    int DIR_B_FL_D = 0;
    int DIR_A_FR_D = 0;
    int DIR_B_FR_D = 0;
    int DIR_A_RL_D = 0;
    int DIR_B_RL_D = 0;
    int DIR_A_RR_D = 0;
    int DIR_B_RR_D = 0;

    //define velocity_left
    double velocity_left;

    //and right
    double velocity_right;

    //actual velocity left
    double actual_left;

    //and right
    double actual_right;

    //define wheel radius
    double wheel_radius = 0.062484;

    //define wheel base
    double length_ = 0.254;

    //PID stuff
    double kpL = 200;
    double kpR = 200;

    double kiL = 3000;
    double kiR = 3000;

    double kdL = 10;
    double kdR = 10;

    double error_left = 0;
    double error_right = 0;

    double last_error_left = 0;
    double last_error_right = 0;

    double integral_left = 0;
    double integral_right = 0;

    double derivative_left = 0;
    double derivative_right = 0;

};



