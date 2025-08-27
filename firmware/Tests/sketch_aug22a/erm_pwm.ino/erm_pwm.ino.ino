const int pin_motor=10;
int valorPWM=0;
void setup() {
 Serial.begin(9600);
 pinMode(pin_motor, OUTPUT); 

}

void loop() {
 for (valorPWM = 0; valorPWM <= 255; valorPWM += 5) {
   analogWrite(pin_motor, valorPWM);
  
     analogWrite(pin_motor, 64);
  delay(30);
    analogWrite(pin_motor, 0);
  delay(300);
  

 
  
  Serial.println(pin_motor);
  delay(50); 
}
}