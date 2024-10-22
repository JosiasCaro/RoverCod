#include "Joystick.h"

Joystick::Joystick(Rover* rover) : _rover(rover) {}

// == GAME CONTROLLER ACTIONS SECTION ==
void Joystick::processGamepad(ControllerPtr ctl) {
    // Manejamos el LED
    digitalWrite(pinLed, (ctl->buttons() == 0x0001) ? HIGH : LOW);

    int motorSpeed = map(ctl->axisY(), -512, 512, -255, 255);
    int giro = map(ctl->axisX(), -512, 512, -255, 255);

    if (abs(motorSpeed) < 50 && abs(giro) < 50) {
        _rover->detenerse();
    } else {
        if (motorSpeed > 0) {
            _rover->avanzar(motorSpeed);
        } else {
            _rover->retroceder(-motorSpeed);
        }

        if (giro < 0) {
            _rover->girarDerecha(-giro);
        } else if (giro > 0) {
            _rover->girarIzquierda(giro);
        }
    }
}
