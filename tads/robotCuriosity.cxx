
#include <string>

#include "robotCuriosity.h"


RobotCuriosity::RobotCuriosity() {
    this->coordX = 0;
    this->coordY = 0;
    this->angulo = 0;
}

RobotCuriosity::RobotCuriosity(float x, float y, float a = 0) {
    this->coordX = x;
    this->coordY = y;
    this->angulo = a;
}

float RobotCuriosity::getX() {
    return this->coordX;
}

float RobotCuriosity::getY() {
    return this->coordY;
}

void RobotCuriosity::setData(float x, float y, float a) {
    this->coordX = x;
    this->coordY = y;
    this->angulo = a;
}

void RobotCuriosity::avanzar(float dist, string unit = "metros") {
    if (unit == "centimetros") {
        dist *= 0.01;
    } else if (unit == "kilometros") {
        dist *= 1000;
    } else if (unit != "metros") {
        throw runtime_error("Unidad invalida o no soportada");
    }
    this->coordX += dist*cos(this->angulo);
    this->coordY += dist*sin(this->angulo);
}

void RobotCuriosity::girar(float a, string unit = "radianes") {
    if (unit == "grados") {
        a *= PI/180;
    } else if (unit != "radianes") {
        throw runtime_error("Unidad de medida invalida");
    }
    this->angulo += a;
}