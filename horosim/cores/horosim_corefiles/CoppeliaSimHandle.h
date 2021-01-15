#ifndef COPPELIASIM_HANDLE
#define COPPELIASIM_HANDLE

#include <string>
#include <vector>
#include "HardwareDevice.h"


class CoppeliaSimHandle : public HardwareDevice{       // The class
 
  public:             // Access specifier
    
    CoppeliaSimHandle( std::string);
    CoppeliaSimHandle(){};

  protected:
    int handle=-1; //

};

#endif