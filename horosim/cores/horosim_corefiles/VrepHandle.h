#ifndef VREP_HANDLE
#define VREP_HANDLE

#include <string>
#include <vector>
#include "HardwareDevice.h"


class VrepHandle : public HardwareDevice{       // The class
 
  public:             // Access specifier
    
    VrepHandle( std::string);
    VrepHandle(){};

  protected:
    int handle=-1; //

};

#endif