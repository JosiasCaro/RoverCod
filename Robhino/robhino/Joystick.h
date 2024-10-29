#ifndef Joystick_h
#define Joystick_h

#include <Arduino.h>
#include <Bluepad32.h>
#include <array>

class Joystick
{
    public:
        Joystick(int ledPin);
        std::array<int, 4> actualizacion(); // Cambia el tipo de retorno

    private:
        void inicializar();
        static void onConnectedController(ControllerPtr ctl);
        static void onDisconnectedController(ControllerPtr ctl);
        void processControllers();
        void processGamepad(ControllerPtr ctl);
        void dumpGamepad(ControllerPtr ctl);

        int _ledPin;
        std::array<int, 4> _motorSpeeds; // Cambia el tipo a std::array
};

#endif