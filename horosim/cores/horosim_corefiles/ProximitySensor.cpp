#include "ProximitySensor.h"
#include "Defines.h"
#include <string>

extern "C" {
#include "extApi.h"
}
extern int clientID;

//Vector with the handles of joints and sensors
extern std::vector<HardwareDevice*> handles;

ProximitySensor::ProximitySensor(int pin_i, std::string str, float range_i, float threshold_i):VrepSensor{pin_i, str, threshold_i} {

  type=ProximitySensor_t;
  int error;
  range=range_i;


  //First call to set te streaming mode
  float readDistance[3] = {0, 0, 0};
  error=simxReadProximitySensor(clientID, handle, NULL, &(readDistance[0]), NULL, NULL, simx_opmode_streaming);

  if(error>simx_return_novalue_flag) {
    printf("ARDUINO2VREP: Error reading the sensor, error %d, handle %d, sensor %s.\n", error, handle, handle_name.c_str());
  }

  handles.push_back(this);
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
  value/=range;

  if(value<threshold)
    return 1;
  else
    return 0;
}

int ProximitySensor::analogRead(int pin_i) {
  if(pin_i!=pin)
    return -1;

  if(!set2input)
    return -1;

  //If it is not an analog pin
  if(pin<A0 || pin>A5) {
    if((readProximitySensor()/range)<0.5)
      return 0;
    else
      return 1023;
  }

  return readProximitySensor()/range*1023;
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
  return range;
}

