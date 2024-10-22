#ifndef Joystick_h
#define Joystick_h

#include <Arduino.h>
#include "../Rover/Rover.h"
#include <Bluepad32.h> 

class Joystick {
public:
    Joystick(int pinX, int pinY, int pinLed, Rover* rover);
    void inicializar();
    void procesar();
    void detener();
    void onConnectedController(ControllerPtr ctl);  
    void onDisconnectedController(ControllerPtr ctl);
    bool isConnected();  

private:
    int _pinX;
    int _pinY;
    int _pinLed;
    Rover* _rover;
    bool _connected;
    ControllerPtr _controller;  
};

#endif
