
#define MOTOR_RIGHT_PIN 11


void hardware_setup(){
	DCMotor_Transistor* right_motor = new DCMotor_Transistor(11, "right_motor", 2.5, -2.1415, 1);
    DCMotor_Transistor* left_motor = new DCMotor_Transistor(10, "left_motor", 2.5, -2.1415, 1);
    VisionSensor* left_sensor = new VisionSensor(9, "left_IR", 0.5);
    VisionSensor* right_sensor = new VisionSensor(8, "right_IR", 0.5);
    ProximitySensor* front_sensor = new ProximitySensor(7, "front_IR", 0.16, 0.3);
    ServoMotor* servo_motor = new ServoMotor(3, "servo_joint", 2.5, -2.1415, 1);
   
    handles.push_back(left_motor);
    handles.push_back(right_motor);
    handles.push_back(left_sensor);
    handles.push_back(right_sensor);
    handles.push_back(front_sensor);
    handles.push_back(servo_motor);
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
