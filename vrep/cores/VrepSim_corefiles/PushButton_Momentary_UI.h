#ifndef PUSHBUTTON_MOMENTARY_UI
#define PUSHBUTTON_MOMENTARY_UI

#include <string>
#include "VrepHandle.h"
#include "ArduinoUno.h"
#include "Defines.h"


class PushButton_Momentary_UI : public VrepHandle {      // The class

public:             // Access specifier

	PushButton_Momentary_UI(int, std::string, enum ButtonType);
	PushButton_Momentary_UI() {};
	int digitalRead(int);
    int analogRead(int);
    void pinMode(char, char);
	void setPushed();
	void setReleased();


protected:
	enum ButtonType b_type=PULL_DOWN;
	bool state;
	int pin;        // Pin of the Arduino where is connected
	bool set2input=true;
private:

};

#endif