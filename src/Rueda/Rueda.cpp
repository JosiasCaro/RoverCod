#include "Rueda.h"

Rueda::Rueda(int pin_ruedaA, int pin_ruedaB) {
    _pin_asignadoA = pin_ruedaA;
    _pin_asignadoB = pin_ruedaB;
    inicializar();
};

void Rueda::inicializar() {
    pinMode(_pin_asignadoA, OUTPUT);
    pinMode(_pin_asignadoB, OUTPUT);
}

void Rueda::girar(int velocidadA, int velocidadB) {
    analogWrite(_pin_asignadoA, velocidadA);
    analogWrite(_pin_asignadoB, velocidadA);
};

void Rueda::detenerse() {
    analogWrite(_pin_asignadoA, LOW);
    analogWrite(_pin_asignadoB, LOW);
};
