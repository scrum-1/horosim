#ifndef VREP_HANDLE
#define VREP_HANDLE

#include <string>


class VrepHandle {       // The class
 
  public:             // Access specifier
    
    VrepHandle( std::string);
    VrepHandle(){};
    virtual void pinMode(char, char){}; 
    virtual void digitalWrite(int, int){};
    virtual int digitalRead(int){return -1;};

  protected:
  	std::string handle_name;  // Name of the joint/sensor in Vrep
    int handle=-1; //

};

#endif