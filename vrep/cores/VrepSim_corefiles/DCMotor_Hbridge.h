#include <string>
#include "VrepMotor.h"
#include "Defines.h"

class DCMotor_Hbridge : public VrepMotor{       // The class
 
  public:             // Access specifier
    
    void pinMode(char, char);
    void digitalWrite(int, int);
    DCMotor_Hbridge(int, int, int, std::string, float, float, float);
    DCMotor_Hbridge(){};
    void analogWrite(int, int);

  private:
  	int in1_pin, in2_pin, en_pin;        // Pin of the Arduino where is connected
    bool in1_set2output=false;
    bool in2_set2output=false;
    bool en_set2output=false;
    bool in1=LOW, in2=LOW, en=LOW;
    int pwm=255;

};