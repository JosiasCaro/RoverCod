#include "Joystick.h"

Joystick::Joystick(Rover* rover) : _rover(rover) {}

// == GAME CONTROLLER ACTIONS SECTION ==
void Joystick::processGamepad(ControllerPtr ctl) {
    // Manejamos el LED
    if (ctl->buttons() == 0x0001) {
        digitalWrite(pinLed, HIGH);
    } else {
        digitalWrite(pinLed, LOW);
    }

    //== LEFT JOYSTICK - UP ==//
    if (ctl->axisY() <= -25) {
        int motorSpeed = map(ctl->axisY(), -25, -508, 70, 255);
        _rover->avanzar(motorSpeed);
    }

    //== LEFT JOYSTICK - DOWN ==//
    if (ctl->axisY() >= 25) {
        int motorSpeed = map(ctl->axisY(), 25, 512, 70, 255);
        _rover->retroceder(motorSpeed);
    }

    //== LEFT JOYSTICK - LEFT ==//
    if (ctl->axisX() <= -25) {
        int motorSpeed = map(ctl->axisX(), -25, -508, 70, 255);
        _rover->girarIzquierda(motorSpeed);
    }

    //== LEFT JOYSTICK - RIGHT ==//
    if (ctl->axisX() >= 25) {
        int motorSpeed = map(ctl->axisX(), 25, 512, 70, 255);
        _rover->girarDerecha(motorSpeed);
    }

    //== LEFT JOYSTICK DEADZONE ==//
    if (ctl->axisY() > -25 && ctl->axisY() < 25 && ctl->axisX() > -25 && ctl->axisX() < 25) {
        _rover->detenerse();
    }
}
