
#include <string>
#include <vector>
#include <regex>

#include "elemento.h"

using namespace std;


void Elemento::verificarDatos(vector<string> args) {
    if (args.size() < 4) throw runtime_error(
        "La informacion del elemento no corresponde a los datos esperados (tipo, tamano, unidad_medida, coordenada_x, coordenada_y).");
        
    if (args[0] != "roca" && args[0] != "suelo" && args[0] != "agua") {
        throw runtime_error(
            "El tipo del elemento no corresponde a los datos esperados (roca, suelo, agua).");
    } else if (!regex_match(args[1], regex("[0-9]+(.[0-9]+)?"))) {
        throw runtime_error("El tamano del elemento debe ser un numero.");
    } else if (args[2] != "m" && args[2] != "cm" && args[2] != "mm") {
        throw runtime_error("La unidad de medida del elemento no corresponde a los datos esperados (m, cm, mm).");
    } else if (!regex_match(args[3], regex("[0-9]+(.[0-9]+)?"))) {
        throw runtime_error("La coordenada x del elemento debe ser un numero.");
    } else if (!regex_match(args[4], regex("[0-9]+(.[0-9]+)?"))) {
        throw runtime_error("La coordenada y del elemento debe ser un numero.");
    }
}

Elemento::Elemento(string tipo, float tam, string um, float x, float y) {
    tipo_elemento = tipo;
    tamano = tam;
    unidad_medida = um;
    coordenada_x = x;
    coordenada_y = y;
}

string Elemento::toString(char delim = ' ') {
    return tipo_elemento + delim + to_string(tamano) + delim + unidad_medida
        + delim + to_string(coordenada_x) + delim + to_string(coordenada_y);
}