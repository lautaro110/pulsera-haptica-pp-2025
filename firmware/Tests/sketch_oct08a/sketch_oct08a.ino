/*  DETECCIÓN Y POSICIÓN - ADXL (analógico)
    - Auto-calibra los centros al arrancar
    - Filtra lecturas (media móvil)
    - Detecta si el sensor está presente
    - Informa: Arriba / Abajo / Izquierda / Derecha / Plano
*/

const int PIN_X = A0;
const int PIN_Y = A1;
const int PIN_Z = A2;

// ------- Parámetros de calibración y filtro -------
const int CAL_SAMPLES = 200;    // lecturas para calibrar al inicio
const int FILTRO_TAM   = 8;     // tamaño media móvil (mayor = más estable, más lento)
const int MIN_VALID = 50;       // rango mínimo aceptable para considerar "conectado"
const int MAX_VALID = 1000;     // rango máximo aceptable

// buffers media móvil
int bufX[FILTRO_TAM], bufY[FILTRO_TAM], bufZ[FILTRO_TAM];
int idxX = 0, idxY = 0, idxZ = 0;
long sumX = 0, sumY = 0, sumZ = 0;

// centros medidos en calibración
float centroX = 512.0;
float centroY = 512.0;
float centroZ = 512.0;

// desviaciones estándar de la calibración (para umbral dinámico)
float stdX = 0, stdY = 0, stdZ = 0;

// umbral para decidir posición (se calcula tras calibrar)
float umbral = 60.0; // valor por defecto; se ajustará automáticamente

// lecturas filtradas actuales
int valX = 0, valY = 0, valZ = 0;

void setup() {
  Serial.begin(9600);
  delay(200);
  Serial.println(F("=== Inicio chequeo acelerometro (analógico) ==="));
  Serial.println(F("Realizando calibracion... manten el sensor en la posicion de reposo (pulso estable)"));
  calibrarSensor();
  filtroInit(); // inicializa buffers del filtro con la lectura actual
  Serial.println(F("Calibracion completa."));
  Serial.print(F("CentroX=")); Serial.print(centroX);
  Serial.print(F("  CentroY=")); Serial.print(centroY);
  Serial.print(F("  CentroZ=")); Serial.println(centroZ);
  Serial.print(F("StdX=")); Serial.print(stdX,2);
  Serial.print(F("  StdY=")); Serial.print(stdY,2);
  Serial.print(F("  StdZ=")); Serial.println(stdZ,2);

  // Calcula umbral dinámico: usar la mayor desviación encontrada * factor
  float maxStd = max(max(stdX, stdY), stdZ);
  umbral = max(40.0, maxStd * 2.0); // al menos 40, o 2x desviación
  Serial.print(F("Umbral dinamico establecido en: "));
  Serial.println(umbral);
  Serial.println(F("=============================================="));
}

void loop() {
  // Leer con filtro
  valX = leerFiltroX();
  valY = leerFiltroY();
  valZ = leerFiltroZ();

  // Comprobar si los valores están en rango plausible
  bool plausible = (valX > MIN_VALID && valX < MAX_VALID)
                 && (valY > MIN_VALID && valY < MAX_VALID)
                 && (valZ > MIN_VALID && valZ < MAX_VALID);

  if (!plausible) {
    Serial.println(F("⚠️  Lecturas fuera de rango -> comprobar conexiones o alimentacion"));
    Serial.print(F("X: ")); Serial.print(valX);
    Serial.print(F("  Y: ")); Serial.print(valY);
    Serial.print(F("  Z: ")); Serial.println(valZ);
    delay(600);
    return;
  }

  // calcular desplazamientos respecto al centro calibrado
  float dx = valX - centroX;
  float dy = valY - centroY;
  float dz = valZ - centroZ;

  // decidir eje dominante
  float absx = abs(dx), absy = abs(dy), absz = abs(dz);
  String posicion
