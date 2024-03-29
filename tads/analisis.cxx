
#include <string>
#include <vector>

#include "analisis.h"


void Analisis::verificarDatos(vector<string> args) {
    if (args.size() < 2) throw runtime_error(
        "La informacion del analisis no corresponde a los datos esperados (tipo, objeto, comentario).");
        
    if (args[0] != "fotografiar" && args[0] != "composicion" && args[0] != "perforar") {
        throw runtime_error(
            "El tipo del analisis no corresponde a los datos esperados (fotografiar, composicion, perforar).");
    } else if (args.size() >= 3) {
        string com = args[2];
        for (int i=3; i<args.size(); i++) {
            com += " " + args[i];
        }
        if (!regex_match(com, regex("'([a-zA-Z0-9_!.,;+/*%?¡¿@#()><= ]|-)*'"))) {
            throw runtime_error("El comentario debe estar entre comillas simples, sin acentos");
        }
    }
}

Analisis::Analisis(string tipo, string obj, string coment = "") {
    tipo_analisis = tipo;
    objeto = obj;
    comentario = coment;
}

string Analisis::toString(char delim = ' ') {
    return tipo_analisis + delim + objeto + ((comentario != "")? delim + comentario : "");
}
