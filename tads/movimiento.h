
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
        static void verificarDatos(vector<string> args) {
            float magn;
            if (args.size() != 3) throw runtime_error(
                "Los comandos de movimiento requieren tipo_movimiento, magnitud y unidad_medida como argumentos");
            try {
                magn = stof(args[1]);
            } catch (const invalid_argument& e) {
                throw runtime_error("La magnitud del comando debe ser un numero flotante");
            } 
            if (args[0] == "avanzar") {
                if (magn < 0) throw runtime_error(
                    "La magnitud del movimiento debe ser positiva");
                else if (args[2] != "centimetros" && args[2] != "metros" && args[2] != "kilometros")
                    throw runtime_error("El tipo de movimiento 'avanzar' solo permite"
                        "'centimetros', 'metros' y 'kilometros' como unidades de medida");
            } else if (args[0] == "girar") {
                if (args[2] != "grados" && args[2] != "radianes")
                    throw runtime_error("El tipo de movimiento 'girar' solo permite 'grados' y 'radianes' "
                        "como unidades de medida");
            } else {
                throw runtime_error("El tipo del movimiento no corresponde a los datos esperados (avanzar, girar).");
            }
        }

        Movimiento(string tipo, float magn, string um) {
            
            tipo_movimiento = tipo;
            magnitud = magn;
            unidad_medida = um;
        }

        void ejecutar(RobotCuriosity &robot) {
            if (tipo_movimiento == "girar") {
                robot.girar(magnitud, unidad_medida);
            } else {
                robot.avanzar(magnitud, unidad_medida);
            }
        }

        string toString(char delim = ' ') {
            return tipo_movimiento + delim + to_string(magnitud) + delim + unidad_medida;
        }  
};

#endif