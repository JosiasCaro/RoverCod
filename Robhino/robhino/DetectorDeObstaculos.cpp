#include "DetectorDeObstaculos.h"

DetectorDeObstaculos::DetectorDeObstaculos(){

}

int DetectorDeObstaculos::detectarObstaculo(int distancia){
    if (distancia > 2 && distancia < 20) {
        //Objeto detectado a distancia
        return 1;
    } else {
        //No hay objetos en el rango definido
        return 0;
    }
}