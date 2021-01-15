#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include <string>
#include "CoppeliaSimHandle.h"
#include "ArduinoUno.h"


class Potentiometer : public CoppeliaSimHandle {      // The class

public:             // Access specifier

	Potentiometer(int, std::string, float);
	Potentiometer() {};
	int digitalRead(int);
    int analogRead(int);
    void pinMode(char, char);
	void setPotVal(float);
	float* getPotPointer();

protected:
	float potVal;
	int pin;        // Pin of the Arduino where is connected
	bool set2input=true;
	float range;
private:

	float readPot();

};

#endif