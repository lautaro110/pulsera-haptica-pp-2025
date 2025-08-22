int motorPin=7;
void setup() {
 pinMode(motorPin,OUTPUT); 

}

void loop() {
for (int i = 0;i<=255; i +=7){
  analogWrite(motorPin, i);
  delay(300);

}
for (int i = 255;i>=0; i -=7){
  analogWrite(motorPin, i);
  delay(300);
}
}