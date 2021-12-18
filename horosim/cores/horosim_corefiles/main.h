#include <stdint.h>

enum Endings {NONE=0, NL=1, CR=2, NLCR=3};


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



