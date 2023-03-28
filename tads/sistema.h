
#ifndef SISTEMA
#define SISTEMA


#include <string>
#include <list>
#include <vector>
#include <map>

#include "desplazamiento.h"
#include "elemento.h"
#include "comandoSistema.h"

using namespace std;


class Sistema {
    using funcion = function<void(list<Desplazamiento>&,list<Elemento>&,vector<string>)>;

    private:
        map<string, ComandoSistema> comandos;
        list<Desplazamiento> desplazamientos;
        list<Elemento> elementos;
        
    public:
        Sistema() {}

        void agregar_comando(string nombre, string desc, funcion func) {
            comandos.insert({nombre, ComandoSistema(nombre, desc, func)});
        }

        void ayuda(vector<string> args) {
            if (args.empty()){
                for (pair<const string, ComandoSistema> tupla: comandos) {
                    cout << "\t" << tupla.first << endl;
                }
            } else if (args.size() == 1) {
                if (comandos.count(args[0]) > 0) {
                    cout << "\t" << comandos[args[0]].getDescripcion() << endl;
                } else {
                    throw runtime_error("No se encontro el comando '" + args[0] + "'");
                }
            } else {
                throw runtime_error("El comando 'ayuda' recibe maximo un argumento");
            }
        }

        bool comando_existe(string nombre) {
            return comandos.count(nombre) > 0;
        }

        void ejecutar(string comando, vector<string> args) {
            if (!comando_existe(comando))
                throw runtime_error("El comando '" + comando + "' no existe");

            if (comando == "ayuda") {
                ayuda(args);
            } else {
                comandos[comando](desplazamientos, elementos, args);
            }
        }
};

#endif