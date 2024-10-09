#include <Arduino.h>
#include "Rover/Rover.h"


int velocidad = 200;
int espera = 1500;

Rover rover(12, 13, 14, 27);

void InicializarSerial(){
  Serial.begin(9600);
}

void setup() {
  InicializarSerial();
}

void loop() {
  rover.avanzar(velocidad);
  delay(espera);
  rover.retroceder(velocidad);
  delay(espera);
  rover.girarDerecha(velocidad);
  delay(espera);
  rover.girarIzquierda(velocidad);
  delay(espera);
  rover.detenerse();
  delay(espera);
}
