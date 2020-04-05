/*
  main.cpp - Main loop for Arduino sketches
  Copyright (c) 2005-2013 Arduino Team.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

//#include <stdio.h>
//#include <unistd.h>
#include <iostream>
#include <main.h>
#include "VrepMotor.h"
#include "VrepSensor.h"
#include <signal.h>
#include "SimTime.h"

using namespace std;

extern "C" {
    #include "extApi.h"
}


VrepMotor* left_motor;
VrepMotor* right_motor;
VrepSensor* right_sensor;
VrepSensor* left_sensor;
VrepSensor* front_sensor;
int clientID = -1;
bool stop_sim = false;



// Declared weak in Arduino.h to allow user redefinitions.
int atexit(void (* /*func*/ )()) { return 0; }

void signal_callback_handler(int signum) {
  printf("\n");
  stop_sim=true;
}
void stop_simulation(){
   //cout << "Caught signal " << signum << endl;
  //Switch off motors and wait 2 seconds
    digitalWrite(10, 0);
    digitalWrite(11, 0);

    int ret=simxStopSimulation(clientID, simx_opmode_oneshot);
    if (ret==simx_return_ok||ret==simx_return_novalue_flag)
      printf("ARDUINO2VREP: Simulation stopped!\n");
    else
      printf("ARDUINO2VREP: Remote API function call returned with error code, when requestin simulation stop: %d\n",ret);

    delay(100);
    // Now close the connection to V-REP:   
    simxFinish(clientID);
    printf("ARDUINO2VREP: Simulation finished!\n");


   // Terminate program
   exit(0);
}



int main(void)
{

  signal(SIGINT, signal_callback_handler);
  timeInit();

  clientID=simxStart((simxChar*)"127.0.0.1",19997,true,true,2000,5);
  if (clientID!=-1)
    clientID=simxStart((simxChar*)"10.0.2.2",19997,true,true,2000,5);
  
  if (clientID!=-1){
    printf("ARDUINO2VREP: Connected to remote API server\n");

    // Now try to retrieve data in a blocking fashion (i.e. a service call):
    int objectCount;
    int* objectHandles;
    int ret=simxGetObjects(clientID,sim_handle_all,&objectCount,&objectHandles,simx_opmode_blocking);
    if (ret==simx_return_ok)
      printf("ARDUINO2VREP: Number of objects in the scene: %d\n",objectCount);
    else
      printf("ARDUINO2VREP: Remote API function call returned with error code: %d\n",ret);

    ret=simxStartSimulation(clientID, simx_opmode_oneshot);
    if (ret==simx_return_ok||ret==simx_return_novalue_flag)
      printf("ARDUINO2VREP: Simulation started!\n");
    else
      printf("ARDUINO2VREP: Remote API function call returned with error code, when requestin simulation start: %d\n",ret);


    left_motor = new VrepMotor(10, "left_motor");
    right_motor = new VrepMotor(11, "right_motor");
    left_sensor = new VrepSensor(9, "left_IR", VisionSensor);
    right_sensor = new VrepSensor(8, "right_IR", VisionSensor);
    front_sensor = new VrepSensor(7, "front_IR", ProximitySensor);

    //Switch off motors and wait 2 seconds
    digitalWrite(10, 0);
    digitalWrite(11, 0);
    extApi_sleepMs(2000);


    setup();
    
    for (;;) {
      if(stop_sim)
        stop_simulation();
      loop();
      //if (serialEventRun) serialEventRun();
    }
        
    // Before closing the connection to V-REP, make sure that the last command sent out had time to arrive. You can guarantee this with (for example):
    int pingTime;
    simxGetPingTime(clientID,&pingTime);

    // Now close the connection to V-REP:   
    simxFinish(clientID);
    printf("ARDUINO2VREP: Simulation finished!\n");
    return 0;

  }else{
    printf("ARDUINO2VREP: NOT Connected to remote API server\n");
  }
}



int vrep_setup(){
 //        // Now retrieve streaming data (i.e. in a non-blocking fashion):
 //        int startTime=extApi_getTimeInMs();
 //        int mouseX;
 //        simxGetIntegerParameter(clientID,sim_intparam_mouse_x,&mouseX,simx_opmode_streaming); // Initialize streaming
 //        while (extApi_getTimeDiffInMs(startTime) < 5000)
 //        {
 //            ret=simxGetIntegerParameter(clientID,sim_intparam_mouse_x,&mouseX,simx_opmode_buffer); // Try to retrieve the streamed data
 //            if (ret==simx_return_ok) // After initialization of streaming, it will take a few ms before the first value arrives, so check the return code
 //                printf("Mouse position x: %d\n",mouseX); // Mouse position x is actualized when the cursor is over V-REP's window
 //        }
        
 //        // Now send some data to V-REP in a non-blocking fashion:
 //        simxAddStatusbarMessage(clientID,"Hello V-REP!",simx_opmode_oneshot);

	// printf("NOT Connected to remote API server\n");
 //    return(0);
}

void pinMode(char pin, char mode){

  right_sensor->pinMode(pin, mode);
  left_sensor->pinMode(pin, mode);
  front_sensor->pinMode(pin, mode);
  left_motor->pinMode(pin, mode);
  right_motor->pinMode(pin, mode);
	
}
void digitalWrite(char a, char b){

  left_motor->digitalWrite(a, b);
  right_motor->digitalWrite(a, b);
	//printf("This C program will exit in 10 seconds.\n"); 
	
}

int digitalRead(int a){

  int result = right_sensor->digitalRead(a);
  if(result>=0)
    return result;
  result = left_sensor->digitalRead(a);
  if(result>=0)
    return result;
  result = front_sensor->digitalRead(a);
  if(result>=0)
    return result;
  //printf("This C program will exit in 10 seconds.\n"); 

  //TODO: Give random number
  return 0;
  
}



