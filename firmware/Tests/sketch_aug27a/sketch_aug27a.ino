const int pin_motor = 10;
int valorPWM = 0;
void setup() {
  Serial.begin(9600);
  pinMode(pin_motor, OUTPUT);

}

void loop() {
  for (valorPWM = 0; valorPWM <= 255; valorPWM += 5) {
    analogWrite(pin_motor, valorPWM);


    analogWrite(pin_motor, valorPWM);
    delay(300);
   analogWrite(pin_motor, valorPWM);
     delay(30);

    Serial.println(valorPWM);
    delay(50);
  }
}
