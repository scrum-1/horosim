#ifndef TOGGLEBUTTON_LATCHING_UI
#define TOGGLEBUTTON_LATCHING_UI

#include <string>
#include "HardwareDevice.h"
#include "ArduinoUno.h"
#include "Defines.h"
#include "imgui/imgui.h"


class ToggleButton_Latching_UI : public HardwareDevice {      // The class

public:             // Access specifier

	ToggleButton_Latching_UI(int, std::string, enum ButtonType);
	ToggleButton_Latching_UI() {};
	void updateGUI();
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