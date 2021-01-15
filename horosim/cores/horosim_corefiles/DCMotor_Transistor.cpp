#include "DCMotor_Transistor.h"
#include "Defines.h"
#include <string>


extern "C" {
#include "coppeliasim/extApi.h"
}
extern int clientID;

//Vector with the handles of joints and sensors
extern std::vector<HardwareDevice*> handles;

DCMotor_Transistor::DCMotor_Transistor(int pin_i, std::string str, float force, float speed, float reduction):
	VrepMotor{str, force, speed, reduction} {
	pin=pin_i;
	type=DCMotor_Transistor_t;
	enableControlLoop(false);
	handles.push_back(this);

}

void DCMotor_Transistor::pinMode(char pin_i, char mode) {
	if(pin_i!=pin)
		return;
	if(mode==OUTPUT)
		set2output=true;
	else
		set2output=false;
}
void DCMotor_Transistor::digitalWrite(int pin_i, int status) {
	if(pin_i!=pin)
		return;
	if(!set2output)
		return;

	float speed = 0;
	if(status>0) {
		speed=rpm_max;
	}
	setTargetSpeed(speed);
}

void DCMotor_Transistor::analogWrite(int pin_i, int value) {
	if(pin_i!=pin)
		return;
	if(!set2output)
		return;
	if(pin_i==3||pin_i==5||pin_i==6||pin_i==9||pin_i==10||pin_i==11) {
		value=value%256;
		setTargetSpeed(rpm_max/255*value);
	}
}