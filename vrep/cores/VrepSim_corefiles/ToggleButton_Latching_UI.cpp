#include "ToggleButton_Latching_UI.h"
#include "Defines.h"
#include <string>


extern "C" {
#include "extApi.h"
}
extern int clientID;

//Vector with the handles of joints and sensors
extern std::vector<VrepHandle*> handles;

ToggleButton_Latching_UI::ToggleButton_Latching_UI(int pin_i, std::string str, enum ButtonType b_type_i):VrepHandle{str} {
	pin=pin_i;
	b_type=b_type_i;
	if(b_type==PULL_DOWN)
		state=false;
	else
		state=true;
	type=ToggleButton_Latching_UI_t;
	handles.push_back(this);
}


bool* ToggleButton_Latching_UI::getState() {
	return &state;
}

int ToggleButton_Latching_UI::digitalRead(int pin_i) {
	if(pin_i!=pin)
		return -1;

	if(!set2input)
		return 0;

	if(state)
		return 1;
	else
		return 0;
}

int ToggleButton_Latching_UI::analogRead(int pin_i) {
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

void ToggleButton_Latching_UI::pinMode(char pin_i, char mode) {
	if(pin_i!=pin)
		return;
	if(mode==OUTPUT)
		set2input=false;
	else
		set2input=true;
}
