
#define MOTOR_RIGHT_PIN 11


void hardware_setup(){
	new DCMotor_Transistor(11, "right_motor", 2.5, -2.1415, 1);
  new DCMotor_Transistor(10, "left_motor", 2.5, -2.1415, 1);
  new VisionSensor(9, "left_IR", 0.5);
  new VisionSensor(8, "right_IR", 0.5);
  new ProximitySensor(7, "front_IR", 0.16, 0.3);
  new ServoMotor(3, "servo_joint", 2.5, -2.1415, 0.016);
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
