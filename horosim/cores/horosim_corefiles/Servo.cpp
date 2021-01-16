#include "Servo.h"
#include <stdio.h>
#include <string>
#include <vector>
using namespace std;
#include "CoppeliaSimHandle.h"

extern "C" {
#include "coppeliasim/remoteapi/extApi.h"
}
//Vector with the handles of joints and sensors
extern std::vector<HardwareDevice*> handles;

extern int clientID;

std::string servo_name;

void Servo::attach(int pin_i) {
	if(pin_i<0)
		return;
	isAttached=true;
	//Lets find the name of the handle that is connected to this pin
	for(vector<HardwareDevice*>::iterator it=handles.begin(); it!=handles.end(); ++it) {
		int pin=(*it)->getServoPin();
		if(pin==pin_i){
			pin=pin_i;
			initialized=true;
			servo_name=(*it)->getHandleName();
			reduction=(*it)->getServoReduction();
		}
	}

	
	//If we did not find a servo connected to this pin, abort
	if(!initialized)
		return;

	int error=simxGetObjectHandle(clientID, servo_name.c_str(), &handle, simx_opmode_blocking);
	//printf(name.c_str());
	if(error!=simx_return_ok) {
		printf("HoRoSim: Error retrieving the servo handler, error %d.\n", error);
	}
	// else{
	// 	printf("Servo handler OK.\n");
	// }
}

void Servo::write(int val) {
	if(initialized && handle>0 && isAttached) {
		if(val>180)
			val=180;
		if(val<0)
			val=0;
		currentPos=val;
		//The servo starts centered (0=>left, 90:center, 180=>right)
		float pos=(val-90)/180.0*3.1415*reduction;
		int error=simxSetJointTargetPosition(clientID, handle, pos, simx_opmode_oneshot);
		if(error>simx_return_novalue_flag) {
			printf("HoRoSim: Error setting the motor speed, error %d, handle %d, joint %s.\n", error, handle, servo_name.c_str());
		}
		// else{
		// 	printf("Position set correctly.\n");
		// }
	}
}

void Servo::writeMicroseconds(int val) {
	int minUs=700;
	int maxUs=2300;
	if(val<minUs)
		val=minUs;
	if(val>maxUs)
		val=maxUs;
	write((val-minUs)/(maxUs-minUs)*180);
}

int Servo::read() {
	return currentPos;
}

bool Servo::attached(){
	return isAttached;
}

void Servo::dettach(){
	isAttached=false;
}