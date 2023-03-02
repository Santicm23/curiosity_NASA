
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
        static void verificarDatos(string tipo, string um) {
            if (tipo == "avanzar") {
                if (um != "centimetros" && um != "metros" && um != "kilometros")
                    throw runtime_error("El tipo de movimiento 'avanzar' solo permite 'centimetros', 'metros' "
                        "y 'kilometros' como unidades de medida");
            } else if (tipo == "girar") {
                if (um != "grados" && um != "radianes")
                    throw runtime_error("El tipo de movimiento 'girar' solo permite 'grados', 'radianes' "
                        "como unidades de medida");
            } else
                throw runtime_error("El tipo de movimiento debe ser un valor entre 'girar' y 'avanzar'");
        }

        Movimiento(string tipo, float magn, string um) {
            
            tipo_movimiento = tipo;
            magnitud = magn;
            unidad_medida = um;
        }

        void ejecutar(RobotCuriosity &robot) {
            if (tipo_movimiento == "girar") {
                robot.turn(magnitud, unidad_medida);
            } else {
                robot.advance(magnitud, unidad_medida);
            }
        }

        string toString() {
            return tipo_movimiento + " " + to_string(magnitud) + " " + unidad_medida;
        }
};

#endif