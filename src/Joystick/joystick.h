#ifndef Joystick_h
#define Joystick_h

#include <Arduino.h>
#include "../Rover/Rover.h"

class Joystick {
public:
    Joystick(int pinX, int pinY, int pinLed, Rover* rover);
    void inicializar();
    void procesar();
    void detener();
    void onConnectedController();
    void onDisconnectedController();
    void dumpGamepad();
    void ProcessControllers();
private:
    int _pinX;
    int _pinY;
    int _pinLed;
    Rover* _rover;
    bool _connected; 
};

#endif
