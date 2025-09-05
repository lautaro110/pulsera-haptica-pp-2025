int motorPin=5;
int boton = 2;
void setup() {
 pinMode(motorPin, OUTPUT); 
 pinMode(boton, INPUT_PULLUP);

}

void loop() {
  if (digitalRead(boton)==LOW){
     
       analogWrite(motorPin,255);
       delay(200);
       analogWrite(motorPin,0);
       delay(150);
      }
    
   else{
    analogWrite(motorPin,0);
}
}
