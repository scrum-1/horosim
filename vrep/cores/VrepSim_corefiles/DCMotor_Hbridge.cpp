#include "DCMotor_Hbridge.h"
#include <string>


extern "C" {
#include "extApi.h"
}
extern int clientID;


DCMotor_Hbridge::DCMotor_Hbridge(int in1_pin_i, int in2_pin_i, int en_pin_i,std::string str, float force, float speed, float reduction):
	VrepMotor{str, force, speed, reduction} {
	in1_pin=in1_pin_i;
	in2_pin=in2_pin_i;
	en_pin=en_pin_i;
	type=DCMotor_Hbridge_t;
	enableControlLoop(false);
	handles.push_back(this);
}

void DCMotor_Hbridge::pinMode(char pin_i, char mode) {
	if(pin_i!=in1_pin) {
		if(mode==OUTPUT)
			in1_set2output=true;
		else
			in1_set2output=false;
	}

	if(pin_i!=in2_pin) {
		if(mode==OUTPUT)
			in2_set2output=true;
		else
			in2_set2output=false;
	}

	if(pin_i!=en_pin) {
		if(mode==OUTPUT)
			en_set2output=true;
		else
			en_set2output=false;
	}
}
void DCMotor_Hbridge::digitalWrite(int pin_i, int status) {
	if(pin_i!=in1_pin && pin_i!=in2_pin && pin_i!=en_pin)
		return;

	if(pin_i==in1_pin){
		if(!in1_set2output){
			return;
		}else{
			if(status>0){
				in1=HIGH;
			}else{
				in1=LOW;
			}
		}
	}

	if(pin_i==in2_pin){
		if(!in2_set2output){
			return;
		}else{
			if(status>0){
				in2=HIGH;
			}else{
				in2=LOW;
			}
		}
	}

	if(pin_i==en_pin){
		if(!en_set2output){
			return;
		}
		else{
			//This stops the PWM signal
			pwm=255;
			if(status>0){
				en=HIGH;
			}else{
				en=LOW;
			}

		}
	}

	//Speed if its enabled
	float speed = rpm_max/255*pwm;
	
	if(en){
		if(in1==HIGH && in2==LOW){
			//Forward
			setTargetSpeed(speed);
			return;
		}
		if(in1==LOW && in2==HIGH){
			//Backward
			setTargetSpeed(-1*speed);
			return;
		}
		//Stopped
		setTargetSpeed(0);
	}
}

void DCMotor_Hbridge::analogWrite(int pin_i, int value) {
	if(pin_i!=en_pin)
		return;
	
	if(pin_i==3||pin_i==5||pin_i==6||pin_i==9||pin_i==10||pin_i==11) {
		//analogWrite does calls pinMode directly
		en_set2output=true;
		en=true;
		pwm=value%256;
		float speed = rpm_max/255*pwm;
		if(in1==HIGH && in2==LOW){
			//Forward
			setTargetSpeed(speed);
			return;
		}
		if(in1==LOW && in2==HIGH){
			//Backward
			setTargetSpeed(-1*speed);
			return;
		}
		//Stopped
		setTargetSpeed(0);
	}
}