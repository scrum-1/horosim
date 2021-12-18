#include <stdint.h>

enum Endings {NONE=0, NL=1, CR=2, NLCR=3};
enum BaudRate {BR4800=0, BR9600=1, BR14400=2, BR19200=3, BR28800=4,
               BR38400=5, BR57600=6, BR115200=7};
               
//Arduino API functions
void pinMode(char, char);
void digitalWrite(char, char);
void analogWrite(char, int);
int digitalRead(int);
int analogRead(int);
long map(long x, long in_min, long in_max, long out_min, long out_max);


//Arduino sketch functions
void setup(void);
void loop(void);
void hardware_setup(void);


//HoRoSim internal functions
void serialMonitor();
void stop_simulation(void);
int test(void);
void simulator_loop();
void updateInBuffer(char[], Endings, long); 



