
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

using namespace std;


// funcion que crea y retorna un comando de desplazamiento a partir de una linea
Desplazamiento* crearDesplazamiento(string linea, char delim = ' ') {
    string palabra;

    stringstream ss(linea);
    vector<string> palabras;

    getline(ss, palabra, delim); 
    palabras.push_back(palabra); 

    if (palabras[0] == "avanzar" || palabras[0] == "girar") {
        while (getline(ss, palabra, delim))
            palabras.push_back(palabra);

        Movimiento::verificarDatos(palabras); // verifica el cast y los valores antes de crear el objeto

        return new Movimiento(palabras[0], stof(palabras[1]), palabras[2]);
        
    } else if (palabras[0] == "fotografiar" || palabras[0] == "composicion" || palabras[0] == "perforar") {
        while (getline(ss, palabra, delim))
            palabras.push_back(palabra);
            
        Analisis::verificarDatos(palabras);

        if (palabras.size() == 2) {
            return new Analisis(palabras[0], palabras[1]);
        } else {
            string comentario = palabras[2];
            for (int i=3; i<palabras.size(); i++) {
                comentario += delim + palabras[i];
            }
            return new Analisis(palabras[0], palabras[1], comentario);
        }

    } else {
        throw runtime_error("El tipo de comando no es valido (Movimiento: avanzar o girar; "
            "Analisis: fotografiar, composicion o perforar)");
    }
    
}

// funcion que crea y retorna un elemento de interes a partir de una linea
Elemento* crearElemento(string linea, char delim = ' ') {
    string palabra;
    vector<string> palabras;

    stringstream ss(linea);

    while (getline(ss, palabra, delim))
        palabras.push_back(palabra);
    
    Elemento::verificarDatos(palabras);

    return new Elemento(palabras[0], stof(palabras[1]), palabras[2], stof(palabras[3]), stof(palabras[4]));
}

class Sistema {

    using funcion = function<void(Sistema&,vector<string>)>;

    private:
        map<string,ComandoSistema<Sistema>> comandos;
        list<Desplazamiento*> desplazamientos;
        list<Elemento*> elementos;
        RobotCuriosity robot;
        
    public:
        Sistema();

        Sistema(const Sistema& sistema);

        map<string,ComandoSistema<Sistema>>& getComandos();

        list<Desplazamiento*>& getDesplazamientos();

        list<Elemento*>& getElementos();

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