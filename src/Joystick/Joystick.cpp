#include "Joystick.h"
#include <Bluepad32.h>

Joystick::Joystick(int pinX, int pinY, int pinLed, Rover* rover) {
    _pinX = pinX;
    _pinY = pinY;
    _pinLed = pinLed;
    _rover = rover;
    _connected = false;  
    _controller = nullptr;  
}

void Joystick::inicializar() {
    pinMode(_pinX, INPUT);
    pinMode(_pinY, INPUT);
    pinMode(_pinLed, OUTPUT);
    BP32.setup(&onConnectedController, &onDisconnectedController);  
    digitalWrite(_pinLed, LOW); 
}

void Joystick::procesar() {
    BP32.update();  

    if (_controller && _controller->isConnected()) {
        int ejeX = _controller->axisX();
        int ejeY = _controller->axisY();

        if (ejeY <= -25) {
            _rover->avanzar(map(ejeY, -25, -508, 70, 255));
        } else if (ejeY >= 25) {
            _rover->retroceder(map(ejeY, 25, 512, 70, 255));
        } else {
            detener();
        }

        if (ejeX <= -25) {
            _rover->girarIzquierda(map(ejeX, -25, -508, 70, 255));
        } else if (ejeX >= 25) {
            _rover->girarDerecha(map(ejeX, 25, 512, 70, 255));
        }
    }
}

void Joystick::detener() {
    _rover->detenerse();
}

void Joystick::onConnectedController(ControllerPtr ctl) {
    _connected = true;
    _controller = ctl; 
    digitalWrite(_pinLed, HIGH);  
    Serial.println("Controlador conectado");
}

void Joystick::onDisconnectedController(ControllerPtr ctl) {
    if (_controller == ctl) {
        _connected = false;
        _controller = nullptr;  
        digitalWrite(_pinLed, LOW);  
        Serial.println("Controlador desconectado");
    }
}

bool Joystick::isConnected() {
    return _connected;  
}
