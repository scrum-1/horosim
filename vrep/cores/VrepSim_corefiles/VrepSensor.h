#include <string>
#include "VrepHandle.h"

enum SensorType {VisionSensor = 0, ProximitySensor = 1}; 

class VrepSensor : public VrepHandle{       // The class
 
  public:             // Access specifier
    
    void pinMode(char, char);
    int digitalRead(int);
    VrepSensor(int, std::string, enum SensorType);
    VrepSensor(){};

  private:
  	int pin;        // Pin of the Arduino where is connected
    SensorType type;
    bool set2input=true;
    float readVisionSensor();
    float readProximitySensor();

};