#ifndef LED_UI
#define LED_UI

#include <string>
#include "HardwareDevice.h"
#include "ArduinoUno.h"
#include "Defines.h"
#include "imgui/imgui.h"


class Led_UI : public HardwareDevice {      // The class

public:             // Access specifier

	Led_UI(int, std::string, enum  LedColor);
	Led_UI(int, std::string);
	Led_UI() {};
	void updateGUI();
	void digitalWrite(int, int);
    void analogWrite(int, int);
    void pinMode(char, char);

protected:
	enum LedColor color=LED_RED;
	int state;
	int pin;        // Pin of the Arduino where is connected
	bool set2output=false;
private:

};

#endif