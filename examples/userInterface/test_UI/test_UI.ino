

void hardware_setup(){

    new Potentiometer_UI(A0, "Potentiometer 1", 0.3);
    new Potentiometer_UI(A1, "Potentiometer 2", 0.7);
    new PushButton_Momentary_UI(A2, "Button 1", PULL_UP);
    new ToggleButton_Latching_UI(A3, "Button 2", PULL_DOWN);
    new Led_UI(3, "Led for potentiometer test");
    new Led_UI(4, "Led for button1 test", LED_GREEN);
    new Led_UI(5, "Led for button2 test", LED_GREEN);
    
}

void setup() {
  // put your setup code here, to run once:
  //Configure the LEDs as outputs
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  //Send the values read by serial:
  Serial.write("Sensors: ");
  Serial.write( digitalRead(A2));
  Serial.write(" ");
  Serial.write( digitalRead(A3));
  Serial.println(" ");

  //Update LEDs:
  digitalWrite(4, digitalRead(A2));
  digitalWrite(5, digitalRead(A3));
  analogWrite(3, analogRead(A0)/4);
  delay(50);
}
