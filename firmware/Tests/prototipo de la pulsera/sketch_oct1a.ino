int motorPin = 5;
int boton    = 2;

bool motorEncendido = false; // estado del motor
bool botonPrevio    = HIGH;  // guarda el estado anterior del botón

// --- ADAPTADO: Acelerómetro analógico (ej. ADXL335) ---
int accX = A0; // eje X del acelerómetro
int accY = A1; // eje Y del acelerómetro
int accZ = A2; // eje Z del acelerómetro

void setup() {
  pinMode(motorPin, OUTPUT); 
  pinMode(boton, INPUT_PULLUP);
  analogWrite(motorPin, 0); // motor apagado al inicio

  Serial.begin(9600); // para monitorear acelerómetro
}

void loop() {
  bool estadoBoton = digitalRead(boton);

  // Detectar flanco: botón recién apretado
  if (botonPrevio == HIGH && estadoBoton == LOW) {
    // si estaba apagado -> encender motor
    if (!motorEncendido) {
      analogWrite(motorPin, 255);
      motorEncendido = true;
    } else {
      // si estaba encendido -> apagar gradualmente
      for (int i = 255; i >= 0; i -= 5) {
        analogWrite(motorPin, i);
        delay(30);
      }
      analogWrite(motorPin, 0);
      motorEncendido = false;
    }
  }

  // --- Leer acelerómetro ---
  int valorX = analogRead(accX);
  int valorY = analogRead(accY);
  int valorZ = analogRead(accZ);

  // Mostrar en monitor serie (opcional)
  Serial.print("X: "); Serial.print(valorX);
  Serial.print("  Y: "); Serial.print(valorY);
  Serial.print("  Z: "); Serial.println(valorZ);

  botonPrevio = estadoBoton; // actualizar estado anterior
}
