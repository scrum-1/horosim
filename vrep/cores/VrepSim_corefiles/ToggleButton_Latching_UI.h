#ifndef TOGGLEBUTTON_LATCHING_UI
#define TOGGLEBUTTON_LATCHING_UI

#include <string>
#include "VrepHandle.h"
#include "ArduinoUno.h"
#include "Defines.h"


class ToggleButton_Latching_UI : public VrepHandle {      // The class

public:             // Access specifier

	ToggleButton_Latching_UI(int, std::string, enum ButtonType);
	ToggleButton_Latching_UI() {};
	int digitalRead(int);
    int analogRead(int);
    void pinMode(char, char);
	bool* getState();

protected:
	enum ButtonType b_type=PULL_DOWN;
	bool state;
	int pin;        // Pin of the Arduino where is connected
	bool set2input=true;
private:

};

#endif