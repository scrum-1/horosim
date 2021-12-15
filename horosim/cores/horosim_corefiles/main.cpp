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

#define HOROSIM_VERSION "0.1.0"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glut.h"
#include "imgui/imgui_impl_opengl2.h"
#include <thread>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif


//#include <stdio.h>
//#include <unistd.h>
#include <iostream>
#include <main.h>
#include "Potentiometer.h"
#include "DCMotor_Transistor.h"
#include "DCMotor_Hbridge.h"
#include "StepperMotor.h"
#include "CoppeliaSimSensor.h"
#include <signal.h>
#include "SimTime.h"
#include <vector>
#include "CoppeliaSimHandle.h"
#include "Potentiometer_UI.h"
#include "PushButton_Momentary_UI.h"
#include "ToggleButton_Latching_UI.h"
#include "Led_UI.h"


#ifdef _MSC_VER
#pragma warning (disable: 4505) // unreferenced local function has been removed
#endif

// Our state
static bool show_serial_monitor = true;
const unsigned int SENT_BUF_LEN = 256;
const unsigned int SERIAL_BUF_MAX_LEN = 1024;
unsigned int serial_buffer_index = 0;
unsigned int serial_buffer_len = 0;
char serial_buffer[SERIAL_BUF_MAX_LEN];
char serial_sent_buffer[SENT_BUF_LEN];
static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

using namespace std; 

extern "C" {
#include "coppeliasim/remoteapi/extApi.h"
}

//Vector with the handles of joints and sensors
std::vector<HardwareDevice*> handles;

int clientID = -1;
bool stop_sim = false;


void my_display_code()
{

  
  //if (serialEventRun) serialEventRun();


  // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
  {
    //static float f = 0.0f;
    //static int counter = 0;

    ImGui::Begin("HoRoSim User Interface");                   // Create a window called HoRoSim User Interface" and append into it.

    //ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
    //ImGui::Checkbox("Another Window", &show_serial_monitor);

    //ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
    //ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

    //if(ImGui::Button("Button"))                             // Buttons return true when clicked (most widgets return true when edited/activated)
    //  counter++;
    //ImGui::ArrowButton("TEST", ImGuiDir_Left);
    //ImGui::SameLine();
    //ImGui::Text("counter = %d", counter);
    //static bool b=true;
    //ToggleButton("TEST", &b);
    //LED("TEST LED", &b);

    //Lets find the User Interface devices (Switches, Potentiometers, Leds)
    for(vector<HardwareDevice*>::iterator it=handles.begin(); it!=handles.end(); ++it) {
      //printf("Type: %d\n", (*it)->getType());
      auto type=(*it)->getType();
      if(type==Potentiometer_UI_t) {
        Potentiometer_UI& pot_UI = dynamic_cast<Potentiometer_UI&>(**it); // downcast
        ImGui::SliderFloat(pot_UI.getHandleName().c_str(), pot_UI.getPotPointer(), 0.0f, 1.0f);
      }

      if(type==PushButton_Momentary_UI_t) {
        PushButton_Momentary_UI& button_momentary_UI = dynamic_cast<PushButton_Momentary_UI&>(**it); // downcast
        ImGui::Button(button_momentary_UI.getHandleName().c_str());
        if(ImGui::IsItemActive())
          button_momentary_UI.setPushed();
        else
          button_momentary_UI.setReleased();
      }
      if(type==ToggleButton_Latching_UI_t) {
        ToggleButton_Latching_UI& tbutton_lat_UI = dynamic_cast<ToggleButton_Latching_UI&>(**it); // downcast
        tbutton_lat_UI.updateGUI();
      }
      if(type==Led_UI_t) {
        Led_UI& led_UI = dynamic_cast<Led_UI&>(**it); // downcast
        led_UI.updateGUI();
      }
      
    }

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
  }

  // 3. Show another simple window.
  if(show_serial_monitor)
  {
    serialMonitor();
  }
}

void serialMonitor()
{

  const char* ending_items[] = { "No line ending", "Newline", "Carriage return", "Both NL & CR"};
  static int ending_current = 0;
  const char* baud_items[] = { "4800 baud", "9600 baud", "14400 baud", "19200 baud", "28800 baud",
                               "38400 baud","57600 baud", "115200 baud"
                             };
  static int baud_current = 0;
  unsigned int bytes = 0;

  ImGui::Begin("HoRoSim Serial Monitor");   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
  ImGui::PushItemWidth(ImGui::GetContentRegionAvailWidth()-45);
  ImGui::InputText("##sent_msg", serial_sent_buffer, IM_ARRAYSIZE(serial_sent_buffer));
  ImGui::SameLine();
  if(ImGui::Button("Send")) {
    //Find how many bytes are in the message and store the bytes in the serial buffer
    for(unsigned int i = 0; i < SENT_BUF_LEN; ++i) {
      if(serial_sent_buffer[i] == 0) {
        bytes = i;
        break;
      } else {
        serial_buffer[(serial_buffer_index + serial_buffer_len)%SERIAL_BUF_MAX_LEN] = serial_sent_buffer[i];
        serial_buffer_len++;
        if(serial_buffer_len>SERIAL_BUF_MAX_LEN)
          serial_buffer_len = SERIAL_BUF_MAX_LEN;
      }
    }
    if(bytes>0) {
      switch(ending_current) {
      case 0:
        break;
      case 1:
        serial_buffer[(serial_buffer_index + serial_buffer_len)%SERIAL_BUF_MAX_LEN] = '\n';
        serial_buffer_len++;
        break;
      case 2:
        serial_buffer[(serial_buffer_index + serial_buffer_len)%SERIAL_BUF_MAX_LEN] = '\r';
        serial_buffer_len++;
        break;
      case 3:
        serial_buffer[(serial_buffer_index + serial_buffer_len)%SERIAL_BUF_MAX_LEN] = '\n';
        serial_buffer_len++;
        serial_buffer[(serial_buffer_index + serial_buffer_len)%SERIAL_BUF_MAX_LEN] = '\r';
        serial_buffer_len++;
        break;
      }
    }
    printf("characters in sent buffer: %d\n", bytes);
    printf("characters in serial buffer: %d\n", serial_buffer_len);
    printf("serial buffer: %s\n", serial_buffer);
    printf("serial buffer index: %d\n", serial_buffer_index);
  }

  ImGui::Spacing (); //Add vertical spacing
  ImGui::Indent(ImGui::GetContentRegionAvailWidth()*0.4);
  ImGui::PushItemWidth(ImGui::GetContentRegionAvailWidth()*0.5);
  ImGui::Combo("##endings", &ending_current, ending_items, IM_ARRAYSIZE(ending_items));
  ImGui::SameLine(); //HelpMarker("Using t");
  ImGui::PushItemWidth(ImGui::GetContentRegionAvailWidth());
  ImGui::Combo("##baud", &baud_current, baud_items, IM_ARRAYSIZE(baud_items));
  //ImGui::SameLine(); //HelpMarker("Using t");


  //if(ImGui::Button("Close Me"))
  //show_serial_monitor = false;
  ImGui::Indent(0);
  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
  ImGui::End();

}
void glut_display_func()
{
  // Start the Dear ImGui frame
  ImGui_ImplOpenGL2_NewFrame();
  ImGui_ImplGLUT_NewFrame();

  my_display_code();

  // Rendering
  ImGui::Render();
  ImGuiIO& io = ImGui::GetIO();
  glViewport(0, 0, (GLsizei)io.DisplaySize.x, (GLsizei)io.DisplaySize.y);
  glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
  glClear(GL_COLOR_BUFFER_BIT);
  //glUseProgram(0); // You may want this if using this code in an OpenGL 3+ context where shaders may be bound, but prefer using the GL3+ code.
  ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

  glutSwapBuffers();
  glutPostRedisplay();
}


void simulator_loop(){
  while(!stop_sim) {
    //Update the simulator and Arduino
    loop();
  }
}



// Declared weak in Arduino.h to allow user redefinitions.
//Comented as it does not link on Windows
//int atexit(void (* /*func*/)()) { return 0; }

void signal_callback_handler(int signum) {
  printf("Interrupt signal received. Signal: %d\n", signum);
  stop_sim=true;
}

void stop_simulation() {
  //cout << "Caught signal " << signum << endl;

  int ret=simxStopSimulation(clientID, simx_opmode_oneshot);
  if(ret==simx_return_ok||ret==simx_return_novalue_flag)
    printf("HoRoSim: Simulation stopped!\n");
  else
    printf("HoRoSim: Remote API function call returned with error code, when requestin simulation stop: %d\n",ret);

  // Before closing the connection to V-REP, make sure that the last command sent out had time to arrive. You can guarantee this with (for example):
  int pingTime;
  simxGetPingTime(clientID,&pingTime);

  // Now close the connection to V-REP:
  simxFinish(clientID);
  printf("HoRoSim: Simulation finished!\n");
}



int main(int argc, char** argv)
{


  //Connect to Coppelia Sim
  signal(SIGINT, signal_callback_handler);
  simTime_timeInit();

  printf("HoRoSim %s\n", HOROSIM_VERSION);

  int port=19997;
  int commThreadCycleInMs=5;
  clientID=simxStart((simxChar*)"127.0.0.1",port,true,true,2000,commThreadCycleInMs);
  //If we could not connect to localhost, it should be a VM. Try default gateway
  if(clientID==-1)
    clientID=simxStart((simxChar*)"10.0.2.2",port,true,true,2000,commThreadCycleInMs);
  if(clientID==-1){
    port=10000; //Another port to try
    clientID=simxStart((simxChar*)"127.0.0.1",port,true,true,2000,commThreadCycleInMs);
  }
  if(clientID==-1)
    clientID=simxStart((simxChar*)"10.0.2.2",port,true,true,2000,commThreadCycleInMs);

  if(clientID==-1) {
    printf("HoRoSim: NOT Connected to remote API server\n");
    return -1;
  }

  #ifdef __MINGW32__
  //Commented as the deactivation of the buffer for the stdout fixed this problem
  //Do this after checking that CoppeliaSim is connected. Thus, the previous error appears in the Arduino IDE in Windows
  //FILE* fp;
  //AllocConsole();
  //AttachConsole(ATTACH_PARENT_PROCESS);
  //freopen_s(&fp, "CONIN$", "r", stdin);
  //freopen_s(&fp, "CONOUT$", "w", stdout);
  //freopen_s(&fp, "CONOUT$", "w", stderr);
  #endif

  //Desactivate buffer for stdout, avoids to have to flush 
  setvbuf(stdout, NULL, _IONBF, 0); 

  printf("HoRoSim: Connected to remote API server, clientID: %d\n", clientID);



  // Now try to retrieve data in a blocking fashion (i.e. a service call):
  int objectCount;
  int* objectHandles;
  int ret=simxGetObjects(clientID,sim_handle_all,&objectCount,&objectHandles,simx_opmode_blocking);
  if(ret==simx_return_ok)
    printf("HoRoSim: Number of objects in the scene: %d\n",objectCount);
  else
    printf("HoRoSim: Remote API function call returned with error code: %d\n",ret);

  //Load the hardware from the Arduino sketch and store it in the handles vector
  hardware_setup();

  ret=simxStartSimulation(clientID, simx_opmode_oneshot);
  if(ret==simx_return_ok||ret==simx_return_novalue_flag)
    printf("HoRoSim: Simulation started!\n");
  else
    printf("HoRoSim: Remote API function call returned with error code, when requestin simulation start: %d\n",ret);

  extApi_sleepMs(2000);

  setup();




  // Create GLUT window
  glutInit(&argc, argv);
#ifdef __FREEGLUT_EXT_H__
  glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
#endif
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE);
  glutInitWindowSize(600, 400);
  glutCreateWindow("HoRoSim");

  // Setup GLUT display function
  // We will also call ImGui_ImplGLUT_InstallFuncs() to get all the other functions installed for us,
  // otherwise it is possible to install our own functions and call the imgui_impl_glut.h functions ourselves.
  glutDisplayFunc(glut_display_func);

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;
  //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  //ImGui::StyleColorsClassic();

  // Setup Platform/Renderer bindings
  ImGui_ImplGLUT_Init();
  ImGui_ImplGLUT_InstallFuncs();
  ImGui_ImplOpenGL2_Init();

  // Load Fonts
  // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
  // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
  // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
  // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
  // - Read 'docs/FONTS.txt' for more instructions and details.
  // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
  //io.Fonts->AddFontDefault();
  //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
  //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
  //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
  //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
  //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
  //IM_ASSERT(font != NULL);

  std::thread (simulator_loop).detach();
  glutMainLoop();

  //Wait to finish the simulator loop
  //simulator.join();

  // Cleanup
  ImGui_ImplOpenGL2_Shutdown();
  ImGui_ImplGLUT_Shutdown();
  ImGui::DestroyContext();

  stop_simulation();

  return 0;

}



int coppeliasim_setup() {
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

void pinMode(char pin, char mode) {
  for(vector<HardwareDevice*>::iterator it=handles.begin(); it!=handles.end(); ++it) {

    (*it)->pinMode(pin, mode);
  }
}
void digitalWrite(char a, char b) {
  for(vector<HardwareDevice*>::iterator it=handles.begin(); it!=handles.end(); ++it) {
    (*it)->digitalWrite(a, b);
  }
}

void analogWrite(char a, int b) {
  for(vector<HardwareDevice*>::iterator it=handles.begin(); it!=handles.end(); ++it) {
    (*it)->analogWrite(a, b);
  }
}

int digitalRead(int a) {
  int result;
  for(vector<HardwareDevice*>::iterator it=handles.begin(); it!=handles.end(); ++it) {
    result=(*it)->digitalRead(a);
    if(result>=0)
      return result;
  }
  //TODO: Give random number
  return 0;
}

int analogRead(int a) {
  int result;
  for(vector<HardwareDevice*>::iterator it=handles.begin(); it!=handles.end(); ++it) {
    result=(*it)->analogRead(a);
    if(result>=0)
      return result;
  }
  //TODO: Give random number
  return 0;
}

long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


