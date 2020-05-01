#ifndef VREP_HANDLE
#define VREP_HANDLE

#include <string>
#include <vector>




enum HardwareType {VrepHandle_t=0, VrepMotor_t=1, DCMotor_Transistor_t=2, DCMotor_Hbridge_t=3, StepperMotor_t=4, 
  ServoMotor_t=5, VrepSensor_t=10, VisionSensor_t = 11, ProximitySensor_t = 12,
  Potentiometer_UI_t=20, PushButton_Momentary_UI_t=21, PushButton_Latching_UI_t=22, ToggleButton_Momentary_UI_t=23, ToggleButton_Latching_UI_t=24, 
  Led_UI_t=25}; 

class VrepHandle {       // The class
 
  public:             // Access specifier
    
    VrepHandle( std::string);
    VrepHandle(){};
    virtual void pinMode(char, char){}; 
    virtual void digitalWrite(int, int){};
    virtual void analogWrite(int, int){};
    virtual int digitalRead(int){return -1;};
    virtual int analogRead(int){return -1;};
    virtual int getServoPin(){return -1;};
    virtual double getServoReduction(){return -1;};

    enum HardwareType getType(){return type;};
    std::string getHandleName(){return handle_name;};

  protected:
  	std::string handle_name;  // Name of the joint/sensor in Vrep
    int handle=-1; //
    enum HardwareType type=VrepHandle_t;


};

#endif