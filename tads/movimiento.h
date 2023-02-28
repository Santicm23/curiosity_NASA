
#ifndef MOVIMIENTO
#define MOVIMIENTO


#include <string>

#include "desplazamiento.h"

using namespace std;


class Movimiento : public Desplazamiento {
    private:
        string tipo_movimiento;
        float magnitud;
        string unidad_medida;
    
    public:
        Movimiento(string tipo, float magn, string um) {
            tipo_movimiento = tipo;
            magnitud = magn;
            unidad_medida = um;
        }

        // string toString() {
        //     return tipo_movimiento + " " + to_string(magnitud) + " " + unidad_medida;
        // }
};

#endif