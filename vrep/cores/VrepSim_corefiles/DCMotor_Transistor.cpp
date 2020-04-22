#include "DCMotor_Transistor.h"
#include "Defines.h"
#include <string>


extern "C" {
    #include "extApi.h"
}
extern int clientID;


DCMotor_Transistor::DCMotor_Transistor(int pin_i, std::string str):VrepMotor{str, 2.5, -2.1415, 1}{
  	pin=pin_i; 

 }

void DCMotor_Transistor::pinMode(char pin_i, char mode){
	if(pin_i!=pin)
		return;
	if(mode==OUTPUT)
		set2output=true;
	else
		set2output=false;
}
void DCMotor_Transistor::digitalWrite(int pin_i, int status){
	if(pin_i!=pin)
		return;
	if(!set2output)
		return;

	//TODO: Send command to Vrep
	float speed = 0;
	if(status>0){
		speed=rpm_max;
	}
	setTargetSpeed(speed);
}
