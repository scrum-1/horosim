#include "HardwareDevice.h"
#include "Defines.h"
#include <string>


extern "C" {
    #include "extApi.h"
}


HardwareDevice::HardwareDevice(std::string str){
  	handle_name=str;
  	type=HardwareDevice_t;
 }
