
#include <string>
#include <sstream>
#include <list>
#include <vector>
#include <map>

#include "sistema.h"
#include "arbolQuad.h"


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
}

Sistema::Sistema(const Sistema& sistema) {
    comandos = sistema.comandos;
    desplazamientos = sistema.desplazamientos;
    elementos = sistema.elementos;
    robot = sistema.robot;
    this->arbolElementos = ArbolQuad();
}

map<string,ComandoSistema<Sistema>>& Sistema::getComandos() {
    return comandos;
}

list<Desplazamiento*>& Sistema::getDesplazamientos() {
    return desplazamientos;
}

list<Elemento*>& Sistema::getElementos() {
    return elementos;
}

ArbolQuad& Sistema::getArbolElementos() {
    return arbolElementos;
}

RobotCuriosity& Sistema::getRobot() {
    return robot;
}

string Sistema::obtenerExtension(string nombreArchivo) {
    char delim = '.';
    string palabra;
    stringstream ss(nombreArchivo);
    while (getline(ss, palabra, delim));
    return palabra;
}

void Sistema::agregar_comando(string nombre, string desc, funcion func) {
    comandos.insert({nombre, ComandoSistema<Sistema>(nombre, desc, func)});
}

void Sistema::agregar_desplazamiento(Desplazamiento* desp) {
    desplazamientos.push_back(desp);
}

void Sistema::agregar_desplazamiento(string linea, char delim) {
    desplazamientos.push_back(crearDesplazamiento(linea, delim));
}

void Sistema::agregar_elemento(Elemento* elem) {
    elementos.push_back(elem);
}

void Sistema::agregar_elemento(string linea, char delim) {
    elementos.push_back(crearElemento(linea, delim));
}

void Sistema::borrar_desplazamientos() {
    for (Desplazamiento* desp: desplazamientos) {
        delete desp;
    }
    desplazamientos.clear();
}

void Sistema::borrar_elementos() {
    for (Elemento* elem: elementos) {
        delete elem;
    }
    elementos.clear();
}

bool Sistema::comando_existe(string nombre) {
    return comandos.find(nombre) != comandos.end();
}

void Sistema::ejecutar(string comando, vector<string> args) {
    if (!comando_existe(comando))
        throw runtime_error("El comando '" + comando + "' no existe");

    comandos[comando](*this, args);
}

void Sistema::salir() {
    this->borrar_elementos();
    this->borrar_desplazamientos();
    arbolElementos.~ArbolQuad();
}