#include "SerialClass.h"
#include <iostream>  
#include <cstring>

void SerialClass::begin(unsigned long bauds){
	initialized=true;
	switch(bauds) {
	case 4800:
		baudrate = BR4800;
		break;
	case 9600:
		baudrate = BR9600;
		break;
	case 14400:
		baudrate = BR14400;
		break;
	case 19200:
		baudrate = BR19200;
		break;
	case 28800:
		baudrate = BR28800;
		break;
	case 38400:
		baudrate = BR38400;
		break;
	case 57600:
		baudrate = BR57600;
		break;
	case 115200:
		baudrate = BR115200;
		break;
	default:
		baudrate = BR_OTHER;
	}
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

size_t SerialClass::write(uint8_t val){
	if(initialized){
		char tmp[2];
		if(baudrate == baudSerialMonitor)
			tmp[0]=val;
		else
			tmp[0]=rand()%127;
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




