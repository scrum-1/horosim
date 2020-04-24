#include "ProximitySensor.h"
#include "Defines.h"
#include <string>

extern "C" {
#include "extApi.h"
}
extern int clientID;



ProximitySensor::ProximitySensor(int pin_i, std::string str):VrepSensor{pin_i, str} {

  type=ProximitySensor_t;
  int error;

  //First call to set te streaming mode
  float readDistance[3] = {0, 0, 0};
  error=simxReadProximitySensor(clientID, handle, NULL, &(readDistance[0]), NULL, NULL, simx_opmode_streaming);

  if(error>simx_return_novalue_flag) {
    printf("ARDUINO2VREP: Error reading the sensor, error %d, handle %d, sensor %s.\n", error, handle, handle_name.c_str());
  }

  // else{
  //   printf("Reading first time sensor OK.\n");
  //   // if(auxValuesCount!=NULL){
  //   //   printf("Number of packages: %d, size package1: %d\n", auxValuesCount[0], auxValuesCount[1]);
  //   // }
  //   // else
  //   //    printf("ARDUINO2VREP: DATA empty.\n");
  // }


}

int ProximitySensor::digitalRead(int pin_i) {
  if(pin_i!=pin)
    return -1;

  if(!set2input)
    return -1;

  float value=-1;

  value=readProximitySensor();
  value/=0.16;
  if(value<0)
    return 0;

  if(value<0.3)
    return 1;
  else
    return 0;

}



float ProximitySensor::readProximitySensor() {

  float readDistance[3] = {0, 0, 0};
  int hande_coll=0;
  unsigned char detectionState;
  int error=simxReadProximitySensor(clientID, handle, &detectionState, &(readDistance[0]), &hande_coll, NULL, simx_opmode_buffer);
  if(error>simx_return_novalue_flag) {
    printf("ARDUINO2VREP: Error reading the sensor, error %d, handle %d, sensor %s.\n", error, handle, handle_name.c_str());
  } else {
    if(detectionState!=0 && error==simx_return_ok) {
      //printf("IR SENSOR: " );
      //printf("Value: %f %f %f %d\n", readDistance[0], readDistance[1], readDistance[2], hande_coll);
      return readDistance[2];
    }
    // else
    //   printf("ARDUINO2VREP: No detection.\n");
  }
  return -1;
}

