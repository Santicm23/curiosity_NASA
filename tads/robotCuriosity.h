
#ifndef ROBOTCURIOSITY
#define ROBOTCURIOSITY


#include <iostream>
#include <math.h>
#include <string>

using namespace std;

#define PI 3.14159265358979323846


class RobotCuriosity {
    private:
        float coordX; // en metros
        float coordY; // en metros
        float angulo; // en radianes
    
    public:
        RobotCuriosity(float x, float y, float a = 0) {
            coordX = x;
            coordY = y;
            angulo = a;
        }

        float getX() { return coordX; }

        float getY() { return coordY; }

        void avanzar(float dist, string unit = "metros") {
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

        void girar(float a, string unit = "radianes"){
            if (unit == "grados") {
                a *= PI/180;
            } else if (unit != "radianes") {
                throw runtime_error("Unidad invalida");
            }
            angulo += a;
        }
};

#endif