#include <string>
#include "CoppeliaSimMotor.h"

class ServoMotor : public CoppeliaSimMotor{       // The class
 
  public:             // Access specifier
    
    void analogWrite(int, int);
    ServoMotor(int, std::string, float, float, float);
    ServoMotor(){};
    int getServoPin();
    double getServoReduction();


  private:
  	int pin;        // Pin of the Arduino where is connected
    float pos=0;
};