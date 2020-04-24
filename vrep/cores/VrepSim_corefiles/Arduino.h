//This file replaces the normal Arduino.h
#ifndef Arduino_h
#define Arduino_h

//#include <stdint.h>
#include "SerialClass.h"
#include "main.h"
#include "SimTime.h"
#include "Defines.h"
#include "DCMotor_Transistor.h"
#include "DCMotor_Hbridge.h"
#include "StepperMotor.h"
#include "ServoMotor.h"
#include "VisionSensor.h"
#include "ProximitySensor.h"
#include <vector>

SerialClass Serial;

using namespace std;

//Vector with the handles of joints and sensors
extern std::vector<VrepHandle*> handles;

#endif
