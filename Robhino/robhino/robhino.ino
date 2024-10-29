#include <Arduino.h>
#include "Rover.h"
#include "Sensor.h"
#include "Joystick.h"

int esperaSensor = 100;
int led = 4;
int choque = 0;

Sensor sensor1(15);

Rover rover(13, 12, 14, 27, 2);

void InicializarSerial(){
  Serial.begin(115200);
}

TaskHandle_t Tarea1;

// This callback gets called any time a new gamepad is connected.
// Up to 4 gamepads can be connected at the same time.

void loop_tarea1(void * pvParameters) {
  Serial.print("Tarea1 se corre en el nucleo: ");
  Serial.println(xPortGetCoreID());
  while(1){
    int distancia = sensor1.medirDistancia(led);
    if(distancia > 0 && distancia < 20){
      choque = distancia;
    }else{
      choque = 0;
    }
    delay(600);
  }
}

// Arduino setup function. Runs in CPU 1
void setup() {
  InicializarSerial();
  pinMode(led, OUTPUT);

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
  // The main loop must have some kind of "yield to lower priority task" event.
  // Otherwise, the watchdog will get triggered.
  // If your main loop doesn't have one, just add a simple vTaskDelay(1).
  // Detailed info here:
  // https://stackoverflow.com/questions/66278271/task-watchdog-got-triggered-the-tasks-did-not-reset-the-watchdog-in-time
  
  rover.actualizar(choque);
  vTaskDelay(1);
  delay(100);
}