#include "Rover.h"

Rover::Rover(int pinIzquierdaA, int pinIzquierdaB, int pinDerechaA, int pinDerechaB, int pinJoystick)
    : _ruedaIzquierda(pinIzquierdaA, pinIzquierdaB), _ruedaDerecha(pinDerechaA, pinDerechaB), _joystick(pinJoystick) {
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

void Rover::actualizar(int sensor){
    if(sensor > 0){
        std::array<int, 4> motorSpeed = _joystick.actualizacion();
        if(motorSpeed[0] > 0){
            avanzar(motorSpeed[0]);
        }
        if(motorSpeed[1] > 0){
            retroceder(motorSpeed[1]);
        }
        if(motorSpeed[2] > 0){
            girarIzquierda(motorSpeed[2]);
        }
        if(motorSpeed[3] > 0){
            girarDerecha(motorSpeed[3]);
        }
        if(motorSpeed[0] == 0 || motorSpeed[1] == 0 || motorSpeed[2] == 0 || motorSpeed[3] == 0){
            detenerse();
        }
    }
}