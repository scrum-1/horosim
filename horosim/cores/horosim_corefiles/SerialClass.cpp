#include "SerialClass.h"
#include <iostream>  
#include <cstring>
#include <mutex> 

void SerialClass::begin(unsigned long bauds){
	initialized=true;
	baudrate=bauds;
}

int SerialClass::available(){
	return serial_in_len;
}

int SerialClass::read(){
	if(serial_in_len>0){
		char data = serial_in[serial_in_index++];
		serial_in_index=serial_in_index%SERIAL_IN_MAX_LEN;
		serial_in_len--;
		return data;
	}else{
		return -1;
	}
}


void SerialClass::flush(void){}

//Get the number of bytes (characters) available for writing in the serial buffer without blocking the write operation.
int SerialClass::availableForWrite(void)
{
  return SERIAL_TX_BUFFER_SIZE - 1;
}

//Returns the next byte (character) of incoming serial data without removing it from the internal serial buffer. 
//That is, successive calls to peek() will return the same character, as will the next call to read().
int SerialClass::peek(void){
	//FIXME 
	return 0;
}
/*
int SerialClass::write(std::string str){
	if(initialized){
		std::printf("%s", str.c_str());
		std::strncat(serial_out, str.c_str(), strlen(str.c_str()));
		return str.size();
	}
	return 0;
}*/

size_t SerialClass::write(uint8_t val){
	if(initialized){
		char tmp[2];
		tmp[0]=val;
		tmp[1]='\0';
		//printf("WRITE_CHAR\n");
		//std::printf("%s", tmp);
		mtx.lock();
		std::strncat(serial_out, tmp, 2);
		mtx.unlock();
		
		return 1;
	}
	return 0;
}




