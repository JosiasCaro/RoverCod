#ifndef Rover_h
#define Rover_h

#include <Arduino.h>
#include "Rueda.h"
#include "Cortador.h"

class Rover {
    
    public: 
        Rover(int pinIzquierdaA, int pinIzquierdaB, int pinDerechaA, int pinDerechaB, int pinPasto);
        void avanzar(int velocidad);
        void retroceder(int velocidad);
        void detenerse();
        void girarIzquierda(int velocidad);
        void girarDerecha(int velocidad);
        bool cortar();
    private:
        Rueda _ruedaIzquierda;
        Rueda _ruedaDerecha;
        Cortador _cortadora;
};

#endif
