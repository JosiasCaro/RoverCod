#ifndef Joystick_h
#define Joystick_h

#include <Arduino.h>
#include <Bluepad32.h>
#include "Rover.h"

class Joystick
{
    public:
        Joystick(int ledPin, Rover& rover);
        void setup();
        void loop();

    private:
        static void onConnectedController(ControllerPtr ctl);
        static void onDisconnectedController(ControllerPtr ctl);
        void processControllers();
        void processGamepad(ControllerPtr ctl);
        void dumpGamepad(ControllerPtr ctl);

        int _ledPin;
        Rover& _rover;
        int _direccion;
};

#endif