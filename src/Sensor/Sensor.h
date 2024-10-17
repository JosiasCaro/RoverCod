#ifndef Sensor_h
#define Sensor_h

#include <Arduino.h>
#include "../Sensor/Sensor.h"

class Sensor {
    
    public: 
        Sensor(int pingPin);
        void medirDistancia();

    private:
        int _pingPin;
        long microsegundosACentimetros(long microseconds);
};

#endif
