
#ifndef COMANDOSISTEMA
#define COMANDOSISTEMA


#include <string>
#include <vector>
#include <functional>

#include "desplazamiento.h"
#include "movimiento.h"
#include "analisis.h"
#include "elemento.h"

using namespace std;


template<class sis>
class ComandoSistema {
    using funcion = function<void(sis&,vector<string>)>;

    private:
        string nombre;
        string descricion;
        funcion func;

    public:
        ComandoSistema() {}

        ComandoSistema(const ComandoSistema& comandoSistema) {
            nombre = comandoSistema.nombre;
            descricion = comandoSistema.descricion;
            func = comandoSistema.func;
        }

        ComandoSistema(string nom, string desc, funcion f) {
            nombre = nom;
            descricion = desc;
            func = f;
        }

        string& getDescripcion() {
            return descricion;
        }

        void operator()(sis& sistema, vector<string> args) {
            func(sistema, args);
        }
};

#endif