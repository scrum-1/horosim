#include <string>

enum SensorType {VisionSensor = 0, ProximitySensor = 1}; 

class VrepSensor {       // The class
 
  public:             // Access specifier
    
    void pinMode(char, char);
    int digitalRead(int);
    VrepSensor(int, std::string, enum SensorType);
    VrepSensor(){};

  private:
  	int pin;        // Pin of the Arduino where is connected
    std::string name;  // Name of the sensor in Vrep
    int handle=-1; //
    SensorType type;
    bool set2input=true;
    float readVisionSensor();
    float readProximitySensor();

};