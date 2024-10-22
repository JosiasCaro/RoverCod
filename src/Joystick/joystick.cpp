#include "Joystick.h"

Joystick::Joystick(int pinX, int pinY, int pinLed, Rover* rover) {
    _pinX = pinX;
    _pinY = pinY;
    _pinLed = pinLed;
    _rover = rover;
    _connected = false; 
}

void Joystick::inicializar() {
    pinMode(_pinX, INPUT);
    pinMode(_pinY, INPUT);
    pinMode(_pinLed, OUTPUT);
    onConnectedController(); 
}

void Joystick::procesar() {
    int ejeX = analogRead(_pinX);
    int ejeY = analogRead(_pinY);
  
    if (ejeY < 400) {
        _rover->avanzar(map(ejeY, 400, 0, 0, 255));
    } else if (ejeY > 600) {
        _rover->retroceder(map(ejeY, 600, 1023, 0, 255));
    } else {
        detener();
    }

    if (ejeX < 400) {
        _rover->girarIzquierda(map(ejeX, 400, 0, 0, 255));
    } else if (ejeX > 600) {
        _rover->girarDerecha(map(ejeX, 600, 1023, 0, 255));
    }
}

void Joystick::detener() {
    _rover->detenerse();
}

void Joystick::onConnectedController() {
    _connected = true;
    digitalWrite(_pinLed, HIGH); 
    Serial.println("Controlador conectado");
}

void Joystick::onDisconnectedController() {
    _connected = false;
    digitalWrite(_pinLed, LOW); 
    Serial.println("Controlador desconectado");
}

void Joystick::dumpGamepad() {
    Serial.print("Conectado: ");
    Serial.println(_connected ? "Sí" : "No");
}

void Joystick::ProcessControllers() {
    if (_connected) {
        procesar();
    }
}
