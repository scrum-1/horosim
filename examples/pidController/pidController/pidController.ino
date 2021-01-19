//Pin definitions 
#define MOTOR_IN1_PIN 11
#define MOTOR_IN2_PIN 12
#define MOTOR_EN_PIN 10 //Needs a PWM pin
#define POT_PIN A0      //Needs an analog pin
#define POT_T1 A1       //Needs an analog pin
#define POT_T2 A2       //Needs an analog pin
#define POT_P A3        //Needs an analog pin

//Global variables
long timeInit;
int target;  
float p;
bool goToTarget1;

void hardware_setup(){
  new DCMotor_Hbridge(MOTOR_IN1_PIN, MOTOR_IN2_PIN, 
        MOTOR_EN_PIN, "motor_joint", 2.5, -2.5, 1);
  new Potentiometer(POT_PIN, "motor_joint", 6.3);
  new Potentiometer_UI(POT_T1, "Target 1", 0.3);
  new Potentiometer_UI(POT_T2, "Target 2", 0.7);
  new Potentiometer_UI(POT_P, "p value", 0.1);
}

void setup() {
  // initilize the pins for the H-Bridge as outputs
  pinMode(MOTOR_IN1_PIN, OUTPUT);
  pinMode(MOTOR_IN2_PIN, OUTPUT);
  pinMode(MOTOR_EN_PIN, OUTPUT);

  digitalWrite(MOTOR_EN_PIN, HIGH); //Enable the H-Bridge

  timeInit = millis();
  target = analogRead(POT_T1);
  goToTarget1 = true;
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
    p = float(analogRead(POT_P))/10.0; //Update p
    if(goToTarget1){
      target = analogRead(POT_T2); //Update target 2
      goToTarget1 = false;
    } else {
      target = analogRead(POT_T1); //Update target 1
      goToTarget1 = true;
    }
  }
  
  

}
