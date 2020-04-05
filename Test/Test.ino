
#define MOTOR_RIGHT_PIN 11

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
