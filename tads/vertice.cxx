#include "vertice.h"
#include "elemento.h"

using namespace std;

void Vertice::insertarArista(float distancia, Vertice& verticeDestino) {
    Arista nuevaArista(distancia, verticeDestino);
    adyacentes.insert(nuevaArista);
}

void Vertice::eliminarArista(Vertice& verticeDestino) {
     for (Arista arista: this->adyacentes) {
        if (arista.second.getId() == verticeDestino.getId()) {
            adyacentes.erase(arista);
            break;
        }
    }
}

int Vertice::getId() {
    return id;
}
void Vertice::setId(int k) {
    this->id=k;
}


Elemento Vertice::getElemento() {
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

float Vertice::retornarCosto(Vertice& verticeDestino) {
    for (Arista arista: this->adyacentes) {
        if (arista.second.getId() == verticeDestino.getId()) {
            return arista.first;
        }
    }
    return -1;
}
bool Vertice::getmarcado()
{
    return this->marcado;
}