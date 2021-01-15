#include "PushButton_Momentary_UI.h"
#include "Defines.h"
#include <string>


extern "C" {
#include "coppeliasim/remoteapi/extApi.h"
}
extern int clientID;

//Vector with the handles of joints and sensors
extern std::vector<HardwareDevice*> handles;

PushButton_Momentary_UI::PushButton_Momentary_UI(int pin_i, std::string str, enum ButtonType b_type_i):
HardwareDevice{str} {
	pin=pin_i;
	b_type=b_type_i;
	type=PushButton_Momentary_UI_t;
	handles.push_back(this);
}


void PushButton_Momentary_UI::setPushed() {
	if(b_type==PULL_DOWN)
		state=true;
	else
		state=false;
}

void PushButton_Momentary_UI::setReleased() {
	if(b_type==PULL_DOWN)
		state=false;
	else
		state=true;
}

int PushButton_Momentary_UI::digitalRead(int pin_i) {
	if(pin_i!=pin)
		return -1;

	if(!set2input)
		return 0;

	if(state)
		return 1;
	else
		return 0;
}

int PushButton_Momentary_UI::analogRead(int pin_i) {
	if(pin_i!=pin)
		return -1;

	if(!set2input)
		return 0;

	//It is not an analog sensor!
	if(state)
		return 1023;
	else
		return 0;
}

void PushButton_Momentary_UI::pinMode(char pin_i, char mode) {
	if(pin_i!=pin)
		return;
	if(mode==OUTPUT)
		set2input=false;
	else
		set2input=true;
}
