#include "Potentiometer.h"
#include "Defines.h"
#include <string>


extern "C" {
#include "coppeliasim/remoteapi/extApi.h"
}
extern int clientID;

//Vector with the handles of joints and sensors
extern std::vector<HardwareDevice*> handles;

Potentiometer::Potentiometer(int pin_i, std::string str, float range_i):
CoppeliaSimHandle{str} {
	pin=pin_i;
	type=Potentiometer_t;
	range = range_i;
	handles.push_back(this);
}

void Potentiometer::setPotVal(float val) {
	potVal=val;
}

float* Potentiometer::getPotPointer() {
	return &potVal;
}

int Potentiometer::digitalRead(int pin_i) {
	if(pin_i!=pin)
		return -1;

	if(!set2input)
		return 0;

	potVal = readPot()/range;

	if(potVal<0.5)
		return 0;
	else
		return 1;
}

float Potentiometer::readPot() {
	float position;
	int error=simxGetJointPosition(clientID, handle, &position, simx_opmode_blocking );
	if(error!=simx_return_ok) {
		printf("HoRoSim: Error reading the angle of the potentiometer, error %d, handle %d, sensor %s.\n", error, handle, handle_name.c_str());
		//We use the last position that we got
		return potVal;
	}else{
		//printf("HoRoSim: Pos angle received, position= %f\n", position);
		return position;
	}
}

int Potentiometer::analogRead(int pin_i) {
	if(pin_i!=pin)
		return -1;

	if(!set2input)
		return 0;

	potVal = readPot()/range;

	//If it is not an analog pin
	if(pin<A0 || pin>A5) {
		if(potVal<0.5)
			return 0;
		else
			return 1023;
	}
	return potVal*1023;
}

void Potentiometer::pinMode(char pin_i, char mode) {
	if(pin_i!=pin)
		return;
	if(mode==OUTPUT)
		set2input=false;
	else
		set2input=true;
}
