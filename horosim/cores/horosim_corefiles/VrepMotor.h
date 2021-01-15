#ifndef COPPELIASIM_MOTOR
#define COPPELIASIM_MOTOR

#include <string>
#include "VrepHandle.h"


#define JOINTINTPARAM_MOTOR_ENABLED 2000 //int32 parameter : dynamic motor enable state (0 or !=0)
#define JOINTINTPARAM_CTRL_ENABLED 2001 //int32 parameter : dynamic motor control loop enable state (0 or !=0)
#define JOINTFLOATPARAM_PID_P 2002 //float parameter : dynamic motor position control P parameter
#define JOINTFLOATPARAM_PID_I 2003 //float parameter : dynamic motor position control I parameter
#define JOINTFLOATPARAM_PID_D 2004 //float parameter : dynamic motor position control D parameter
#define JOINTINTPARAM_MOTOR_ENABLED 2000


class VrepMotor : public VrepHandle{       // The class
 
  public:             // Access specifier
    

    VrepMotor(std::string, double, double, double);
    VrepMotor(){};

  protected:
  	double force_max=-1;
  	double rpm_max=-1;
  	double reduction=1;

  	int setTargetSpeed(float);
  	int setTargetPosition(float);
  	int setMaxForce();
  	int enableControlLoop(bool);
  private:
  	int enableMotor(bool);


};

#endif