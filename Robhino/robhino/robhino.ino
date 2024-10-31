#include <Arduino.h>
#include "Rover.h"
#include "Sensor.h"
#include "Joystick.h"

int esperaSensor = 100;
int pinLed = 2;
int led = 4;

Rover rover(12, 13, 14, 27);

Joystick joystick(pinLed, rover);

Sensor sensor1(26);

void InicializarSerial(){
  Serial.begin(115200);
}

TaskHandle_t Tarea1;

void loop_tarea1(void * pvParameters) {
  Serial.print("Tarea1 se corre en el nucleo: ");
  Serial.println(xPortGetCoreID());
  while(1){
    sensor1.medirDistancia(led);
    delay(600);
  }
}

// Arduino setup function. Runs in CPU 1
void setup() {
  InicializarSerial();
  pinMode(led, OUTPUT);

  joystick.setup();

  xTaskCreatePinnedToCore(
      loop_tarea1, /* Funcion de la tarea1 */
      "Tarea1", /* Nombre de la tarea */
      10000,  /* Tamaño de la pila */
      NULL,  /* Parametros de entrada */
      0,  /* Prioridad de la tarea */
      &Tarea1,  /* objeto TaskHandle_t. */
      0); /* Nucleo donde se correra */

}

// Arduino loop function. Runs in CPU 1.
void loop() {
  joystick.loop();

  // The main loop must have some kind of "yield to lower priority task" event.
  // Otherwise, the watchdog will get triggered.
  // If your main loop doesn't have one, just add a simple vTaskDelay(1).
  // Detailed info here:
  // https://stackoverflow.com/questions/66278271/task-watchdog-got-triggered-the-tasks-did-not-reset-the-watchdog-in-time

  //     vTaskDelay(1);
  delay(100);
}