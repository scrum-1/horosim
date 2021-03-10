#define MOTOR_RIGHT_DIR_PIN 11
#define MOTOR_RIGHT_STEP_PIN 10
#define MOTOR_LEFT_DIR_PIN 7
#define MOTOR_LEFT_STEP_PIN 6
#define IR_LEFT_PIN 9
#define IR_RIGHT_PIN 8
#define US_PIN 8
#define SERVO_PIN 3

void hardware_setup(){
  new StepperMotor(MOTOR_RIGHT_DIR_PIN, MOTOR_RIGHT_STEP_PIN, "right_motor", 2.5, -2.1415, 4);
	new StepperMotor(MOTOR_LEFT_DIR_PIN, MOTOR_LEFT_STEP_PIN, "left_motor", 2.5, -2.1415, 4);
  new VisionSensor(IR_LEFT_PIN, "left_IR", 0.5);
  new VisionSensor(IR_RIGHT_PIN, "right_IR", 0.5);
  new ProximitySensor(US_PIN, "front_IR", 0.16, 0.3);
  new ServoMotor(3, "servo_joint", 
        2.5, -2.1415, 0.016);
}

void setup() {
  // put your setup code here, to run once:
}
void loop() {
  // put your main code here, to run repeatedly:

}
