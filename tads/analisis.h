
#ifndef ANALISIS
#define ANALISIS


#include <string>
#include <regex>

#include "desplazamiento.h"

using namespace std;


class Analisis : public Desplazamiento {
    private:
        string tipo_analisis;
        string objeto;
        string comentario; //* entre comillas
    
    public:
        Analisis(string tipo, string obj, string coment);

        //* verificar que los datos del vector correspondan a la clase
        static void verificarDatos(vector<string> args);
        
        //* conviertir la información del desplazamiento a un string
        string toString(char delim);
};

#include "analisis.cxx"

#endif