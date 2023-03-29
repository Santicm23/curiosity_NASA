
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

                if (palabras.size() != 3) throw runtime_error(
                    "Los comandos de movimiento requieren tipo_movimiento, magnitud y unidad_medida como argumentos");

                Movimiento::verificarDatos(palabras[0], palabras[2]);

                try {
                    return new Movimiento(palabras[0], stof(palabras[1]), palabras[2]);
                } catch (const invalid_argument& e) {
                    throw runtime_error("La magnitud del comando debe ser un numero flotante");
                }
                
            } else if (palabras[0] == "fotografiar" || palabras[0] == "composicion" || palabras[0] == "perforar") {
                
                getline(ss, palabra, delim);
                palabras.push_back(palabra);

                if (getline(ss, palabra))
                    palabras.push_back(palabra);

                if (palabras.size() == 2) {
                    return new Analisis(palabras[0], palabras[1]);
                    
                } else if (palabras.size() == 3) {
                    if (!regex_match(palabras[2], regex("'([a-zA_Z0-9_!.,;+/*%?¡¿@#()><= ]|-)*'"))) 
                        throw runtime_error("El comentario debe estar entre comillas simples, sin acentos");
                    return new Analisis(palabras[0], palabras[1], palabras[2]);

                } else throw runtime_error(
                    "Los comandos de analisis requieren tipo_analisis, objeto y comentario(opcional) como argumentos");

            } else throw runtime_error("El tipo de comando no es valido");
        }

        // funcion que crea y retorna un elemento de interes a partir de una linea
        static Elemento* crearElemento(string linea, char delim = ' ') {
            string palabra;
            vector<string> palabras;

            stringstream ss(linea);

            while (getline(ss, palabra, delim))
                palabras.push_back(palabra);

            if (palabras.size() != 5) throw runtime_error(
                "Los comandos de movimiento requieren tipo_elemento, tamano, unidad_medida, coordenada_x, coordenada_y");
            
            if (palabras[0] != "roca" && palabras[0] != "crater" && palabras[0] != "monticulo" && palabras[0] != "duna")
                throw runtime_error("El tipo de elemento no es valido ('roca', 'crater', 'monticulo' o 'duna')");

            try {
                return new Elemento(palabras[0], stof(palabras[1]), palabras[2], stof(palabras[3]), stof(palabras[4]));
            } catch (const invalid_argument& e) {
                throw runtime_error("El tamano, y las coordenadas X y Y deben ser numeros flotantes");
            }
        }

        // funcion que retorna la extension de un nombre de archivo dado
        static string obtenerExtension(string nombreArchivo) {
            char delim = '.';
            string palabra;
            stringstream ss(nombreArchivo);
            while (getline(ss, palabra, delim)) {}
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