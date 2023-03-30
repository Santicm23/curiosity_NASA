
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
        static void verificarDatos(vector<string> args);

        Elemento(string tipo, float tam, string um, float x, float y);

        string toString(char delim);
};

#include "elemento.cxx"

#endif