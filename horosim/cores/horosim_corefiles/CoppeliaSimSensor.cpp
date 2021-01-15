#include "CoppeliaSimSensor.h"
#include "Defines.h"
#include <string>

extern "C" {
#include "coppeliasim/remoteapi/extApi.h"
}
extern int clientID;

void CoppeliaSimSensor::pinMode(char pin_i, char mode) {
  if(pin_i!=pin)
    return;
  if(mode==OUTPUT)
    set2input=false;
  else
    set2input=true;
}

CoppeliaSimSensor::CoppeliaSimSensor(int pin_i, std::string str, float threshold_i):CoppeliaSimHandle{str} {
  pin=pin_i;
  type=CoppeliaSimSensor_t;
  if(threshold_i>1)
    threshold_i=1;
  if(threshold_i<0)
    threshold_i=0;
  threshold=threshold_i;
}

