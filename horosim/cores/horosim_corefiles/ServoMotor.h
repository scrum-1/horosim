#include <string>
#include "CoppeliaSimMotor.h"

class ServoMotor : public CoppeliaSimMotor{       // The class
 
  public:             // Access specifier
    
    void analogWrite(int, int);
    ServoMotor(int pin_i, std::string str, float force, float speed, float reduction, float minPos_i = 0);
    ServoMotor(){};
    int getServoPin();
    double getServoReduction();
    double getServoMinPos();


  private:
  	int pin;        // Pin of the Arduino where is connected
    float pos=0;
    float minPos=0;
};