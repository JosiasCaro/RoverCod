#include "Rover.h"

Rover::Rover(int pinIzquierdaA, int pinIzquierdaB, int pinDerechaA, int pinDerechaB)
    : _ruedaIzquierda(pinIzquierdaA, pinIzquierdaB), _ruedaDerecha(pinDerechaA, pinDerechaB) {

}

void Rover::avanzar(int velocidad) {
    _ruedaIzquierda.girar(velocidad, 0);
    _ruedaDerecha.girar(velocidad, 0);
}

void Rover::retroceder(int velocidad) {
    _ruedaIzquierda.girar(0, velocidad);
    _ruedaDerecha.girar(0, velocidad);
}

void Rover::detenerse() {
    _ruedaIzquierda.detenerse();
    _ruedaDerecha.detenerse();
}

void Rover::girarIzquierda(int velocidad) {
    _ruedaIzquierda.girar(velocidad, 0);
    _ruedaDerecha.girar(0, velocidad);
}

void Rover::girarDerecha(int velocidad) {
    _ruedaIzquierda.girar(0, velocidad);
    _ruedaDerecha.girar(velocidad, 0);
}