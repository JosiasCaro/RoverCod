#ifndef DetectorDeObstaculos_h
#define DetectorDeObstaculos_h

#include <Arduino.h>

class DetectorDeObstaculos
{
    public:
        DetectorDeObstaculos();
        int detectarObstaculo(int distancia);
};

#endif