
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
        static void verificarDatos(string tipo, string elem) {
            if (tipo != "fotografiar" && tipo != "composicion" && tipo != "perforar")
                throw runtime_error(
                    "El tipo del analisis no corresponde a los datos esperados (fotografiar, composicion, perforar).");
            if (elem != "roca" && elem != "crater" && elem != "monticulo" && elem != "duna" && elem != "arena")
                throw runtime_error("El tipo de elemento no es valido ('roca', 'crater', 'monticulo', 'duna' o 'arena')");
        }

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