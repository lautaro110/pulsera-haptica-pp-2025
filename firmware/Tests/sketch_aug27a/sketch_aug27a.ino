int motorPin=5;
void setup() {
 pinMode(motorPin, OUTPUT); 

}

void loop() {
 for (int i = 0; i<= 255; i +=5) {
   analogWrite(motorPin, i);
  delay(30);
  } 
  for (int i= 255; i>= 0; i -=5) {
    analogWrite(motorPin, i);
  delay(30);
 
}
}
