
#include <string>
#include <sstream>
#include <list>
#include <vector>
#include <utility>
#include <map>

#include "sistema.h"
#include "arbolQuad.h"
#include "grafo.h"


//! ----- Funciones adicionales -----

// crear un comando de desplazamiento a partir de un string
Desplazamiento* crearDesplazamiento(string linea, char delim = ' ') {
    string palabra;

    stringstream ss(linea);
    vector<string> palabras;

    getline(ss, palabra, delim); 
    palabras.push_back(palabra); 

    if (palabras[0] == "avanzar" || palabras[0] == "girar") {
        while (getline(ss, palabra, delim))
            palabras.push_back(palabra);

        Movimiento::verificarDatos(palabras); //* Se verifica que que todos los datos sean del tipo correcto

        return new Movimiento(palabras[0], stof(palabras[1]), palabras[2]);
        
    } else if (palabras[0] == "fotografiar" || palabras[0] == "composicion" || palabras[0] == "perforar") {
        while (getline(ss, palabra, delim))
            palabras.push_back(palabra);
            
        Analisis::verificarDatos(palabras); //* Se verifica que que todos los datos sean del tipo correcto

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

// crear un elemento de interes a partir de un string
Elemento* crearElemento(string linea, char delim = ' ') {
    string palabra;
    vector<string> palabras;

    stringstream ss(linea);

    while (getline(ss, palabra, delim))
        palabras.push_back(palabra);
    
    Elemento::verificarDatos(palabras); //* Se verifica que que todos los datos sean del tipo correcto

    return new Elemento(palabras[0], stof(palabras[1]), palabras[2], stof(palabras[3]), stof(palabras[4]));
}


//! ----- Implementacion del TAD -----

Sistema::Sistema() {
    this->arbolElementos = ArbolQuad();
    this->mapa = Grafo();
}

Sistema::Sistema(const Sistema& sistema) {
    this->comandos = sistema.comandos;
    this->desplazamientos = sistema.desplazamientos;
    this->elementos = sistema.elementos;
    this->robot = sistema.robot;
    this->arbolElementos = ArbolQuad();
}

map<string,ComandoSistema<Sistema>>& Sistema::getComandos() {
    return this->comandos;
}

list<Desplazamiento*>& Sistema::getDesplazamientos() {
    return this->desplazamientos;
}

list<Elemento*>& Sistema::getElementos() {
    return this->elementos;
}

ArbolQuad& Sistema::getArbolElementos() {
    return this->arbolElementos;
}

RobotCuriosity& Sistema::getRobot() {
    return this->robot;
}

Grafo& Sistema::getMapa() {
    return this->mapa;
}

string Sistema::obtenerExtension(string nombreArchivo) {
    char delim = '.';
    string palabra;
    stringstream ss(nombreArchivo);
    while (getline(ss, palabra, delim));
    return palabra;
}

void Sistema::agregar_comando(string nombre, string desc, funcion func) {
    this->comandos.insert({nombre, ComandoSistema<Sistema>(nombre, desc, func)});
}

void Sistema::agregar_desplazamiento(Desplazamiento* desp) {
    this->desplazamientos.push_back(desp);
}

void Sistema::agregar_desplazamiento(string linea, char delim) {
    this->desplazamientos.push_back(crearDesplazamiento(linea, delim));
}

void Sistema::agregar_elemento(Elemento* elem) {
    this->elementos.push_back(elem);
}

void Sistema::agregar_elemento(string linea, char delim) {
    this->elementos.push_back(crearElemento(linea, delim));
}

list<pair<Elemento*, float>> Sistema::elementos_cercanos(Elemento* elem, int n) {
    list<pair<Elemento*, float>> l_res;

    list<Elemento*> list_copy = this->elementos;

    list_copy.remove(elem);

    for (Elemento* el: list_copy) {
        
        float dist_tmp = elem->calcularDistancia(*el);

        if (l_res.empty()) {
            l_res.push_back(make_pair(el, dist_tmp));

        } else {
            bool added = false;

            for (list<pair<Elemento*, float>>::iterator it = l_res.begin(); it != l_res.end(); it++) {
                if (dist_tmp < it->second && l_res.size() < n) {
                    l_res.insert(it, make_pair(el, dist_tmp));
                    added = true;
                    break;
                }
            }

            if (!added && l_res.size() < n) {
                l_res.push_back(make_pair(el, dist_tmp));
            }
        }
    }

    return l_res;
}

float Sistema::dist(int k, int i, int j){
    if (k == 0) {
        return this->mapa.CostoArco(i, j);
    } else {
        return max(dist(k-1, i, j), dist(k-1, i, k) + dist(k-1, k, j));
    }
}

void Sistema::borrar_desplazamientos() {
    for (Desplazamiento* desp: this->desplazamientos) {
        delete desp;
    }
    this->desplazamientos.clear();
}

void Sistema::borrar_elementos() {
    for (Elemento* elem: this->elementos) {
        delete elem;
    }
    this->elementos.clear();
}

void Sistema::borrar_arbol() {
    this->arbolElementos.~ArbolQuad();
    this->arbolElementos = ArbolQuad();
}

void Sistema::borrar_mapa() {
    this->mapa.borrar();
}

bool Sistema::comando_existe(string nombre) {
    return this->comandos.find(nombre) != this->comandos.end();
}

void Sistema::ejecutar(string comando, vector<string> args) {
    if (!comando_existe(comando))
        throw runtime_error("El comando '" + comando + "' no existe");

    this->comandos[comando](*this, args);
}

void Sistema::salir() {
    this->borrar_elementos();
    this->borrar_desplazamientos();
    this->arbolElementos.~ArbolQuad();
    this->mapa.~Grafo();
}