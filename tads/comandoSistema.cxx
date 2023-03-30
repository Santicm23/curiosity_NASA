
#include <string>
#include <vector>

#include "comandoSistema.h"


template<class sis>
ComandoSistema<sis>::ComandoSistema() {}

template<class sis>
ComandoSistema<sis>::ComandoSistema(const ComandoSistema& comandoSistema) {
    nombre = comandoSistema.nombre;
    descricion = comandoSistema.descricion;
    func = comandoSistema.func;
}

template<class sis>
ComandoSistema<sis>::ComandoSistema(string nom, string desc, funcion f) {
    nombre = nom;
    descricion = desc;
    func = f;
}

template<class sis>
string& ComandoSistema<sis>::getDescripcion() {
    return descricion;
}

template<class sis>
void ComandoSistema<sis>::operator()(sis& sistema, vector<string> args) {
    func(sistema, args);
}