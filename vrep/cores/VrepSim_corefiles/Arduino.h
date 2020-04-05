//This file replaces the normal Arduino.h




#ifndef Arduino_h
#define Arduino_h

//#include <stdint.h>
#include "SerialClass.h"
#include "main.h"
#include "SimTime.h"

typedef char byte;



#define OUTPUT 0
#define INPUT 1

#define LOW 0
#define HIGH 1

#define LED_BUILTIN 13

//Vrep preprocesor defines
#define NON_MATLAB_PARSING
#define MAX_EXT_API_CONNECTIONS 255
#define DO_NOT_USE_SHARED_MEMORY



SerialClass Serial;
#endif





