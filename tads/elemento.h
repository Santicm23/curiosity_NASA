
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
        Elemento(string tipo, float tam, string um, float x, float y) {
            tipo_elemento = tipo;
            tamano = tam;
            unidad_medida = um;
            coordenada_x = x;
            coordenada_y = y;
        }
};

#endif