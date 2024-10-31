#include "Joystick.h"

ControllerPtr myControllers[BP32_MAX_GAMEPADS];

Joystick::Joystick(int ledPin, Rover& rover) : _rover(rover){
    _rover = rover;
    _ledPin = ledPin;
}

void Joystick::setup(){
  pinMode(_ledPin, OUTPUT);
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
  
  digitalWrite(_ledPin, HIGH);
  delay(1000);
  digitalWrite(_ledPin, LOW);
}

void Joystick::loop(){
  // This call fetches all the controllers' data.
  // Call this function in your main loop.
  bool dataUpdated = BP32.update();
  if (dataUpdated){
    processControllers();
  }
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

  if (ctl->buttons() == 0x0001) {
    digitalWrite(_ledPin, HIGH);
  }
  if (ctl->buttons() != 0x0001) {
    digitalWrite(_ledPin, LOW);
  }

  //== R2 - UP ==//
  if (ctl->buttons() == 0x0080) {
    // map joystick values to motor speed
    int motorSpeed = map(r2Intensity, 100, 1023, 150, 255);
    // move motors/robot forward
    _rover.avanzar(motorSpeed);
    Serial.println("Rover adelante | Velocidad: " + String(motorSpeed));
  }

  //== L2 - DOWN ==//
  if (ctl->buttons() == 0x0040) {
    // map joystick values to motor speed
    int motorSpeed = map(l2Intensity, 100, 1023, 150, 255);
    // move motors/robot in reverse
    _rover.retroceder(motorSpeed);
    Serial.println("Rover atras | Velocidad: " + String(motorSpeed));
  }

  //== LEFT JOYSTICK - LEFT ==//
  if (ctl->axisX() <= -25) {
    // map joystick values to motor speed
    int motorSpeed = map(ctl->axisX(), -25, -508, 70, 255);
    // turn robot left - move right motor forward, keep left motor still
    _rover.girarIzquierda(motorSpeed);
    Serial.println("Rover izquierda | Velocidad: " + String(motorSpeed));
  }

  //== LEFT JOYSTICK - RIGHT ==//
  if (ctl->axisX() >= 25) {
    // map joystick values to motor speed
    int motorSpeed = map(ctl->axisX(), 25, 512, 70, 255);
    // turn robot right - move left motor forward, keep right motor still
    _rover.girarDerecha(motorSpeed);
    Serial.println("Rover derecha | Velocidad: " + String(motorSpeed));
  }

  //== LEFT JOYSTICK DEADZONE ==//
  if (ctl->axisX() > -25 && ctl->axisX() < 25 && ctl->buttons() !=  0x0080 && ctl->buttons() != 0x0040) {
    // keep motors off
    _rover.detenerse();
    Serial.println("Rover detenido | Velocidad: 0");
  }

  //dumpGamepad(ctl);
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