
#ifndef COMANDOSISTEMA
#define COMANDOSISTEMA


#include <string>
#include <vector>
#include <functional>

using namespace std;


template<class sis>
class ComandoSistema {
    using funcion = function<void(sis&,vector<string>)>;

    private:
        string nombre;
        string descricion;
        funcion func;

    public:
        ComandoSistema();

        ComandoSistema(const ComandoSistema& comandoSistema);

        ComandoSistema(string nom, string desc, funcion f);

        string& getDescripcion();

        void operator()(sis& sistema, vector<string> args);
};

#include "comandoSistema.cxx"

#endif