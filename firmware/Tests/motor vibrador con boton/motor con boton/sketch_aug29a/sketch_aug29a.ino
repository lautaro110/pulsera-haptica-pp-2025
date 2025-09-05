int motorPin=5;
int boton = 2;
void setup() {
 pinMode(motorPin, OUTPUT); 
 pinMode(boton, INPUT_PULLUP);

}

void loop() {
  if (digitalRead(boton)==LOW){
     for (int i = 0; i<= 255; i +=5) {
       analogWrite(motorPin, i);
      delay(30);
      } 
      for (int i= 255; i>= 0; i -=5) {
        analogWrite(motorPin, i);
      delay(30);
      }
  }else{
    analogWrite(motorPin,0);
}
}
