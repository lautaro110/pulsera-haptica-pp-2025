int motorPin=5;
int boton = 2;
void setup() {
 pinMode(motorPin, OUTPUT); 
 pinMode(boton, INPUT_PULLUP);

}

void loop() {
  if (digitalRead(boton)==LOW){
     for (int potencia = 0; potencia<= 255;  potencia++) {
       analogWrite(motorPin, potencia);
      delay(30);
      } 
    
  }else{
    analogWrite(motorPin,0);
}
}
