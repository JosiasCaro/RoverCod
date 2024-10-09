#include "Rueda.h"

#define pin_M1A 4
#define pin_M1B 16

Rueda::Rueda(int pin_ruedaA, int pin_ruedaB) {
    _pin_asignadoA = pin_ruedaA;
    _pin_asignadoB = pin_ruedaB;
    inicializar();
};

void Rueda::inicializar() {
    pinMode(pin_M1A, OUTPUT);
    pinMode(pin_M1B, OUTPUT);
}

void Rueda::girar(int velocidadA, int velocidadB) {
    analogWrite(pin_M1A, velocidadA);
    analogWrite(pin_M1B, velocidadB);
};

void Rueda::detenerse() {
    analogWrite(pin_M1A, LOW);
    analogWrite(pin_M1B, LOW);
};
