
#include <string>

#include "robotCuriosity.h"


RobotCuriosity::RobotCuriosity() {
    coordX = 0;
    coordY = 0;
    angulo = 0;
}

RobotCuriosity::RobotCuriosity(float x, float y, float a = 0) {
    coordX = x;
    coordY = y;
    angulo = a;
}

float RobotCuriosity::getX() {
    return coordX;
}

float RobotCuriosity::getY() {
    return coordY;
}

void RobotCuriosity::setCoords(float x, float y) {
    coordX = x;
    coordY = y;
}

void RobotCuriosity::avanzar(float dist, string unit = "metros") {
    if (unit == "centimetros") {
        dist *= 0.01;
    } else if (unit == "kilometros") {
        dist *= 1000;
    } else if (unit != "metros") {
        throw runtime_error("Unidad invalida o no soportada");
    }
    coordX += dist*cos(angulo);
    coordY += dist*sin(angulo);
}

void RobotCuriosity::girar(float a, string unit = "radianes") {
    if (unit == "grados") {
        a *= PI/180;
    } else if (unit != "radianes") {
        throw runtime_error("Unidad de medida invalida");
    }
    angulo += a;
}