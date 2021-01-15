#include "Potentiometer_UI.h"
#include "Defines.h"
#include <string>


extern "C" {
#include "coppeliasim/remoteapi/extApi.h"
}
extern int clientID;

//Vector with the handles of joints and sensors
extern std::vector<HardwareDevice*> handles;

Potentiometer_UI::Potentiometer_UI(int pin_i, std::string str, float init_state):
HardwareDevice{str} {
	pin=pin_i;
	type=Potentiometer_UI_t;
	if(init_state>1)
		init_state=1;
	if(init_state<0)
		init_state=0;
	potVal=init_state;
	handles.push_back(this);
}

void Potentiometer_UI::setPotVal(float val) {
	potVal=val;
}

float* Potentiometer_UI::getPotPointer() {
	return &potVal;
}

int Potentiometer_UI::digitalRead(int pin_i) {
	if(pin_i!=pin)
		return -1;

	if(!set2input)
		return 0;

	if(potVal<0.5)
		return 0;
	else
		return 1;
}

int Potentiometer_UI::analogRead(int pin_i) {
	if(pin_i!=pin)
		return -1;

	if(!set2input)
		return 0;

	//If it is not an analog pin
	if(pin<A0 || pin>A5) {
		if(potVal<0.5)
			return 0;
		else
			return 1023;
	}
	return potVal*1023;
}

void Potentiometer_UI::pinMode(char pin_i, char mode) {
	if(pin_i!=pin)
		return;
	if(mode==OUTPUT)
		set2input=false;
	else
		set2input=true;
}
