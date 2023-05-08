
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


//! ----- TAD Sistema ----- 

class Sistema {

    using funcion = function<void(Sistema&,vector<string>)>;

    private:
        map<string,ComandoSistema<Sistema>> comandos; //* map que contiene los comando del sistema
        list<Desplazamiento*> desplazamientos; //* lista que contiene los comandos de desplazamiento
        list<Elemento*> elementos; //* lista que contiene los elementos de interés
        ArbolQuad arbolElementos; //* QuadTree que almacena los elementos de interés en un plano cartesiano
        RobotCuriosity robot; //* robot de la nasa
        
    public:
        Sistema();

        Sistema(const Sistema& sistema);

        map<string,ComandoSistema<Sistema>>& getComandos();

        list<Desplazamiento*>& getDesplazamientos();

        list<Elemento*>& getElementos();

        ArbolQuad& getArbolElementos();

        RobotCuriosity& getRobot();

        //* obtener la extension de un nombre de archivo dado
        static string obtenerExtension(string nombreArchivo);

        //* agregar un comando del sistema
        void agregar_comando(string nombre, string desc, funcion func);
        
        //* cargar un comando de desplazamiento en el sistema
        void agregar_desplazamiento(Desplazamiento* desp);
        
        //* cargar un comando de desplazamiento en el sistema a partir de un string
        void agregar_desplazamiento(string linea, char delim = ',');
        
        //* cargar un elemento en el sistema
        void agregar_elemento(Elemento* elem);

        //* cargar un elemento en el sistema a partir de una string
        void agregar_elemento(string linea, char delim = ',');

        //* borrar los desplazamientos cargados en el sistema
        void borrar_desplazamientos();

        //* borrar los elementos cargados en el sistema
        void borrar_elementos();

        //* verificar que un comando existe
        bool comando_existe(string nombre);

        //* ejecutar un comando
        void ejecutar(string comando, vector<string> args);

        //* salir del sistema
        void salir();
};

#include "sistema.cxx"

#endif