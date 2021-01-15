#include "StepperMotor.h"
#include "Defines.h"
#include <string>
#include <math.h>
#include "SimTime.h"

extern "C" {
#include "coppeliasim/extApi.h"
}
extern int clientID;

//Vector with the handles of joints and sensors
extern std::vector<HardwareDevice*> handles;

StepperMotor::StepperMotor(int dir_pin_i, int step_pin_i, std::string str, float force, float speed, float reduction):
	VrepMotor{str, force, speed, reduction} {
	dir_pin=dir_pin_i;
	step_pin=step_pin_i;
	enableControlLoop(true);
	float position;
	int error=simxGetJointPosition(clientID, handle, &position,  simx_opmode_streaming);
	if(error>simx_return_novalue_flag) {
		printf("ARDUINO2VREP: Error reading the position of the stepper motor, error %d, handle %d, sensor %s.\n", error, handle, handle_name.c_str());
	}
	handles.push_back(this);

}

void StepperMotor::pinMode(char pin_i, char mode) {
	if(pin_i!=dir_pin&&pin_i!=step_pin)
		return;
	if(pin_i==dir_pin) {
		dir_set2output=false;
		if(mode==OUTPUT) {
			dir_set2output=true;
		}
	}
	if(pin_i==step_pin) {
		step_set2output=false;
		if(mode==OUTPUT) {
			step_set2output=true;
		}
	}
}

void StepperMotor::digitalWrite(int pin_i, int status) {
	//printf("a");
	if(pin_i!=dir_pin&&pin_i!=step_pin)
		return;
	//printf("b");
	if(pin_i==dir_pin) {
		if(!dir_set2output)
			return;
		if(status>0) {
			forward=true;
		} else {
			forward=false;
		}
		return;
	}
	//printf("c");
	float position;
	int error=simxGetJointPosition(clientID, handle, &position, simx_opmode_buffer);
	if(error!=simx_return_ok) {
		printf("ARDUINO2VREP: Error reading the pos of the stepper motor, error %d, handle %d, sensor %s.\n", error, handle, handle_name.c_str());
		//We use the last position that we got
		position=pos;
	}else{
		pos=position;
	}
	if(pin_i==step_pin) {
		if(!step_set2output)
			return;
		if(status>0 && step_value==false) {
			//Rising edge, move one step
			//printf("fff");
			if(forward)
				position+=3.1415/100*reduction;
			else
				position-=3.1415/100*reduction;
			setTargetPosition(position);
			step_value=true;

			delay(1);

		} else {
			step_value=false;
		}
	}
}

void StepperMotor::analogWrite(int pin_i, int value) {
	if(pin_i!=step_pin)
		return;
	if(!step_set2output||!dir_set2output)
		return;
	if(pin_i==3||pin_i==5||pin_i==6||pin_i==9||pin_i==10||pin_i==11) {
		value=value%256;
		setTargetSpeed(rpm_max/2);
	}
}

