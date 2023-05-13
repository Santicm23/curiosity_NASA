#include <list>

#include "vertice.h"
#include "elemento.h"


using namespace std;

Vertice::Vertice() {}

Vertice::Vertice(int id, Elemento* elem) {
    this->id = id;
    this->elemento = elem;
}

Vertice::Vertice(int id, Elemento* elem, list<Arista> adyacentes){
    this->id = id;
    this->elemento = elem;
    this->adyacentes = adyacentes;
}

Vertice::~Vertice() {
    delete this->elemento;
}

void Vertice::insertarArista(float distancia, Vertice* verticeDestino) {
    Arista nuevaArista = make_pair(distancia, verticeDestino);
    this->adyacentes.push_back(nuevaArista);
}

void Vertice::eliminarArista(Vertice* verticeDestino) {
     for (Arista arista: this->adyacentes) {
        if (arista.second->getId() == verticeDestino->getId()) {
            adyacentes.remove(arista);
            return;
        }
    }
}

int Vertice::getId() {
    return id;
}
void Vertice::setId(int k) {
    this->id = k;
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
    return marcado;
}

float Vertice::retornarCosto(Vertice* verticeDestino) {
    for (Arista arista: this->adyacentes) {
        if (arista.second->getId() == verticeDestino->getId()) {
            return arista.first;
        }
    }
    return -1;
}
bool Vertice::getmarcado()
{
    return this->marcado;
}

list<int> Vertice::getAdyacentes() {
    list<int> idVertices;
    for (list<Arista>::iterator it = adyacentes.begin(); it != adyacentes.end(); ++it) {
        Arista arista = *it;
        idVertices.push_back(arista.second->getId());
    }
    return idVertices;
}