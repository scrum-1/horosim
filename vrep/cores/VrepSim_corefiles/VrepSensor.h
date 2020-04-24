#ifndef VREP_SENSOR
#define VREP_SENSOR

#include <string>
#include "VrepHandle.h"

class VrepSensor : public VrepHandle{       // The class
 
  public:             // Access specifier
    
    void pinMode(char, char);
    VrepSensor(int, std::string);
    VrepSensor(){};

  protected:
  	int pin;        // Pin of the Arduino where is connected
    bool set2input=true;


};

#endif