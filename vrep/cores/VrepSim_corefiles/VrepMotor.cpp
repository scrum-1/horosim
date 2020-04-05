#include "VrepMotor.h"
#include <string>

extern "C" {
    #include "extApi.h"
}
extern int clientID;


VrepMotor::VrepMotor(int pin_i, std::string str){
  	pin=pin_i; 
  	name=str;
  
  	int error=simxGetObjectHandle(clientID, name.c_str(), &handle, simx_opmode_blocking);
  	//printf(name.c_str());
  	if(error!=simx_return_ok){
  		printf("ARDUINO2VREP: Error retrieving the motor handler, error %d.\n", error);
  	}else{
  		//printf("Motor handler OK.\n");
  	}

 }

void VrepMotor::digitalWrite(int pin_i, int status){
	if(pin_i!=pin)
		return;
	//TODO: Send command to Vrep
	float speed = 0;
	if(status>0){
		speed=-2.1415;
	}

	int error=simxSetJointTargetVelocity(clientID, handle, speed, simx_opmode_oneshot);
	if(error>simx_return_novalue_flag){
  		printf("ARDUINO2VREP: Error setting the motor speed, error %d, handle %d, joint %s.\n", error, handle, name);
  	}else{
  		//printf("Speed set correctly.\n");
  	}
}
