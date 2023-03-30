
#ifndef MOVIMIENTO
#define MOVIMIENTO


#include <iostream>
#include <string>

#include "desplazamiento.h"
#include "robotCuriosity.h"

using namespace std;


class Movimiento : public Desplazamiento {
    private:
        string tipo_movimiento;
        float magnitud;
        string unidad_medida;
    
    public:
        static void verificarDatos(vector<string> args);

        Movimiento(string tipo, float magn, string um);

        void ejecutar(RobotCuriosity &robot);

        string toString(char delim);
};

#include "movimiento.cxx"

#endif