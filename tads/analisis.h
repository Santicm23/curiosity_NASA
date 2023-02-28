
#ifndef ANALISIS
#define ANALISIS


#include <string>

#include "desplazamiento.h"

using namespace std;


class Analisis : public Desplazamiento {
    private:
        string tipo_analisis;
        string objeto;
        string comentario;
    
    public:
        Analisis(string tipo, string obj, string coment = "") {
            tipo_analisis = tipo;
            objeto = obj;
            comentario = coment;
        }
         string toString() {
            return tipo_analisis + " " + objeto + " " + comentario;
        }
};

#endif