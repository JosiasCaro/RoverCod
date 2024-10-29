#include "Joystick.h"

ControllerPtr myControllers[BP32_MAX_GAMEPADS];

Joystick::Joystick(int ledPin) { 
    pinMode(ledPin, OUTPUT);
    _ledPin = ledPin;
    _motorSpeeds = {0, 0, 0, 0};
    inicializar();
};

void Joystick::inicializar() {
    
    Serial.begin(115200);
    Serial.printf("Firmware: %s\n", BP32.firmwareVersion());
    const uint8_t* addr = BP32.localBdAddress();
    Serial.printf("BD Addr: %2X:%2X:%2X:%2X:%2X:%2X\n", addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);

    // Setup the Bluepad32 callbacks
    BP32.setup(&onConnectedController, &onDisconnectedController);

    // "forgetBluetoothKeys()" should be called when the user performs
    // a "device factory reset", or similar.
    // Calling "forgetBluetoothKeys" in setup() just as an example.
    // Forgetting Bluetooth keys prevents "paired" gamepads to reconnect.
    // But it might also fix some connection / re-connection issues.
    BP32.forgetBluetoothKeys();

    // Enables mouse / touchpad support for gamepads that support them.
    // When enabled, controllers like DualSense and DualShock4 generate two connected devices:
    // - First one: the gamepad
    // - Second one, which is a "virtual device", is a mouse.
    // By default, it is disabled.
    BP32.enableVirtualDevice(false);
}

std::array<int, 4> Joystick::actualizacion(){
    // This call fetches all the controllers' data.
    // Call this function in your main loop.
    bool dataUpdated = BP32.update();
    if (dataUpdated){
        processControllers();
    }
    // The main loop must have some kind of "yield to lower priority task" event.
    // Otherwise, the watchdog will get triggered.
    // If your main loop doesn't have one, just add a simple `vTaskDelay(1)`.
    // Detailed info here:
    // https://stackoverflow.com/questions/66278271/task-watchdog-got-triggered-the-tasks-did-not-reset-the-watchdog-in-time

    return _motorSpeeds;

}

// This callback gets called any time a new gamepad is connected.
// Up to 4 gamepads can be connected at the same time.

void Joystick::onConnectedController(ControllerPtr ctl) {
  bool foundEmptySlot = false;
  for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
    if (myControllers[i] == nullptr) {
      Serial.printf("CALLBACK: Controller is connected, index=%d\n", i);
      // Additionally, you can get certain gamepad properties like:
      // Model, VID, PID, BTAddr, flags, etc.
      ControllerProperties properties = ctl->getProperties();
      Serial.printf("Controller model: %s, VID=0x%04x, PID=0x%04x\n", ctl->getModelName().c_str(), properties.vendor_id, properties.product_id);
      myControllers[i] = ctl;
      foundEmptySlot = true;
      break;
      }
  }
  if (!foundEmptySlot) {
    Serial.println("CALLBACK: Controller connected, but could not found empty slot");
  }
}

void Joystick::onDisconnectedController(ControllerPtr ctl) {
    bool foundController = false;

    for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
        if (myControllers[i] == ctl) {
            Serial.printf("CALLBACK: Controller disconnected from index=%d\n", i);
            myControllers[i] = nullptr;
            foundController = true;
            break;
        }
    }

    if (!foundController) {
      Serial.println("CALLBACK: Controller disconnected, but not found in myControllers");
    }
}

// == SEE CONTROLLER VALUES IN SERIAL MONITOR == //

void Joystick::dumpGamepad(ControllerPtr ctl) {
    Serial.printf(
      "idx=%d, dpad: 0x%02x, buttons: 0x%04x, axis L: %4d, %4d, axis R: %4d, %4d, brake: %4d, throttle: %4d, "
      "misc: 0x%02x, gyro x:%6d y:%6d z:%6d, accel x:%6d y:%6d z:%6d\n",
      ctl->index(),        // Controller Index
      ctl->dpad(),         // D-pad
      ctl->buttons(),      // bitmask of pressed buttons
      ctl->axisX(),        // (-511 - 512) left X Axis
      ctl->axisY(),        // (-511 - 512) left Y axis
      ctl->brake(),        // (0 - 1023): brake button
      ctl->throttle(),     // (0 - 1023): throttle (AKA gas) button
      ctl->miscButtons(),  // bitmask of pressed "misc" buttons
      ctl->gyroX(),        // Gyro X
      ctl->gyroY(),        // Gyro Y
      ctl->gyroZ(),        // Gyro Z
      ctl->accelX(),       // Accelerometer X
      ctl->accelY(),       // Accelerometer Y
      ctl->accelZ()        // Accelerometer Z
    );
}

// == GAME CONTROLLER ACTIONS SECTION == //

void Joystick::processGamepad(ControllerPtr ctl) {
    int l2Intensity = ctl->brake();    // L2
    int r2Intensity = ctl->throttle(); // R2
    _motorSpeeds = {0,0,0,0};

    if (ctl->buttons() & 0x0001) {
      digitalWrite(_ledPin, HIGH);
    }

    if (ctl->buttons() != 0x0001) {
      digitalWrite(_ledPin, LOW);
    }

    // == FORWARD (R2) ==
    if (ctl->buttons() & 0x2000) { // R2
        _motorSpeeds[0] = map(r2Intensity, 100, 1023, 150, 255); // map R2 intensity
        //rover.avanzar(motorSpeed);
    }

    // == REVERSE (L2) ==
    if (ctl->buttons() & 0x1000) { // L2
        _motorSpeeds[1] = map(l2Intensity, 100, 1023, 150, 255); // map L2 intensity
        //rover.retroceder(motorSpeed);
    }

    //== LEFT JOYSTICK - LEFT ==//
    if (ctl->axisX() <= -25) {
        // map joystick values to motor speed
        _motorSpeeds[2] = map(ctl->axisX(), -25, -508, 150, 255);
        // turn robot left - move right motor forward, keep left motor still
        //rover.girarIzquierda(motorSpeed);

    }

    //== LEFT JOYSTICK - RIGHT ==//
    if (ctl->axisX() >= 25) {
        // map joystick values to motor speed
        _motorSpeeds[3] = map(ctl->axisX(), 25, 512, 150, 255);
        // turn robot right - move left motor forward, keep right motor still
        //rover.girarDerecha(motorSpeed);
    }

    //== LEFT JOYSTICK DEADZONE ==//
    //if (!(ctl->axisX() < -25 || ctl->axisX() > 25 || ctl->buttons() & 0x1000 || ctl->buttons() & 0x2000)) {
        // keep motors off
        //rover.detenerse();
    //}

    dumpGamepad(ctl);
}

void Joystick::processControllers() {
    for (auto myController : myControllers) {
        if (myController && myController->isConnected() && myController->hasData()) {
            if (myController->isGamepad()) {
                processGamepad(myController);
            }
            else {
                Serial.println("Unsupported controller");
            }
        }
    }
}