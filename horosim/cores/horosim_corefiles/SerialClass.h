
#include <string>

class SerialClass {       // The class
 
  public:             // Access specifier
    
    int available();

    int write(std::string);
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
    
    void begin(int);
    SerialClass(){};

  private:
  	int pin_tx;        // Pin of the Arduino where is connected
  	int pin_rx;        // Pin of the Arduino where is connected
    bool initialized = false;
};

