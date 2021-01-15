//Pin definitions 
#define MOTOR_IN1_PIN 11
#define MOTOR_IN2_PIN 12
#define MOTOR_EN_PIN 10 //Needs a PWM pin
#define POT_PIN A0      //Needs an analog pin

//Global variables
long timeInit;
int target = 200;
//Try differnt values of the p parameter (0.1, 1, 10, 100)...
float p=10;

void hardware_setup(){
  new DCMotor_Hbridge(MOTOR_IN1_PIN, MOTOR_IN2_PIN, MOTOR_EN_PIN, "motor_joint", 2.5, -2.5, 1);
  new Potentiometer(POT_PIN, "motor_joint", 6.3);
}

void setup() {
  // initilize the pins for the H-Bridge as outputs
  pinMode(MOTOR_IN1_PIN, OUTPUT);
  pinMode(MOTOR_IN2_PIN, OUTPUT);
  pinMode(MOTOR_EN_PIN, OUTPUT);

  digitalWrite(MOTOR_EN_PIN, HIGH); //Enable the H-Bridge

  timeInit = millis();
}


void loop() {
  // put your main code here, to run repeatedly:
 
  long timeElapsed = 0;
  
  timeElapsed = millis() - timeInit;
  if (timeElapsed < 3000) {
    int error = target - analogRead(POT_PIN);
    int pwm = abs(error * p);
    if(pwm>255) 
      pwm=255; 
    analogWrite(MOTOR_EN_PIN, pwm);
    if (error>0){
      digitalWrite(MOTOR_IN1_PIN, LOW);
      digitalWrite(MOTOR_IN2_PIN, HIGH);
    }else{
      digitalWrite(MOTOR_IN1_PIN, HIGH);
      digitalWrite(MOTOR_IN2_PIN, LOW);
    }
    delay(10);
    
  } else{
    timeInit = millis();
    if(target==200){
      target=800;
    } else {
      target = 200;
    }
  }
  
  

}
