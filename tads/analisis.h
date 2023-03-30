
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
        string comentario;
    
    public:
        static void verificarDatos(vector<string> args);

        Analisis(string tipo, string obj, string coment);
        
        string toString(char delim);
};

#include "analisis.cxx"

#endif