#ifndef COPPELIASIM_SENSOR
#define COPPELIASIM_SENSOR

#include <string>
#include "VrepHandle.h"

class VrepSensor : public VrepHandle{       // The class
 
  public:             // Access specifier
    
    void pinMode(char, char);
    VrepSensor(int, std::string, float);
    VrepSensor(){};

  protected:
  	int pin;        // Pin of the Arduino where is connected
    bool set2input=true;
    float threshold=0.3; //Threshold for the digital output


};

#endif