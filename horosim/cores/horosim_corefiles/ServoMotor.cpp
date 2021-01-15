#include "ServoMotor.h"
#include "Defines.h"
#include <string>
#include <math.h>
#include "SimTime.h"

extern "C" {
#include "coppeliasim/remoteapi/extApi.h"
}
extern int clientID;

//Vector with the handles of joints and sensors
extern std::vector<HardwareDevice*> handles;

ServoMotor::ServoMotor(int pin_i, std::string str, float force, float speed, float reduction):
	VrepMotor{str, force, speed, reduction} {
	pin=pin_i;
	type=ServoMotor_t;
	enableControlLoop(true);
	handles.push_back(this);
}

int ServoMotor::getServoPin(){
	return pin;
}

double ServoMotor::getServoReduction(){
	return reduction;
};

void ServoMotor::analogWrite(int pin_i, int value) {
	if(pin_i!=pin)
		return;

	if(pin_i==3||pin_i==5||pin_i==6||pin_i==9||pin_i==10||pin_i==11) {
		setTargetPosition(0);
	}
}