#include "Servo.h"
#include <stdio.h>
#include <string>
#include <vector>
using namespace std;
#include "VrepHandle.h"

extern "C" {
#include "extApi.h"
}
//Vector with the handles of joints and sensors
extern std::vector<VrepHandle*> handles;

extern int clientID;

std::string servo_name;

void Servo::attach(int pin_i) {
	
	//Lets find the name of the handle that is connected to this pin
	for(vector<VrepHandle*>::iterator it=handles.begin(); it!=handles.end(); ++it) {
		int pin=(*it)->getServoPin();
		if(pin==pin_i){
			pin=pin_i;
			initialized=true;
			servo_name=(*it)->getHandleName();
		}
	}

	
	//If we did not find a servo connected to this pin, abort
	if(!initialized)
		return;

	int error=simxGetObjectHandle(clientID, servo_name.c_str(), &handle, simx_opmode_blocking);
	//printf(name.c_str());
	if(error!=simx_return_ok) {
		printf("ARDUINO2VREP: Error retrieving the servo handler, error %d.\n", error);
	}
	// else{
	// 	printf("Servo handler OK.\n");
	// }
}

void Servo::write(int val) {
	if(initialized && handle>0) {
		if(val>180)
			val=180;
		if(val<00)
			val=0;
		float pos=val/180.0*0.05;
		int error=simxSetJointTargetPosition(clientID, handle, pos, simx_opmode_oneshot);
		if(error>simx_return_novalue_flag) {
			printf("ARDUINO2VREP: Error setting the motor speed, error %d, handle %d, joint %s.\n", error, handle, servo_name.c_str());
		}
		// else{
		// 	printf("Position set correctly.\n");
		// }
	}

}