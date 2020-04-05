class Servo {       // The class
 
  public:             // Access specifier
    
   void write(int);
   void attach(int);
    
   Servo(){};
  private:
  	int pin;        // Pin of the Arduino where is connected
    int handle=-1;        // Handle of the Vrep joint
    bool initialized=false; //Specifies if the servo is connected at the write pin 
};