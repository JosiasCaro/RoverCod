#ifndef Sensor_h
#define Sensor_h

#include <Arduino.h>
#include "Sensor.h"

class Sensor {
    
    public: 
        Sensor(int pingPin);
        long medirDistancia(int pin);

    private:
        int _pingPin;
        long microsegundosACentimetros(long microseconds);
};

#endif
