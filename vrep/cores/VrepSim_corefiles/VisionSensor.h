#include <string>
#include "VrepSensor.h"


class VisionSensor : public VrepSensor{       // The class
 
  public:             // Access specifier
    
    int digitalRead(int);
    int analogRead(int);
    VisionSensor(int, std::string, float);
    VisionSensor(){};

  private:
  	float readVisionSensor();


};