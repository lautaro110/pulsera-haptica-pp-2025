#include <Wire.h>
#include <SparkFun_ADXL345.h>

ADXL345 adxl;

void setup() {
    Serial.begin(9600);
    Serial.println("Iniciando ADXL345...");

    adxl.powerOn();
    adxl.setRangeSetting(16); // ±16g

    Serial.println("Sensor listo.");
    Serial.println("Rangos posibles: ±2, ±4, ±8, ±16 g");
    Serial.println("Rango actual: ±16 g");
    Serial.println();
}

void loop() {
    int x_raw, y_raw, z_raw;
    adxl.readAccel(&x_raw, &y_raw, &z_raw);

    float scaleFactor = 16.0 / 512.0; // ±16g → 512 counts/g
    float x_g = x_raw * scaleFactor;
    float y_g = y_raw * scaleFactor;
    float z_g = z_raw * scaleFactor;

    Serial.print("Raw: "); Serial.print(x_raw);
    Serial.print(", "); Serial.print(y_raw);
    Serial.print(", "); Serial.println(z_raw);

    Serial.print("g:   "); Serial.print(x_g, 2);
    Serial.print(", "); Serial.print(y_g, 2);
    Serial.print(", "); Serial.println(z_g, 2);

    // Gráfico de barras simple
    Serial.print("X: "); for (int i = 0; i < abs(x_g); i++) Serial.print("#"); Serial.println();
    Serial.print("Y: "); for (int i = 0; i < abs(y_g); i++) Serial.print("#"); Serial.println();
    Serial.print("Z: "); for (int i = 0; i < abs(z_g); i++) Serial.print("#"); Serial.println("\n");

    delay(200);
}
