
#ifndef ROBOTCURIOSITY
#define ROBOTCURIOSITY


#include <iostream>
#include <math.h>
#include <string>

using namespace std;

#define PI 3.14159265358979323846


class RobotCuriosity {
    private:
        float coordX; // on meters
        float coordY; // on meters
        float angle = 0; // on radians
    
    public:
        RobotCuriosity(float x, float y) {
            coordX = x;
            coordY = y;
        }

        float getX() { return coordX; }

        float getY() { return coordY; }

        void advance(float dist, string unit = "metros") {
            if (unit == "centimetros") {
                dist *= 0.01;
            } else if (unit == "kilometros") {
                dist *= 1000;
            } else if (unit != "metros") {
                throw runtime_error("Unidad invalida o no soportada");
            }
            
            coordX += dist*cos(angle);
            coordY += dist*sin(angle);
        }

        void turn(float a, string unit = "radianes"){
            if (unit == "grados") {
                a *= PI/180;
            } else if (unit != "radianes") {
                throw runtime_error("Unidad invalida");
            }
            
            angle += a;
        }
};

#endif