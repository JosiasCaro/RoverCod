#include "Sensor.h"

#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters).

// Constructor
Sensor::Sensor(int triggerPin, int echoPin) 
    : _triggerPin(triggerPin), _echoPin(echoPin), sonar(triggerPin, echoPin, MAX_DISTANCE) {
    // Se inicializa la instancia 'sonar' con los pines y la distancia máxima
}

int Sensor::medirDistancia() {
    delay(50);                     // Wait 50ms between pings.
    _distancia = sonar.ping_cm();
    Serial.print("Distacia: ");
    Serial.print(_distancia); // Send ping, get distance in cm and print result
    Serial.println("cm");
    return _distancia;
}
