#ifndef Rover_h
#define Rover_h

#include <Arduino.h>
#include "../Rueda/Rueda.h"

class Rover {
    
    public: 
        Rover(int pinIzquierdaA, int pinIzquierdaB, int pinDerechaA, int pinDerechaB);
        void avanzar(int velocidad);
        void retroceder(int velocidad);
        void detenerse();
        void girarIzquierda(int velocidad);
        void girarDerecha(int velocidad);
    private:
        Rueda _ruedaIzquierda;
        Rueda _ruedaDerecha;
};

#endif
