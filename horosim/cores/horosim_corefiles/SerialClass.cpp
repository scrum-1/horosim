#include "SerialClass.h"
#include <iostream>  

void SerialClass::begin(int /*baudrate*/){
	initialized=true;
}

int SerialClass::write(std::string str){
	if(initialized){
		std::printf("%s", str.c_str());
		return str.size();
	}
	return 0;
}
int SerialClass::write(int val){
	if(initialized){
		std::printf("%d", val);
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