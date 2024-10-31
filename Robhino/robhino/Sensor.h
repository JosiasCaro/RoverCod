#ifndef Sensor_h
#define Sensor_h

#include <Arduino.h>
#include <NewPing.h>

class Sensor {
    
    public: 
        Sensor(int triggerPin, int echoPin);
        int medirDistancia();

    private:
        int _triggerPin;
        int _echoPin;
        NewPing sonar; // Cambiado para declarar una instancia sin inicializar
        int _distancia;
};

#endif
