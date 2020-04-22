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
#include "DCMotor_Transistor.h"
#include "StepperMotor.h"
#include "VrepSensor.h"
#include <signal.h>
#include "SimTime.h"
#include <vector>
#include "VrepHandle.h"

using namespace std;

extern "C" {
    #include "extApi.h"
}

#define LINE_FOLLOWING_ROBOT

std::vector<VrepHandle*> handles;
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

  int port=19997;
  int commThreadCycleInMs=5;
  clientID=simxStart((simxChar*)"127.0.0.1",port,true,true,2000,commThreadCycleInMs);
  //If we could not connect to localhost, it should be a VM. Try default gateway
  if (clientID==-1)
    clientID=simxStart((simxChar*)"10.0.2.2",port,true,true,2000,commThreadCycleInMs);
  
  if (clientID!=-1){
    printf("ARDUINO2VREP: Connected to remote API server, clientID: %d\n", clientID);

    // Now try to retrieve data in a blocking fashion (i.e. a service call):
    int objectCount;
    int* objectHandles;
    int ret=simxGetObjects(clientID,sim_handle_all,&objectCount,&objectHandles,simx_opmode_blocking);
    if (ret==simx_return_ok)
      printf("ARDUINO2VREP: Number of objects in the scene: %d\n",objectCount);
    else
      printf("ARDUINO2VREP: Remote API function call returned with error code: %d\n",ret);

    
    #ifdef LINE_FOLLOWING_ROBOT
    DCMotor_Transistor* right_motor = new DCMotor_Transistor(11, "right_motor", 2.5, -2.1415, 1);
    DCMotor_Transistor* left_motor = new DCMotor_Transistor(10, "left_motor", 2.5, -2.1415, 1);
    //StepperMotor* left_motor = new StepperMotor(10, 1, "left_motor", 2.5, -2.1415, 1);
    //StepperMotor* right_motor = new StepperMotor(11, 2, "right_motor", 2.5, -2.1415, 1);
    VrepSensor* left_sensor = new VrepSensor(9, "left_IR", VisionSensor);
    VrepSensor* right_sensor = new VrepSensor(8, "right_IR", VisionSensor);
    VrepSensor* front_sensor = new VrepSensor(7, "front_IR", ProximitySensor);
    handles.push_back(left_motor);
    handles.push_back(right_motor);
    handles.push_back(left_sensor);
    handles.push_back(right_sensor);
    handles.push_back(front_sensor);

    ret=simxStartSimulation(clientID, simx_opmode_oneshot);
    if (ret==simx_return_ok||ret==simx_return_novalue_flag)
      printf("ARDUINO2VREP: Simulation started!\n");
    else
      printf("ARDUINO2VREP: Remote API function call returned with error code, when requestin simulation start: %d\n",ret);


    //Switch off motors and wait 2 seconds
    //digitalWrite(10, 0); //DOne in VrepMotor at init
    //digitalWrite(11, 0); //DOne in VrepMotor at init
    #endif
    

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
     return(0);
}

void pinMode(char pin, char mode){
  for(vector<VrepHandle*>::iterator it=handles.begin(); it!=handles.end(); ++it){
    
    (*it)->pinMode(pin, mode);
  }
}
void digitalWrite(char a, char b){
  for(vector<VrepHandle*>::iterator it=handles.begin(); it!=handles.end(); ++it){  
    (*it)->digitalWrite(a, b);
  }
}

void analogWrite(char a, int b){
  for(vector<VrepHandle*>::iterator it=handles.begin(); it!=handles.end(); ++it){  
    (*it)->analogWrite(a, b);
  }
}

int digitalRead(int a){
  int result;
  for(vector<VrepHandle*>::iterator it=handles.begin(); it!=handles.end(); ++it){  
    result=(*it)->digitalRead(a);
    if(result>=0)
      return result;
  }
  //TODO: Give random number
  return 0;
}



