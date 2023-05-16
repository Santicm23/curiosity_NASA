#include <list>

#include "vertice.h"
#include "elemento.h"


using namespace std;

Vertice::Vertice() {}

Vertice::Vertice(Elemento* elem) {
    this->elemento = elem;
}


Elemento* Vertice::getElemento() {
    return elemento;
}

void Vertice::marcar() {
    this->marcado = true;
}

void Vertice::desmarcar() {
    this->marcado = false;
}

bool Vertice::estaMarcado() {
    return this->marcado;
}