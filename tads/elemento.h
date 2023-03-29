
#ifndef ELEMENTO
#define ELEMENTO


#include <string>
#include <vector>

using namespace std;


class Elemento {
    private:
        string tipo_elemento;
        float tamano;
        string unidad_medida;
        float coordenada_x;
        float coordenada_y;
    
    public:
        static void verificarDatos(vector<string> args) {
            float tam, x, y;
            if (args.size() != 5) throw runtime_error(
                "Los comandos de movimiento requieren tipo_elemento, tamano, unidad_medida, coordenada_x, coordenada_y");
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
                    "La unidad de medida del elemento no es valida ('centimetro', 'metro' o 'kilometro')");
            }
        }

        Elemento(string tipo, float tam, string um, float x, float y) {
            tipo_elemento = tipo;
            tamano = tam;
            unidad_medida = um;
            coordenada_x = x;
            coordenada_y = y;
        }

        string toString(char delim = ' ') {
            return tipo_elemento + delim + to_string(tamano) + delim + unidad_medida
                + delim + to_string(coordenada_x) + delim + to_string(coordenada_y);
        }
};

#endif