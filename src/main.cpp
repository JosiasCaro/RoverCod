#include <Arduino.h>
#include "rover.h"


int velocidad = 200;
int espera = 1500;

Rover rover(4, 16,17, 5);

void InicializarSerial(){
  Serial.begin(9600);
}

void setup() {
  InicializarSerial();
}

void loop() {
  rover.avanzar(velocidad);
  Serial.println("Motor Adelante");
  delay(espera);
  rover.retroceder(velocidad);
  Serial.println("Motor Atras");
  delay(espera);
  rover.girarDerecha(velocidad);
  Serial.println("Motor Derecha");
  delay(espera);
  rover.girarIzquierda(velocidad);
  Serial.println("Motor Izquierda");
  delay(espera);
  rover.detenerse();
  Serial.println("Motor quieto");
  delay(espera);
}
