#include "VrepSensor.h"
#include "Defines.h"
#include <string>

extern "C" {
#include "coppeliasim/remoteapi/extApi.h"
}
extern int clientID;

void VrepSensor::pinMode(char pin_i, char mode) {
  if(pin_i!=pin)
    return;
  if(mode==OUTPUT)
    set2input=false;
  else
    set2input=true;
}

VrepSensor::VrepSensor(int pin_i, std::string str, float threshold_i):VrepHandle{str} {
  pin=pin_i;
  type=VrepSensor_t;
  if(threshold_i>1)
    threshold_i=1;
  if(threshold_i<0)
    threshold_i=0;
  threshold=threshold_i;
}

