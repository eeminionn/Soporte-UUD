#include <FastLED.h>

#define NUM_LEDS 30
#define DATA_PIN 4
CRGB leds[NUM_LEDS];

const int sensorPin = 5;  // Pin digital donde está conectado el sensor IR
int contador = 1;
bool esperandoLiberacion = false;

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.clear();
  FastLED.show();
}

void loop() {
  int estado = digitalRead(sensorPin);

  if (estado == LOW && !esperandoLiberacion) {
    // Señal detectada por el IR (por lo general, LOW = obstáculo detectado)
    esperandoLiberacion = true;
    contador++;
    if (contador > 3) contador = 0;
    Serial.print("Contador: ");
    Serial.println(contador);
  }

  if (estado == HIGH && esperandoLiberacion) {
    // IR ya no detecta obstáculo → se libera
    esperandoLiberacion = false;
  }

  // Actualización visual según contador
  if (contador == 0) {
    FastLED.clear();
  } else if (contador == 1) {
    fill_solid(leds, NUM_LEDS, CRGB::Green);
  } else if (contador == 2) {
    fill_solid(leds, NUM_LEDS, CRGB::Yellow);
  } else if (contador == 3) {
    fill_solid(leds, NUM_LEDS, CRGB::Red);
  }

  FastLED.show();
  delay(10);  // Estabilidad de lectura
}
