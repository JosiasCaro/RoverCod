#include "Cortador.h"

Cortador::Cortador(int pinPasto) : _pinPasto(pinPasto), _pasto(false) {
    pinMode(_pinPasto, OUTPUT);
}

bool Cortador::cortar() {
    if (_pasto) {
        digitalWrite(_pinPasto, LOW);
        _pasto = false;
    } else {
        digitalWrite(_pinPasto, HIGH);
        _pasto = true;
    }
    return _pasto;
}