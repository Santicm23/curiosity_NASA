
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
        Movimiento(string tipo, float magn, string um);

        //* verificar que los datos del vector correspondan a la clase
        static void verificarDatos(vector<string> args);

        //* ejecutar el movimiento sobre el robot dado
        void ejecutar(RobotCuriosity &robot);

        //* conviertir la información del desplazamiento a un string
        string toString(char delim);
};

#include "movimiento.cxx"

#endif