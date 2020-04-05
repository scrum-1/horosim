#include "VrepSensor.h"
#include "Defines.h"
#include <string>

extern "C" {
    #include "extApi.h"
}
extern int clientID;

void VrepSensor::pinMode(char pin_i, char mode){
  if(pin_i!=pin)
    return;
  if(mode==OUTPUT)
    set2input=false;
  else
    set2input=true;
}

VrepSensor::VrepSensor(int pin_i, std::string str, enum SensorType type_i){
  	pin=pin_i; 
    type=type_i;
  	name=str;
    int error=simxGetObjectHandle(clientID, name.c_str(), &handle, simx_opmode_blocking);
  	//printf(name.c_str());
  	if(error!=simx_return_ok){
  		printf("ARDUINO2VREP: Error retrieving the sensor handler, error %d.\n", error);
  	}
   //  else{
  	// 	printf("Sensor handler OK.\n");
  	// }

    //First call to set te streaming mode
    if(type==VisionSensor){
      float* auxValues;
      int* auxValuesCount;
      error=simxReadVisionSensor(clientID, handle, NULL, &auxValues, &auxValuesCount, simx_opmode_streaming );
    }
    if(type==ProximitySensor){
      float readDistance[3] = {0, 0, 0};
      error=simxReadProximitySensor(clientID, handle, NULL, &(readDistance[0]), NULL, NULL, simx_opmode_streaming);
    }
    if(error>simx_return_novalue_flag){
        printf("ARDUINO2VREP: Error reading the sensor, error %d, handle %d, sensor %s.\n", error, handle, name.c_str());
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

int VrepSensor::digitalRead(int pin_i){
	if(pin_i!=pin)
		return -1;

  if(!set2input)
    return -1;

  float value=-1;
  if(type==VisionSensor)
    value=readVisionSensor();
  if(type==ProximitySensor){
    value=readProximitySensor();
    value/=0.16;
    if (value<0) 
      return 0;

    if (value<0.3) 
      return 1;
    else
      return 0;
  }

  if (value>0.5) 
    return 1;
  if (value<0) 
    return -1;
  return 0;
  
}

float VrepSensor::readVisionSensor(){

  float* auxValues;
  int* auxValuesCount;
  int error=simxReadVisionSensor(clientID, handle, NULL, &auxValues, &auxValuesCount, simx_opmode_buffer);
  if(error>simx_return_novalue_flag){
      printf("ARDUINO2VREP: Error reading the sensor, error %d, handle %d, sensor %s.\n", error, handle, name.c_str());
    }else{
      //printf("Sensor read correctly.\n");
      if(auxValuesCount!=NULL && error==simx_return_ok){
        //printf("Number of packages: %d, size package1: %d \n", auxValuesCount[0], auxValuesCount[1]);
        //printf("Value: %f", auxValues[10]);
        //printf("Values: " );
        // for (int i = 0; i < auxValuesCount[1]; ++i)
        // {
        //    printf(" %f,", auxValues[i]);
        // }
        // printf("\n" );
        return auxValues[10];
      }
      else
         printf("ARDUINO2VREP: DATA empty.\n");
  }
  return -1;
}

float VrepSensor::readProximitySensor(){

  float readDistance[3] = {0, 0, 0};
  int hande_coll=0;
  unsigned char detectionState;
  int error=simxReadProximitySensor(clientID, handle, &detectionState, &(readDistance[0]), &hande_coll, NULL, simx_opmode_buffer);
  if(error>simx_return_novalue_flag){
      printf("ARDUINO2VREP: Error reading the sensor, error %d, handle %d, sensor %s.\n", error, handle, name.c_str());
  }else{
      if(detectionState!=0 && error==simx_return_ok){        
        //printf("IR SENSOR: " );
        //printf("Value: %f %f %f %d\n", readDistance[0], readDistance[1], readDistance[2], hande_coll);
        return readDistance[2];
      }
      // else
      //   printf("ARDUINO2VREP: No detection.\n");
  }
  return -1;
}

