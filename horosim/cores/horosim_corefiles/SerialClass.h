
#include <string>
#include <mutex> 
#include "arduino/Stream.h"

#define SERIAL_TX_BUFFER_SIZE 64
#define SERIAL_RX_BUFFER_SIZE 64
const unsigned int SENT_BUF_LEN = 256;
const unsigned int SERIAL_IN_MAX_LEN = 1024;

extern char serial_in[];
extern unsigned int serial_in_len;
extern unsigned int serial_in_index;
extern char serial_out[];

extern std::mutex mtx;

class SerialClass : public Stream {       // The class
 
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
    
  private:
  	int pin_tx;        // Pin of the Arduino where is connected
  	int pin_rx;        // Pin of the Arduino where is connected
    bool initialized = false;
    long baudrate; 		//Baudrate for the serial monitor
    long serialMonitorBauds;
    
};

