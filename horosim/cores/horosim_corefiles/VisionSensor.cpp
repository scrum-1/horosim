#include "VisionSensor.h"
#include "Defines.h"
#include <string>

extern "C" {
#include "coppeliasim/remoteapi/extApi.h"
}
extern int clientID;

//Vector with the handles of joints and sensors
extern std::vector<HardwareDevice*> handles;

VisionSensor::VisionSensor(int pin_i, std::string str, float threshold_i):VrepSensor{pin_i, str, threshold_i} {

  type=VisionSensor_t;
  int error;

  //First call to set te streaming mode

  float* auxValues;
  int* auxValuesCount;
  error=simxReadVisionSensor(clientID, handle, NULL, &auxValues, &auxValuesCount, simx_opmode_streaming);


  if(error>simx_return_novalue_flag) {
    printf("HoRoSim: Error reading the sensor, error %d, handle %d, sensor %s.\n", error, handle, handle_name.c_str());
  }
  handles.push_back(this);
  // else{
  //   printf("Reading first time sensor OK.\n");
  //   // if(auxValuesCount!=NULL){
  //   //   printf("Number of packages: %d, size package1: %d\n", auxValuesCount[0], auxValuesCount[1]);
  //   // }
  //   // else
  //   //    printf("HoRoSim: DATA empty.\n");
  // }


}

int VisionSensor::digitalRead(int pin_i) {
  if(pin_i!=pin)
    return -1;

  if(!set2input)
    return -1;

  float value=-1;

  value=readVisionSensor();

  if(value>threshold)
    return 1;
  if(value<0)
    return -1;
  return 0;

}

int VisionSensor::analogRead(int pin_i){
  if(pin_i!=pin)
    return -1;

  if(!set2input)
    return -1;

  //If it is not an analog pin 
  if(pin<A0 || pin>A5){
    if(readVisionSensor()<0.5)
      return 0;
    else
      return 1023;
  }

  //It is an analog pin, return analog value
  return readVisionSensor()*1023;
}

float VisionSensor::readVisionSensor() {

  float* auxValues;
  int* auxValuesCount;
  int error=simxReadVisionSensor(clientID, handle, NULL, &auxValues, &auxValuesCount, simx_opmode_buffer);
  if(error>simx_return_novalue_flag) {
    printf("HoRoSim: Error reading the sensor, error %d, handle %d, sensor %s.\n", error, handle, handle_name.c_str());
  } else {
    //printf("Sensor read correctly.\n");
    if(auxValuesCount!=NULL && error==simx_return_ok) {
      //printf("Number of packages: %d, size package1: %d \n", auxValuesCount[0], auxValuesCount[1]);
      //printf("Value: %f\n", auxValues[10]);
      //printf("Values: " );
      // for (int i = 0; i < auxValuesCount[1]; ++i)
      // {
      //    printf(" %f,", auxValues[i]);
      // }
      // printf("\n" );
      return auxValues[10];
    }
    else
      printf("HoRoSim: DATA empty.\n");
  }
  return -1;
}


