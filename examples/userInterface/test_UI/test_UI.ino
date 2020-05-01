

void hardware_setup(){

    new Potentiometer_UI(A0, "Potentiometer 1", 0.3);
    new Potentiometer_UI(A1, "Potentiometer 2", 0.7);
    new PushButton_Momentary_UI(A2, "Button 1", PULL_UP);
    new ToggleButton_Latching_UI(A3, "Button 2", PULL_DOWN);
    new Led_UI(3, "Led for test");
    
}

void setup() {
  // put your setup code here, to run once:
  pinMode(3, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.write("Sensors: ");
  Serial.write( digitalRead(A2));
  Serial.write(" ");
  Serial.write( digitalRead(A3));
  Serial.println(" ");
  
  analogWrite(3, analogRead(A0)/4);
  delay(50);
}
