
#include "arbolQuad.h"

using namespace std;


ArbolQuad::ArbolQuad() {
    raiz = nullptr;
}

ArbolQuad::ArbolQuad(Elemento& val) {
    raiz = new NodoQuad(val);
}

ArbolQuad::~ArbolQuad() {
    delete raiz;
    raiz = nullptr;
}

Elemento& ArbolQuad::datoRaiz() {
    return raiz->obtenerDato();
}

NodoQuad* ArbolQuad::obtenerRaiz() {
    return raiz;
}

void ArbolQuad::fijarRaiz(NodoQuad* n_raiz) {
    raiz = n_raiz;
}

bool ArbolQuad::esVacio() {
    return raiz == nullptr;
}

bool ArbolQuad::esHoja() {
    return raiz->esHoja();
}

bool ArbolQuad::insertar(Elemento& val) {
    if (raiz == nullptr) {
        raiz = new NodoQuad(val);
        return true;
    } else {
        return raiz->insertar(val);
    }
}

void ArbolQuad::preOrden() {
    if (raiz != nullptr) {
        raiz->preOrden();
    }
}

void ArbolQuad::inOrden() {
    if (raiz != nullptr) {
        raiz->inOrden();
    }
}

void ArbolQuad::posOrden() {
    if (raiz != nullptr) {
        raiz->posOrden();
    }
}

void ArbolQuad::nivelOrden() {
    if (raiz != nullptr) {
        raiz->nivelOrden();
    }
}

list<Elemento> ArbolQuad::en_cuadrante(pair<float, float> min, pair<float, float> max) {
    return this->raiz->en_cuadrante(min, max);
}