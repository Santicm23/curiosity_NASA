
#include <string>
#include <sstream>
#include <list>
#include <vector>
#include <map>

#include "sistema.h"


Sistema::Sistema() {}

Sistema::Sistema(const Sistema& sistema) {
    comandos = sistema.comandos;
    desplazamientos = sistema.desplazamientos;
    elementos = sistema.elementos;
    robot = sistema.robot;
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