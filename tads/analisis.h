
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
        static void verificarDatos(vector<string> args) {
            if (args.size() != 2 && args.size() != 3) throw runtime_error(
                "Los comandos de analisis requieren tipo_analisis, objeto y comentario(opcional) como argumentos");
                
            if (args[0] != "fotografiar" && args[0] != "composicion" && args[0] != "perforar") {
                throw runtime_error(
                    "El tipo del analisis no corresponde a los datos esperados (fotografiar, composicion, perforar).");
            } else if (args.size() == 3 && !regex_match(args[2], regex("'([a-zA_Z0-9_!.,;+/*%?¡¿@#()><= ]|-)*'"))) {
                throw runtime_error("El comentario debe estar entre comillas simples, sin acentos");
            }
        }

        Analisis(string tipo, string obj, string coment = "") {
            tipo_analisis = tipo;
            objeto = obj;
            comentario = coment;
        }
        
        string toString(char delim = ' ') {
            return tipo_analisis + delim + objeto + delim + comentario;
        }
};

#endif