#include "DCMotor_Transistor.h"
#include "Defines.h"
#include <string>


extern "C" {
    #include "extApi.h"
}
extern int clientID;


VrepMotor::VrepMotor(std::string str, double force_max_i, double rpm_max_i, double reduction_i):VrepHandle{str}{
	force_max=force_max_i*reduction_i;
	rpm_max=rpm_max_i/reduction_i;
	reduction=reduction_i;
	enableMotor(true);
	setMaxForce();
	setTargetSpeed(0);
 }

int VrepMotor::setTargetSpeed(float speed){
	int error=simxSetJointTargetVelocity(clientID, handle, speed, simx_opmode_oneshot);
	if(error>simx_return_novalue_flag){
  		printf("ARDUINO2VREP: Error setting the motor speed, error %d, handle %d, joint %s.\n", error, handle, handle_name.c_str());
  	}else{
  		//printf("Speed set correctly.\n");
  	}
  	return error;
 }

int VrepMotor::setMaxForce(){

	int error=simxSetJointForce(clientID, handle, force_max, simx_opmode_oneshot);
	if(error>simx_return_novalue_flag){
  		printf("ARDUINO2VREP: Error setting the motor max force, error %d, handle %d, joint %s.\n", error, handle, handle_name.c_str());
  	}else{
  		//printf("Speed set max force.\n");
  	}
  	return error;
}

int VrepMotor::enableMotor(bool enable){
	int enable_int=0;
	if(enable)
		enable_int=1;
 	int error=simxSetObjectIntParameter(clientID, handle, JOINTINTPARAM_MOTOR_ENABLED, enable_int, simx_opmode_oneshot);
 	if(error>simx_return_novalue_flag){
  		printf("ARDUINO2VREP: Error setting the motor max force, error %d, handle %d, joint %s.\n", error, handle, handle_name.c_str());
  	}else{
  		//printf("Enable motor correctly.\n");
  	}
  	return error;
}