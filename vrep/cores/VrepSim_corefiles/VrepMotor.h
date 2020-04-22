#include <string>
#include "VrepHandle.h"


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
  	int setMaxForce();
  private:
  	int enableMotor(bool);

};