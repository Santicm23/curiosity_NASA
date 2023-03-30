
#include <string>
#include <vector>

#include "movimiento.h"

using namespace std;


void Movimiento::verificarDatos(vector<string> args) {
    float magn;
    if (args.size() != 3) throw runtime_error(
        "La informacion del movimiento no corresponde a los datos esperados (tipo, magnitud, unidad).");
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

Movimiento::Movimiento(string tipo, float magn, string um) {
    
    tipo_movimiento = tipo;
    magnitud = magn;
    unidad_medida = um;
}

void Movimiento::ejecutar(RobotCuriosity &robot) {
    if (tipo_movimiento == "girar") {
        robot.girar(magnitud, unidad_medida);
    } else {
        robot.avanzar(magnitud, unidad_medida);
    }
}

string Movimiento::toString(char delim = ' ') {
    return tipo_movimiento + delim + to_string(magnitud) + delim + unidad_medida;
}