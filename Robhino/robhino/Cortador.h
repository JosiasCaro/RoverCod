#ifndef Cortador_h
#define Cortador_h

#include <Arduino.h>

class Cortador
{
    public:
        Cortador(int pinPasto);
        bool cortar();
    private:
        int _pinPasto;
        bool _pasto;
};

#endif