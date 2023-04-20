
#ifndef ROBOTCURIOSITY
#define ROBOTCURIOSITY


#include <iostream>
#include <math.h>
#include <string>

using namespace std;

#define PI 3.14159265358979323846


class RobotCuriosity {
    private:
        float coordX; //* en metros
        float coordY; //* en metros
        float angulo; //* en radianes
    
    public:
        RobotCuriosity();

        RobotCuriosity(float x, float y, float a);

        float getX();

        float getY();

        void setData(float x, float y, float a);

        //* desplazar el robot en una distancia dada y en la direccion actual
        void avanzar(float dist, string unit);

        //* girar el robot según un angulo ingresado
        void girar(float a, string unit);
};

#include "robotCuriosity.cxx"

#endif