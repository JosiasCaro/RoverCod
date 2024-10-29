#include "Sensor.h"

Sensor::Sensor(int pingPin) {
    _pingPin = pingPin;
};


long Sensor::medirDistancia(int pin) {
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
    if(cm < 10) {
        digitalWrite(pin, HIGH);
    } else {
        digitalWrite(pin, LOW);
    }

    Serial.print(cm);
    Serial.print("cm");
    Serial.println();
    return cm;
};

long Sensor::microsegundosACentimetros(long microseconds) {
    return microseconds / 29 / 2;
}