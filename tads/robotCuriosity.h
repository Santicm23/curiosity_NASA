
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
        RobotCuriosity();

        RobotCuriosity(float x, float y, float a);

        float getX();

        float getY();

        void setCoords(float x, float y);

        void avanzar(float dist, string unit);

        void girar(float a, string unit);
};

#include "robotCuriosity.cxx"

#endif