#ifndef Rover_h
#define Rover_h

#include <Arduino.h>
#include "Rueda.h"
#include "Joystick.h"

class Rover {
    
    public: 
        Rover(int pinIzquierdaA, int pinIzquierdaB, int pinDerechaA, int pinDerechaB, int pinJoystick);
        void avanzar(int velocidad);
        void retroceder(int velocidad);
        void detenerse();
        void girarIzquierda(int velocidad);
        void girarDerecha(int velocidad);
        void actualizar(int sensor);
    private:
        Rueda _ruedaIzquierda;
        Rueda _ruedaDerecha;
        Joystick _joystick;
};

#endif
