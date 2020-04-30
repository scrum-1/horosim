#ifndef POTENTIOMETER_UI
#define POTENTIOMETER_UI

#include <string>
#include "VrepHandle.h"
#include "ArduinoUno.h"


class Potentiometer_UI : public VrepHandle {      // The class

public:             // Access specifier

	Potentiometer_UI(int, std::string, float);
	Potentiometer_UI() {};
	int digitalRead(int);
    int analogRead(int);
    void pinMode(char, char);
	void setPotVal(float);
	float* getPotPointer();

protected:
	float potVal;
	int pin;        // Pin of the Arduino where is connected
	bool set2input=true;
private:

};

#endif