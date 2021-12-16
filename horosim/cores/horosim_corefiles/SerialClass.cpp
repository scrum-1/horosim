#include "SerialClass.h"
#include <iostream>  
#include <cstring>

extern char serial_buffer[];
extern unsigned int serial_buffer_len;
extern unsigned int serial_buffer_index;
extern char serial_out[];

void SerialClass::begin(unsigned long bauds){
	initialized=true;
	baudrate=bauds;
}

int SerialClass::available(){
	return serial_buffer_len;
}

int SerialClass::read(){
	if(serial_buffer_len>0){
		char data = serial_buffer[serial_buffer_index];
		serial_buffer_index++;
		serial_buffer_len--;
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
		std::printf("%s", tmp);
		std::strncat(serial_out, tmp, 2);
		printf("WRITE_CHAR");
		return 1;
	}
	return 0;
}
/*
int SerialClass::write(int val){
	if(initialized){
		std::printf("%d", val);
		printf("WRITE_INT");
		return std::to_string(val).size();
	}
	return 0;
}
int SerialClass::write(float val){
	if(initialized){
		std::printf("%f", val);
		return std::to_string(val).size();
	}
	return 0;
}
int SerialClass::write(long val){
	if(initialized){
		std::printf("%ld", val);
		return std::to_string(val).size();
	}
	return 0;
}
int SerialClass::write(double val){
	if(initialized){
		std::printf("%f", val);
		return std::to_string(val).size();
	}
	return 0;
}

int SerialClass::write(char* buf, int len){
	if(initialized){
		for (int i = 0; i < len; ++i){
			std::printf("%c", buf[i]);
		}
		std::strncat(serial_out, buf, strlen(buf));
		printf("WRITE_BUF");
		return len;
	}
	return 0;
}


//TODO: Printf is not the same as write, but it should be OK for now:
int SerialClass::print(std::string str){
	return write(str);
}
int SerialClass::print(int val){
	return write(val);
}
int SerialClass::print(float val){
	return write(val);
}
int SerialClass::print(long val){
	return write(val);
}
int SerialClass::print(double val){
	return write(val);
}

int SerialClass::print(char* buf, int len){
	return write(buf, len);
}

//Println
int SerialClass::println(std::string str){
	int bytes=write(str);
	bytes+=write("\n");
	return bytes;
}
int SerialClass::println(int val){
	int bytes=write(val);
	bytes+=write("\n");
	return bytes;
}
int SerialClass::println(float val){
	int bytes=write(val);
	bytes+=write("\n");
	return bytes;
}
int SerialClass::println(long val){
	int bytes=write(val);
	bytes+=write("\n");
	return bytes;
}
int SerialClass::println(double val){
	int bytes=write(val);
	bytes+=write("\n");
	return bytes;
}

int SerialClass::println(char* buf, int len){
	int bytes=write(buf, len);
	bytes+=write("\n");
	return bytes;
}
*/