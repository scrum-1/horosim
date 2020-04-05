#include "Servo.h"
#include <stdio.h>

extern "C" {
    #include "extApi.h"
}
extern int clientID;

#define SERVO_PIN 3
#define SERVO_NAME "servo_joint"

void Servo::attach(int pin_i){
	pin=pin_i;
	if(pin==SERVO_PIN)
		initialized=true;

	int error=simxGetObjectHandle(clientID, SERVO_NAME, &handle, simx_opmode_blocking);
  	//printf(name.c_str());
  	if(error!=simx_return_ok){
  		printf("ARDUINO2VREP: Error retrieving the servo handler, error %d.\n", error);
  	}
  	// else{
  	// 	printf("Servo handler OK.\n");
  	// }
}

void Servo::write(int val){
	if(initialized && handle>0){
		if(val>180)
			val=180;
		if (val<00)
			val=0;
		float pos=val/180.0*0.05;
		int error=simxSetJointTargetPosition(clientID, handle, pos, simx_opmode_oneshot);
		if(error>simx_return_novalue_flag){
  			printf("ARDUINO2VREP: Error setting the motor speed, error %d, handle %d, joint %s.\n", error, handle, SERVO_NAME);
  		}
  		// else{
  		// 	printf("Position set correctly.\n");
  		// }
	}

}