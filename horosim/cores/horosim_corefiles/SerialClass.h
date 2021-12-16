
#include <string>
#include "arduino/Stream.h"

#define SERIAL_TX_BUFFER_SIZE 64
#define SERIAL_RX_BUFFER_SIZE 64

class SerialClass : Stream {       // The class
 
  public:             // Access specifier
  	SerialClass(){};

  	//Definitions taken from Arduino´s HardwareSerial (avr)
    void begin(unsigned long baud);
    //void begin(unsigned long, uint8_t);
    void end();
    virtual int available(void);
    virtual int peek(void);
    virtual int read(void);
    virtual int availableForWrite(void);
    virtual void flush(void);
    virtual size_t write(uint8_t);
    inline size_t write(unsigned long n) { return write((uint8_t)n); }
    inline size_t write(long n) { return write((uint8_t)n); }
    inline size_t write(unsigned int n) { return write((uint8_t)n); }
    inline size_t write(int n) { return write((uint8_t)n); }
    using Print::write; // pull in write(str) and write(buf, size) from Print
    operator bool() { return true; }
    /*
    int available();

    int write(std::string);
    int write(char);
    int write(int);
    int write(float);
		int write(long);
		int write(double);
		int write(char* , int);
		int print(std::string);
    int print(int);
    int print(float);
		int print(long);
		int print(double);
		int print(char* , int);
		int println(std::string);
		int println(int);
    int println(float);
		int println(long);
		int println(double);
		int println(char* , int);

		char read();
    
*/
  private:
  	int pin_tx;        // Pin of the Arduino where is connected
  	int pin_rx;        // Pin of the Arduino where is connected
    bool initialized = false;
    long baudrate; 		//Baudrate for the serial monitor
};

