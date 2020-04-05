#include <string>

class VrepMotor {       // The class
 
  public:             // Access specifier
    
    void pinMode(char, char);
    void digitalWrite(int, int);
    VrepMotor(int, std::string);
    VrepMotor(){};

  private:
  	int pin;        // Pin of the Arduino where is connected
    std::string name;  // Name of the joint in Vrep
    int handle=-1; //
    bool set2output=false;

};