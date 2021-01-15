#include <string>
#include "CoppeliaSimSensor.h"
#include "ArduinoUno.h"



class ProximitySensor : public CoppeliaSimSensor{       // The class
 
  public:             // Access specifier
    
    int digitalRead(int);
    int analogRead(int);
    ProximitySensor(int, std::string, float, float);
    ProximitySensor(){};

  private:
    float readProximitySensor();
    float range;

};