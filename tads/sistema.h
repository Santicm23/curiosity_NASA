
#ifndef SISTEMA
#define SISTEMA


#include <string>
#include <list>
#include <vector>
#include <map>

#include "desplazamiento.h"
#include "movimiento.h"
#include "analisis.h"
#include "elemento.h"
#include "comandoSistema.h"
#include "robotCuriosity.h"
#include "arbolQuad.h"


using namespace std;


class Sistema {

    using funcion = function<void(Sistema&,vector<string>)>;

    private:
        map<string,ComandoSistema<Sistema>> comandos;
        list<Desplazamiento*> desplazamientos;
        list<Elemento*> elementos;
        ArbolQuad arbolElementos; //QuadTree para almacenar mapa con los elementos de interés
        RobotCuriosity robot;
        
    public:
        Sistema();

        Sistema(const Sistema& sistema);

        map<string,ComandoSistema<Sistema>>& getComandos();

        list<Desplazamiento*>& getDesplazamientos();

        list<Elemento*>& getElementos();

        ArbolQuad& getArbolElementos();

        RobotCuriosity& getRobot();

        // funcion que retorna la extension de un nombre de archivo dado
        static string obtenerExtension(string nombreArchivo);

        void agregar_comando(string nombre, string desc, funcion func);
        
        void agregar_desplazamiento(Desplazamiento* desp);
        
        void agregar_desplazamiento(string linea, char delim = ',');
        
        void agregar_elemento(Elemento* elem);

        void agregar_elemento(string linea, char delim = ',');

        void borrar_desplazamientos();

        void borrar_elementos();

        bool comando_existe(string nombre);

        void ejecutar(string comando, vector<string> args);
};

#include "sistema.cxx"

#endif