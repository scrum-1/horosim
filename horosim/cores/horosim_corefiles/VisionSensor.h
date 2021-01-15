#include <string>
#include "CoppeliaSimSensor.h"
#include "ArduinoUno.h"

class VisionSensor : public CoppeliaSimSensor{       // The class
 
  public:             // Access specifier
    
    int digitalRead(int);
    int analogRead(int);
    VisionSensor(int, std::string, float);
    VisionSensor(){};

  private:
  	float readVisionSensor();


};