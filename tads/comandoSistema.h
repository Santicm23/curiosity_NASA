
#ifndef COMANDOSISTEMA
#define COMANDOSISTEMA


#include <string>
#include <vector>
#include <functional>

#include "desplazamiento.h"
#include "elemento.h"

using namespace std;


class ComandoSistema {
    using funcion = function<void(list<Desplazamiento>&,list<Elemento>&,vector<string>)>;

    private:
        string nombre;
        string descricion;
        funcion func;
    public:
        ComandoSistema(string nom, string desc, funcion f) {
            nombre = nom;
            descricion = desc;
            func = f;
        }

        string getDescripcion() {
            return descricion;
        }

        void operator()(list<Desplazamiento>& ld, list<Elemento>& le, vector<string> args) {
            func(ld, le, args);
        }
};

#endif