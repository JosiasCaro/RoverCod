#ifndef Rueda_h
#define Rueda_h

#include <Arduino.h>

class Rueda 
{

    public:
        Rueda(int pin_ruedaA, int pin_ruedaB);
        void inicializar();
        void girar(int velocidadA, int velocidadB);
        void detenerse();
    private:
        int _pin_asignadoA;
        int _pin_asignadoB;
};

#endif