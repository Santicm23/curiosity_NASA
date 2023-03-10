
#ifndef ELEMENTO
#define ELEMENTO


#include <string>

using namespace std;


class Elemento {
    private:
        string tipo_elemento;
        float tamano;
        string unidad_medida;
        float coordenada_x;
        float coordenada_y;
    
    public:
        static void verificarDatos(string tipo, float tam, string um) {
            if (tipo != "roca" && tipo != "crater" && tipo != "monticulo" && tipo != "duna")
                throw runtime_error("El tipo de elemento no es valido ('roca', 'crater', 'monticulo' o 'duna')");
            if (tam <= 0)
                throw runtime_error("El tamano del elemento no es valido, debe ser mayor que 0");
            if (um != "centimetros" && um != "metros" && um != "kilometros")
                throw runtime_error(
                    "La unidad de medida del elemento no es valida ('centimetro', 'metro' o 'kilometro')");
        }

        Elemento(string tipo, float tam, string um, float x, float y) {
            tipo_elemento = tipo;
            tamano = tam;
            unidad_medida = um;
            coordenada_x = x;
            coordenada_y = y;
        }

        string toString() {
            return tipo_elemento + " " + to_string(tamano) + " " + unidad_medida
                + " " + to_string(coordenada_x) + " " + to_string(coordenada_y);
        }
};

#endif