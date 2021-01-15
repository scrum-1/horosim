#ifndef COPPELIASIM_SENSOR
#define COPPELIASIM_SENSOR

#include <string>
#include "CoppeliaSimHandle.h"

class CoppeliaSimSensor : public CoppeliaSimHandle{       // The class
 
  public:             // Access specifier
    
    void pinMode(char, char);
    CoppeliaSimSensor(int, std::string, float);
    CoppeliaSimSensor(){};

  protected:
  	int pin;        // Pin of the Arduino where is connected
    bool set2input=true;
    float threshold=0.3; //Threshold for the digital output


};

#endif