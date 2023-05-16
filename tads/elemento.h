
#ifndef ELEMENTO
#define ELEMENTO


#include <utility>
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
        Elemento();

        Elemento(string tipo, float tam, string um, float x, float y);

        //* verificar que los datos del vector correspondan a la clase
        static void verificarDatos(vector<string> args);

        //* obtener el punto donde se encuentra el elemento
        pair<float, float> getPunto();

        //* conviertir la información del desplazamiento a un string
        string toString(char delim);

        //* verificar que el elemento esta en el cuadrante ingresado
        bool estaEnCuadrante(pair<float, float> min, pair<float, float> max);

        //* calcular distancia entre el elemento y otro dado
        float calcularDistancia(Elemento elem);
        
};

#include "elemento.cxx"

#endif