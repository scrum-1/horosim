#include <string>
#include "VrepSensor.h"


class VisionSensor : public VrepSensor{       // The class
 
  public:             // Access specifier
    
    int digitalRead(int);
    VisionSensor(int, std::string);
    VisionSensor(){};

  private:
  	float readVisionSensor();


};