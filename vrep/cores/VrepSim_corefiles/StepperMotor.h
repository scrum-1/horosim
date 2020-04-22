#include <string>
#include "VrepMotor.h"

class StepperMotor : public VrepMotor{       // The class
 
  public:             // Access specifier
    
    void pinMode(char, char);
    void digitalWrite(int, int);
    void analogWrite(int, int);
    StepperMotor(int, int, std::string, float, float, float);
    StepperMotor(){};

  private:
  	int dir_pin;        // Pin of the Arduino where is connected
    int step_pin;        // Pin of the Arduino where is connected    
    bool dir_set2output=false;
    bool step_set2output=false;
    bool forward=true;
    float pos=0;
    bool step_value=false;

};