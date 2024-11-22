#include "Cortador.h"

Cortador::Cortador(int pinPasto) : _pinPasto(pinPasto), _pasto(false) {
    pinMode(_pinPasto, OUTPUT);
    _pasto = false;
}

bool Cortador::cortar() {
    if (_pasto) {
        Serial.println("Cortadora apagada");
        digitalWrite(_pinPasto, LOW);
        _pasto = false;
    } else {
        Serial.println("Cortando");
        digitalWrite(_pinPasto, HIGH);
        _pasto = true;
    }
    return _pasto;
}