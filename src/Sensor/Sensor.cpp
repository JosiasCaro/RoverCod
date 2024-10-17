#include "Sensor.h"

Sensor::Sensor(int pingPin) {
    _pingPin = pingPin;
};


void Sensor::medirDistancia() {
    long duration, cm;

    pinMode(_pingPin, OUTPUT);
    digitalWrite(_pingPin, LOW);
    delayMicroseconds(2);
    digitalWrite(_pingPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(_pingPin, LOW);

    pinMode(_pingPin, INPUT);
    duration = pulseIn(_pingPin, HIGH);

    cm = microsegundosACentimetros(duration);
    Serial.print(cm);
    Serial.print("cm");
    Serial.println();
};

long Sensor::microsegundosACentimetros(long microseconds) {
    return microseconds / 29 / 2;
}