#include <string>
#include "VrepSensor.h"



class ProximitySensor : public VrepSensor{       // The class
 
  public:             // Access specifier
    
    int digitalRead(int);
    ProximitySensor(int, std::string);
    ProximitySensor(){};

  private:
    float readProximitySensor();

};