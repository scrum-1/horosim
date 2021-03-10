#define MOTOR_RIGHT_PIN 11
#define MOTOR_LEFT_PIN 10
#define IR_LEFT_PIN 9
#define IR_RIGHT_PIN 8
#define US_PIN 8
#define SERVO_PIN 3

void hardware_setup(){
	new DCMotor_Transistor(MOTOR_RIGHT_PIN, "right_motor", 
	      2.5, -2.1415, 1);
  new DCMotor_Transistor(MOTOR_LEFT_PIN, "left_motor", 
        2.5, -2.1415, 1);
  new VisionSensor(IR_LEFT_PIN, "left_IR", 0.5);
  new VisionSensor(IR_RIGHT_PIN, "right_IR", 0.5);
  new ProximitySensor(US_PIN, "front_IR", 0.16, 0.3);
  new ServoMotor(3, "servo_joint", 
        2.5, -2.1415, 0.016);
}

void setup() {
  // put your setup code here, to run once:
pinMode(MOTOR_RIGHT_PIN, OUTPUT);
}
void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(MOTOR_RIGHT_PIN, LOW);
  delay(1000);
  digitalWrite(MOTOR_RIGHT_PIN, HIGH);
  delay(1000);
}
