#include <ArduinoFake.h>
#include <unity.h>
using namespace fakeit;
#include "../src/Rover/Rover.h"
#include "../src/Rover/Rover.cpp"
#include "../src/Rueda/Rueda.h"
#include "../src/Rueda/Rueda.cpp"  

Rover* rover ;

void setUp(void) {
    ArduinoFakeReset();  // Resetea el estado de las funciones de ArduinoFake
}

void tearDown(void) {
    delete rover;  // Liberamos el puntero al objeto Rover
    rover = nullptr;
}
void test_archivo_accesible(void) {
    TEST_ASSERT_TRUE(true); // Si compila, confirma que el archivo es accesible.
}

void test_inicializacion_rueda(void) {
    // Configura las simulaciones para pinMode
    When(Method(ArduinoFake(), pinMode).Using(12, OUTPUT)).AlwaysReturn();
    When(Method(ArduinoFake(), pinMode).Using(13, OUTPUT)).AlwaysReturn();
    When(Method(ArduinoFake(), pinMode).Using(14, OUTPUT)).AlwaysReturn();
    When(Method(ArduinoFake(), pinMode).Using(27, OUTPUT)).AlwaysReturn();

    // Crea un nuevo objeto Rover
    rover = new Rover(12, 13, 14, 27);

    // Verifica que los pines se hayan configurado correctamente
    Verify(Method(ArduinoFake(), pinMode).Using(12, OUTPUT)).Once();
    Verify(Method(ArduinoFake(), pinMode).Using(13, OUTPUT)).Once();
    Verify(Method(ArduinoFake(), pinMode).Using(14, OUTPUT)).Once();
    Verify(Method(ArduinoFake(), pinMode).Using(27, OUTPUT)).Once();

    // Limpia el objeto creado
    delete rover;
    rover = nullptr;
}
void test_avanzar(void) {
    // Configura las simulaciones para pinMode (asumiendo que se llaman en el constructor de Rover)
    When(Method(ArduinoFake(), pinMode).Using(12, OUTPUT)).AlwaysReturn();
    When(Method(ArduinoFake(), pinMode).Using(13, OUTPUT)).AlwaysReturn();
    When(Method(ArduinoFake(), pinMode).Using(14, OUTPUT)).AlwaysReturn();
    When(Method(ArduinoFake(), pinMode).Using(27, OUTPUT)).AlwaysReturn();

    // Crea un nuevo objeto Rover
    rover = new Rover(12, 13, 14, 27);

    // Configura las simulaciones para digitalWrite o cualquier función relevante que usarías al avanzar
    When(Method(ArduinoFake(), digitalWrite)).AlwaysReturn();
    When(Method(ArduinoFake(), analogWrite)).AlwaysReturn();

    // Llama al método avanzar con un valor de velocidad
    int velocidad = 200;
    rover->avanzar(velocidad);

    // Verifica que el método avanzar configure las ruedas correctamente usando analogWrite (simulando la velocidad)
    Verify(Method(ArduinoFake(), analogWrite).Using(12, velocidad)).Once(); // Supongamos que 12 controla una rueda
    Verify(Method(ArduinoFake(), analogWrite).Using(13, velocidad)).Once(); // Supongamos que 13 controla la otra rueda
    Verify(Method(ArduinoFake(), analogWrite).Using(14, velocidad)).Once(); // Supongamos que 12 controla una rueda
    Verify(Method(ArduinoFake(), analogWrite).Using(27, velocidad)).Once();
    // Limpia el objeto creado
    delete rover;
    rover = nullptr;
}
void test_retroceder(void) {
    When(Method(ArduinoFake(), pinMode).Using(12, OUTPUT)).AlwaysReturn();
    When(Method(ArduinoFake(), pinMode).Using(13, OUTPUT)).AlwaysReturn();
    When(Method(ArduinoFake(), pinMode).Using(14, OUTPUT)).AlwaysReturn();
    When(Method(ArduinoFake(), pinMode).Using(27, OUTPUT)).AlwaysReturn();

    // Crea un nuevo objeto Rover
    rover = new Rover(12, 13, 14, 27);

    // Configura las simulaciones para digitalWrite o cualquier función relevante
    When(Method(ArduinoFake(), digitalWrite)).AlwaysReturn();
    When(Method(ArduinoFake(), analogWrite)).AlwaysReturn();

    // Llama al método retroceder con un valor de velocidad
    int velocidad = 200;
    rover->retroceder(velocidad);

    // Verifica que analogWrite se haya llamado con los valores correctos
    Verify(Method(ArduinoFake(), analogWrite).Using(12, _)).Once();
    Verify(Method(ArduinoFake(), analogWrite).Using(13, _)).Once();
    Verify(Method(ArduinoFake(), analogWrite).Using(14, _)).Once();
    Verify(Method(ArduinoFake(), analogWrite).Using(27, _)).Once();

    delete rover;
    rover = nullptr;
}
void test_girarDerecha(void) {
    // Configura las simulaciones para pinMode (asumiendo que se llaman en el constructor de Rover)
    When(Method(ArduinoFake(), pinMode).Using(12, OUTPUT)).AlwaysReturn();
    When(Method(ArduinoFake(), pinMode).Using(13, OUTPUT)).AlwaysReturn();
    When(Method(ArduinoFake(), pinMode).Using(14, OUTPUT)).AlwaysReturn();
    When(Method(ArduinoFake(), pinMode).Using(27, OUTPUT)).AlwaysReturn();

    // Crea un nuevo objeto Rover
    rover = new Rover(12, 13, 14, 27);

    // Configura las simulaciones para digitalWrite o cualquier función relevante que usarías al avanzar
    When(Method(ArduinoFake(), digitalWrite)).AlwaysReturn();
    When(Method(ArduinoFake(), analogWrite)).AlwaysReturn();

    // Llama al método avanzar con un valor de velocidad
    int velocidad = 200;
    rover->girarDerecha(velocidad);

    // Verifica que el método avanzar configure las ruedas correctamente usando analogWrite (simulando la velocidad)
    Verify(Method(ArduinoFake(), analogWrite).Using(12, LOW)).Once(); // Supongamos que 12 controla una rueda
    Verify(Method(ArduinoFake(), analogWrite).Using(13, LOW)).Once(); // Supongamos que 13 controla la otra rueda
    Verify(Method(ArduinoFake(), analogWrite).Using(14, _)).Once(); // Supongamos que 12 controla una rueda
    Verify(Method(ArduinoFake(), analogWrite).Using(27, _)).Once(); 
    // Limpia el objeto creado
    delete rover;
    rover = nullptr;

}
void test_detenerse(void) {
    // Configura las simulaciones para pinMode (asumiendo que se llaman en el constructor de Rover)
    When(Method(ArduinoFake(), pinMode).Using(12, OUTPUT)).AlwaysReturn();
    When(Method(ArduinoFake(), pinMode).Using(13, OUTPUT)).AlwaysReturn();
    When(Method(ArduinoFake(), pinMode).Using(14, OUTPUT)).AlwaysReturn();
    When(Method(ArduinoFake(), pinMode).Using(27, OUTPUT)).AlwaysReturn();

    // Crea un nuevo objeto Rover
    rover = new Rover(12, 13, 14, 27);

    // Configura las simulaciones para digitalWrite o cualquier función relevante que usarías al avanzar
    When(Method(ArduinoFake(), digitalWrite)).AlwaysReturn();
    When(Method(ArduinoFake(), analogWrite)).AlwaysReturn();

    // Llama al método avanzar con un valor de velocidad
    int velocidad = 200;
    rover->detenerse();

    // Verifica que el método avanzar configure las ruedas correctamente usando analogWrite (simulando la velocidad)
    Verify(Method(ArduinoFake(), analogWrite).Using(12, LOW)).Once(); // Supongamos que 12 controla una rueda
    Verify(Method(ArduinoFake(), analogWrite).Using(13, LOW)).Once(); // Supongamos que 13 controla la otra rueda
    Verify(Method(ArduinoFake(), analogWrite).Using(14, LOW)).Once(); // Supongamos que 12 controla una rueda
    Verify(Method(ArduinoFake(), analogWrite).Using(27, LOW)).Once(); 
    // Limpia el objeto creado
    delete rover;
    rover = nullptr;
}
void test_girarIzquierda(void) {
    // Configura las simulaciones para pinMode (asumiendo que se llaman en el constructor de Rover)
    When(Method(ArduinoFake(), pinMode).Using(12, OUTPUT)).AlwaysReturn();
    When(Method(ArduinoFake(), pinMode).Using(13, OUTPUT)).AlwaysReturn();
    When(Method(ArduinoFake(), pinMode).Using(14, OUTPUT)).AlwaysReturn();
    When(Method(ArduinoFake(), pinMode).Using(27, OUTPUT)).AlwaysReturn();

    // Crea un nuevo objeto Rover
    rover = new Rover(12, 13, 14, 27);

    // Configura las simulaciones para digitalWrite o cualquier función relevante que usarías al avanzar
    When(Method(ArduinoFake(), digitalWrite)).AlwaysReturn();
    When(Method(ArduinoFake(), analogWrite)).AlwaysReturn();

    // Llama al método avanzar con un valor de velocidad
    int velocidad = 200;
    rover->girarIzquierda(velocidad);

    // Verifica que el método avanzar configure las ruedas correctamente usando analogWrite (simulando la velocidad)
    Verify(Method(ArduinoFake(), analogWrite).Using(12, _)).Once(); // Supongamos que 12 controla una rueda
    Verify(Method(ArduinoFake(), analogWrite).Using(13, _)).Once(); // Supongamos que 13 controla la otra rueda
    Verify(Method(ArduinoFake(), analogWrite).Using(14, LOW)).Once(); // Supongamos que 12 controla una rueda
    Verify(Method(ArduinoFake(), analogWrite).Using(27, LOW)).Once(); 
    // Limpia el objeto creado
    delete rover;
    rover = nullptr;
}
void test_digitalWrite(void) {
    // Simulamos que digitalWrite se llama para encender un LED
    When(Method(ArduinoFake(), digitalWrite).Using(13, HIGH)).AlwaysReturn(); // Simulamos digitalWrite(13, HIGH)

    // Ejecutamos la acción (simulamos que queremos encender un LED en el pin 13)
    digitalWrite(13, HIGH);

    // Verificamos que digitalWrite fue llamado correctamente
    Verify(Method(ArduinoFake(), digitalWrite).Using(13, HIGH)).Once();  // Esperamos que digitalWrite(13, HIGH) haya sido llamado una vez
}

void test_analogWrite(void) {
    // Simulamos que analogWrite se llama para establecer un valor PWM
    When(Method(ArduinoFake(), analogWrite).Using(9, 128)).AlwaysReturn(); // Simulamos analogWrite(9, 128)

    // Ejecutamos la acción (simulamos que queremos establecer un valor PWM en el pin 9)
    analogWrite(9, 128);

    // Verificamos que analogWrite fue llamado correctamente
    Verify(Method(ArduinoFake(), analogWrite).Using(9, 128)).Once();  // Esperamos que analogWrite(9, 128) haya sido llamado una vez
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_digitalWrite);  // Ejecuta la prueba de digitalWrite
    RUN_TEST(test_analogWrite);   // Ejecuta la prueba de analogWrite
    RUN_TEST(test_archivo_accesible); 
    RUN_TEST(test_inicializacion_rueda);
    RUN_TEST(test_avanzar);
    RUN_TEST(test_retroceder);
    RUN_TEST(test_detenerse);
    RUN_TEST(test_girarIzquierda);
    RUN_TEST(test_girarDerecha);
    UNITY_END();

    return 0;
}

