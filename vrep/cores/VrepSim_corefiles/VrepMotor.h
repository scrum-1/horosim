#include <string>
#include "VrepHandle.h"

class VrepMotor : public VrepHandle{       // The class
 
  public:             // Access specifier
    

    VrepMotor(std::string, double, double, double);
    VrepMotor(){};

  protected:
  	double force_max=-1;
  	double rpm_max=-1;
  	double reduction=1;

  private:
  	void setMaxForce();
};