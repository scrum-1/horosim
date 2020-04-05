#include "SimTime.h"

using namespace std;

// #include <stdio.h>
// #include <unistd.h>
// #include <iostream>
// #include <time.h>

#include <chrono>



std::chrono::time_point<std::chrono::steady_clock> start;

void timeInit(){
	start = chrono::steady_clock::now();
}

void delay(long ms){
  	struct timespec tim;

  	tim.tv_sec = ms/1000;
  	tim.tv_nsec = (ms%1000)*1000000;
  	//printf("tv_sec: %d\n", tim.tv_sec);
  	//printf("tv_nsec: %d\n", tim.tv_nsec);
  	nanosleep(&tim, NULL);	
}

void delayMicroseconds(long us){
  	struct timespec tim;

  	tim.tv_sec = us/1000000;
  	tim.tv_nsec = (us%1000000)*1000;
  	//printf("tv_sec: %d\n", tim.tv_sec);
  	//printf("tv_nsec: %d\n", tim.tv_nsec);
  	nanosleep(&tim, NULL);  
}

//TODO: This should return unsigned long, but triggers an error
long millis(){
  	auto end = chrono::steady_clock::now();
  	return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}

//TODO: This should return unsigned long, but triggers an error
long micros(){
    auto end = chrono::steady_clock::now();
    return chrono::duration_cast<chrono::microseconds>(end - start).count();
}