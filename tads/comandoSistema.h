
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
        static Desplazamiento* crearDesplazamiento(string linea, char delim = ' ') {
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
                        comentario += " " + palabras[i];
                    }
                    return new Analisis(palabras[0], palabras[1], comentario);
                }

            } else {
                throw runtime_error("El tipo de comando no es valido (Movimiento: avanzar o girar; "
                    "Analisis: fotografiar, composicion o perforar)");
            }
            
        }

        // funcion que crea y retorna un elemento de interes a partir de una linea
        static Elemento* crearElemento(string linea, char delim = ' ') {
            string palabra;
            vector<string> palabras;

            stringstream ss(linea);

            while (getline(ss, palabra, delim))
                palabras.push_back(palabra);
            
            Elemento::verificarDatos(palabras);

            return new Elemento(palabras[0], stof(palabras[1]), palabras[2], stof(palabras[3]), stof(palabras[4]));
        }

        // funcion que retorna la extension de un nombre de archivo dado
        static string obtenerExtension(string nombreArchivo) {
            char delim = '.';
            string palabra;
            stringstream ss(nombreArchivo);
            while (getline(ss, palabra, delim));
            return palabra;
        }

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