
#include <string>
#include <vector>
#include <regex>
#include <math.h>

#include "elemento.h"

using namespace std;


void Elemento::verificarDatos(vector<string> args) {
    float tam, x, y;
    if (args.size() != 5) throw runtime_error(
        "La informacion del elemento no corresponde a los datos esperados (tipo, tamano, unidad, x, y).");
    try {
        tam = stof(args[1]);
        x = stof(args[3]);
        y = stof(args[4]);
    } catch(const invalid_argument& e) {
        throw runtime_error("El tamano, y las coordenadas X y Y deben ser numeros flotantes");
    }
    if (args[0] != "roca" && args[0] != "crater" && args[0] != "monticulo" && args[0] != "duna" && args[0] != "arena") {
        throw runtime_error(
            "El tipo de elemento no es valido ('roca', 'crater', 'monticulo', 'duna' o 'arena')");
    } else if (tam < 0) {
        throw runtime_error("El tamano del elemento no es valido, debe ser mayor que 0");
    } else if (args[2] != "centimetros" && args[2] != "metros" && args[2] != "kilometros") {
        throw runtime_error(
            "La unidad de medida del elemento no es valida ('centimetros', 'metros' o 'kilometros')");
    }
}

Elemento::Elemento() {
    tipo_elemento = "";
    tamano = 0;
    unidad_medida = "";
    coordenada_x = 0;
    coordenada_y = 0;
}

Elemento::Elemento(string tipo, float tam, string um, float x, float y) {
    tipo_elemento = tipo;
    tamano = tam;
    unidad_medida = um;
    coordenada_x = x;
    coordenada_y = y;
}

pair<float, float> Elemento::getPunto() {
    return make_pair(coordenada_x, coordenada_y);
}

string Elemento::toString(char delim = ' ') {
    return tipo_elemento + delim + to_string(tamano) + delim + unidad_medida
        + delim + to_string(coordenada_x) + delim + to_string(coordenada_y);
}

bool Elemento::estaEnCuadrante(pair<float, float> min, pair<float, float> max) {
    return (min.first <= coordenada_x && coordenada_x <= max.first)
        && (min.second <= coordenada_y && coordenada_y <= max.second);
}
float calcularDistancia(Elemento uno, Elemento dos)
{
    return pow(pow((uno.getPunto().second-uno.getPunto().first),2)+pow((dos.getPunto().second-dos.getPunto().first),2),1/2);
}