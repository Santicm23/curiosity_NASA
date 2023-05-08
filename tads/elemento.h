
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

        Elemento();

        Elemento(string tipo, float tam, string um, float x, float y);

        pair<float, float> getPunto();

        string toString(char delim);

        bool estaEnCuadrante(pair<float, float> min, pair<float, float> max);
};

#include "elemento.cxx"

#endif