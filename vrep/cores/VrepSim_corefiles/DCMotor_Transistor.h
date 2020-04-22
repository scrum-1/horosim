#include <string>
#include "VrepMotor.h"

class DCMotor_Transistor : public VrepMotor{       // The class
 
  public:             // Access specifier
    
    void pinMode(char, char);
    void digitalWrite(int, int);
    DCMotor_Transistor(int, std::string, float, float, float);
    DCMotor_Transistor(){};
    void analogWrite(int, int);

  private:
  	int pin;        // Pin of the Arduino where is connected
    bool set2output=false;

};