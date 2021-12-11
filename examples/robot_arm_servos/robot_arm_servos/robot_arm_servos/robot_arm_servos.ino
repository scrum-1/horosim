
#define SERVO_PIN 3
#define SERVO_PIN2 4
#define SERVO_PIN3 5
#define SERVO_PIN4 6
#define POT_T1 A1       //Needs an analog pin
#define POT_T2 A2       //Needs an analog pin
#define POT_T3 A3       //Needs an analog pin
#define POT_T4 A4       //Needs an analog pin
#define US_PIN 2
#define LED_PIN 8

#include <Servo.h>

Servo Servo1;
Servo Servo2;
Servo Servo3;
Servo Servo4;

void hardware_setup(){
  new ServoMotor(SERVO_PIN, "uarm_motor1", 
        10, -2.1415, 1);
  new ServoMotor(SERVO_PIN2, "uarm_motor2", 
        10, -2.1415, 1);
  new ServoMotor(SERVO_PIN3, "uarm_motor3", 
        10, -2.1415, 1);
  new ServoMotor(SERVO_PIN4, "uarmGripper_motor1Method2", 
        10, -2.1415, 0.008, 0);
  new Potentiometer_UI(POT_T1, "Motor Base", 0.5);
  new Potentiometer_UI(POT_T2, "Motor 2", 0.5);
  new Potentiometer_UI(POT_T3, "Motor 3", 0.5);
  new Potentiometer_UI(POT_T4, "Gripper", 0.5);
  new Led_UI(LED_PIN, "Green");
}

void setup() {
  // put your setup code here, to run once:

  pinMode(SERVO_PIN, OUTPUT);
  pinMode(SERVO_PIN2, OUTPUT);
  pinMode(SERVO_PIN3, OUTPUT);
  pinMode(SERVO_PIN4, OUTPUT);
  Servo1.attach(SERVO_PIN);
  Servo2.attach(SERVO_PIN2);
  Servo3.attach(SERVO_PIN3);
  Servo4.attach(SERVO_PIN4);
  pinMode(LED_PIN, OUTPUT);
}


void loop() {
  int target1 = analogRead(POT_T1);
  int target2 = analogRead(POT_T2);
  int target3 = analogRead(POT_T3);
  int target4 = analogRead(POT_T4);
  Servo1.write(map(target1, 0, 1023, 0, 170));
  Servo2.write(map(target2, 0, 1023, 0, 170));
  Servo3.write(map(target3, 0, 1023, 0, 170));
  Servo4.write(map(target4, 0, 1023, 0, 170));
}
