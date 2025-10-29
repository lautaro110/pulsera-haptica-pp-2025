#include <Wire.h>
#include <MPU6050_tockn.h>

// === Inicialización del MPU ===
MPU6050 mpu(Wire);

// === Pines de motores ===
int motor1 = 5;
int motor2 = 6;
int motor3 = 9;
int motor4 = 10;

// === Pines de LEDs ===
int led1 = 11;
int led2 = 12;
int led3 = 13;
int led4 = 8;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.begin();
  delay(1000);  // Esperar a que el sensor se estabilice
  mpu.calcGyroOffsets(true); // Calibración rápida

  // Configurar pines de salida
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(motor3, OUTPUT);
  pinMode(motor4, OUTPUT);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

  Serial.println("✅ MPU6050 inicializado correctamente");
}

void loop() {
  mpu.update();
  
  float anguloY = mpu.getAngleY(); // Eje de inclinación frontal
  Serial.print("Ángulo Y: ");
  Serial.println(anguloY);

  // --- Detectar inclinación ---
  if (anguloY > 10) {  // Vaso inclinado hacia arriba
    encenderMotores(1, 2);
  } 
  else if (anguloY < -10) { // Vaso inclinado hacia abajo
    encenderMotores(3, 4);
  } 
  else { // Nivelado
    apagarTodo();
  }

  delay(200);
}

void encenderMotores(int m1, int m2) {
  apagarTodo(); // Apagar primero todo
  switch (m1) {
    case 1: analogWrite(motor1, 255); digitalWrite(led1, HIGH); break;
    case 2: analogWrite(motor2, 255); digitalWrite(led2, HIGH); break;
    case 3: analogWrite(motor3, 255); digitalWrite(led3, HIGH); break;
    case 4: analogWrite(motor4, 255); digitalWrite(led4, HIGH); break;
  }
  switch (m2) {
    case 1: analogWrite(motor1, 255); digitalWrite(led1, HIGH); break;
    case 2: analogWrite(motor2, 255); digitalWrite(led2, HIGH); break;
    case 3: analogWrite(motor3, 255); digitalWrite(led3, HIGH); break;
    case 4: analogWrite(motor4, 255); digitalWrite(led4, HIGH); break;
  }
}

void apagarTodo() {
  analogWrite(motor1, 0); digitalWrite(led1, LOW);
  analogWrite(motor2, 0); digitalWrite(led2, LOW);
  analogWrite(motor3, 0); digitalWrite(led3, LOW);
  analogWrite(motor4, 0); digitalWrite(led4, LOW);
}
