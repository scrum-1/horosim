#include <stdint.h>

int test(void);
void pinMode(char, char);
void digitalWrite(char, char);
void analogWrite(char, int);
int digitalRead(int);
int analogRead(int);


void setup(void);
void loop(void);
void hardware_setup(void);
void stop_simulation(void);
long map(long x, long in_min, long in_max, long out_min, long out_max);

