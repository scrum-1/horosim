//This file replaces the normal Arduino.h
#ifndef Arduino_h
#define Arduino_h

//#include <stdint.h>
#include "ArduinoUno.h"
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
#include "Potentiometer_UI.h"
#include "PushButton_Momentary_UI.h"
#include "ToggleButton_Latching_UI.h"


#include <vector>


SerialClass Serial;

using namespace std;

#endif
