#include <string>
#include "VrepSensor.h"
#include "ArduinoUno.h"



class ProximitySensor : public VrepSensor{       // The class
 
  public:             // Access specifier
    
    int digitalRead(int);
    int analogRead(int);
    ProximitySensor(int, std::string, float, float);
    ProximitySensor(){};

  private:
    float readProximitySensor();
    float range;

};