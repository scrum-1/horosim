class Servo {       // The class
 
  public:             // Access specifier
    
   void write(int);
   void writeMicroseconds(int);
   int read();
   void attach(int);
   bool attached();
   void dettach();

    
   Servo(){};
  private:
  	int pin;        // Pin of the Arduino where is connected
    int handle=-1;        // Handle of the CoppeliaSim joint
    bool initialized=false; //Specifies if the servo is connected at the write pin 
    double reduction=1;
    int currentPos=90; 
    bool isAttached=false;
    double minPos=0;
};