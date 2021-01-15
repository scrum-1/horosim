#include "VrepHandle.h"
#include "Defines.h"
#include <string>


extern "C" {
    #include "coppeliasim/remoteapi/extApi.h"
}
extern int clientID;


VrepHandle::VrepHandle(std::string str):HardwareDevice{str}{
	type=VrepHandle_t;
  	int error=simxGetObjectHandle(clientID, handle_name.c_str(), &handle, simx_opmode_blocking);
  	//printf(name.c_str());
  	if(error!=simx_return_ok){
  		printf("HoRoSim: Error retrieving the handler of %s, error %d.\n", handle_name.c_str(), error);
  	}else{
  		//printf("Motor handler OK.\n");
  	}

 }
