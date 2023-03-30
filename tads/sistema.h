
#ifndef SISTEMA
#define SISTEMA


#include <string>
#include <list>
#include <vector>
#include <map>

#include "desplazamiento.h"
#include "elemento.h"
#include "comandoSistema.h"
#include "robotCuriosity.h"

using namespace std;


class Sistema {

    using funcion = function<void(Sistema&,vector<string>)>;

    private:
        map<string,ComandoSistema<Sistema>> comandos;
        list<Desplazamiento*> desplazamientos;
        list<Elemento*> elementos;
        RobotCuriosity robot;
        
    public:
        Sistema() {}

        map<string,ComandoSistema<Sistema>>& getComandos() { return comandos; }

        list<Desplazamiento*>& getDesplazamientos() { return desplazamientos; }

        list<Elemento*>& getElementos() { return elementos; }

        RobotCuriosity& getRobot() { return robot; }

        void agregar_comando(string nombre, string desc, funcion func) {
            comandos.insert({nombre, ComandoSistema<Sistema>(nombre, desc, func)});
        }
        
        void agregar_desplazamiento(Desplazamiento* desp) {
            desplazamientos.push_back(desp);
        }
        
        void agregar_elemento(Elemento* elem) {
            elementos.push_back(elem);
        }

        void borrar_desplazamientos() {
            for (Desplazamiento* desp: desplazamientos) {
                delete desp;
            }
            desplazamientos.clear();
        }

        void borrar_elementos() {
            for (Elemento* elem: elementos) {
                delete elem;
            }
            elementos.clear();
        }

        bool comando_existe(string nombre) {
            return comandos.count(nombre) > 0 || nombre == "ayuda";
        }

        void ejecutar(string comando, vector<string> args) {
            if (!comando_existe(comando))
                throw runtime_error("El comando '" + comando + "' no existe");

            comandos[comando](*this, args);
        }
};

#endif