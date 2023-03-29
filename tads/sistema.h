
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


void nada(...) {}

class Sistema {

    using funcion = function<void(Sistema&,vector<string>)>;

    private:
        map<string,ComandoSistema<Sistema>> comandos;
        list<Desplazamiento*> desplazamientos;
        list<Elemento*> elementos;
        
    public:
        Sistema() {}

        list<Desplazamiento*>& getDesplazamientos() {
            return desplazamientos;
        }

        list<Elemento*>& getElementos() {
            return elementos;
        }

        void agregar_comando(string nombre, string desc, funcion func = nada) {
            comandos.insert({nombre, ComandoSistema<Sistema>(nombre, desc, func)});
        }

        void ayuda(vector<string> args) {
            if (args.empty()){
                for (pair<const string,ComandoSistema<Sistema>> tupla: comandos) {
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
            return comandos.count(nombre) > 0 || nombre == "ayuda";
        }

        void ejecutar(string comando, vector<string> args) {
            if (!comando_existe(comando))
                throw runtime_error("El comando '" + comando + "' no existe");

            if (comando == "ayuda") {
                ayuda(args);
            } else {
                comandos[comando](*this, args);
            }
        }
};

#endif