#include "grafo.h"

using namespace std;


Grafo::Grafo() {}

int Grafo::idVertice(Elemento* el) {
    int k = 0;
    for (Vertice v: this->vertices) {
        if (v.getElemento() == el) {
            return k;
        }
        k++;
    }

    throw runtime_error("El elemento no se encuentra en el mapa");
}

Elemento* Grafo::InfoVertice(int v) {
    if (v >= this->aristas.size())
        throw runtime_error("El vertice no existe en el grafo.");

    list<Vertice>::iterator it = this->vertices.begin();
    advance(it, v);

    return it->getElemento();
}

void Grafo::InsVertice(Elemento* v) {
    vertices.push_back(Vertice(v));
    aristas.push_back(set<Arista>());
}

bool Grafo::existeVertice(Elemento* el) {
    for (Vertice v: this->vertices) {
        if (v.getElemento() == el) {
            return true;
        }
    }
    return false;
}

void Grafo::InsArco(int v1, int v2, float c) {
    if (v1 >= this->vertices.size() || v2 >= this->vertices.size())
        throw runtime_error("No se encontraron los vertices indicados.");
        
    list<set<Arista>>::iterator it = this->aristas.begin();
    advance(it, v1);

    it->insert({c, v2});
}

void Grafo::ElimArco(int v1, int v2) {
    if (v1 >= this->vertices.size() || v2 >= this->vertices.size())
        return;
    
    list<set<Arista>>::iterator it1 = this->aristas.begin();
    advance(it1, v1);

    for (Arista a: *it1) {
        if (a.second == v2) {
            it1->erase(a);
            return;
        }
    }

}

int Grafo::OrdenGrafo() const {
    return vertices.size();
}

float Grafo::CostoArco(int v1, int v2) {
    if (v1 == v2){
        return 0;
    }
    
    list<set<Arista>>::iterator it1 = this->aristas.begin();
    advance(it1, v1);

    for (Arista a: *it1) {
        if (a.second == v2) {
            return a.first;
        }
    }

    return -1;
}

bool Grafo::MarcadoVertice(int v) {
    if (v >= this->aristas.size())
        throw runtime_error("El vertice no existe en el grafo.");

    list<Vertice>::iterator it = this->vertices.begin();
    advance(it, v);

    return it->estaMarcado();
}

void Grafo::DesmarcarGrafo() {
    for (Vertice vertice: this->vertices) {
        vertice.desmarcar();
    }
}

void Grafo::DesmarcarVertice(int v) {
    if (v >= this->aristas.size())
        throw runtime_error("El vertice no existe en el grafo.");

    list<Vertice>::iterator it = this->vertices.begin();
    advance(it, v);

    it->desmarcar();
}

void Grafo::MarcarVertice(int v) {
    if (v >= this->aristas.size())
        throw runtime_error("El vertice no existe en el grafo.");

    list<Vertice>::iterator it = this->vertices.begin();
    advance(it, v);

    return it->marcar();
}

list<Elemento*> Grafo::getVertices() {
    list<Elemento*> elemVertices;
    for (Vertice v: this->vertices) {
        elemVertices.push_back(v.getElemento());
    }
    return elemVertices;
}

// void Grafo::ElimVertice(int v) {
//     if (v >= this->aristas.size())
//         throw runtime_error("El vertice no existe en el grafo.");

//     list<Vertice>::iterator it1 = this->vertices.begin();
//     advance(it1, v);
//     this->vertices.erase(it1);

//     list<set<Arista>>::iterator it2 = this->aristas.begin();
//     advance(it2, v);
//     this->aristas.erase(it2);

//     for (set<Arista> s: this->aristas) {
        
//     }
// }

list<int> Grafo::sucesores(int v) {
    if (v >= this->aristas.size())
        throw runtime_error("El vertice no existe en el grafo.");

    list<set<Arista>>::iterator it1 = this->aristas.begin();
    advance(it1, v);

    list<int> l_res;

    for (Arista a: *it1) {
        l_res.push_back(a.second);
    }

    return l_res;
}

void Grafo::borrar() {
    this->aristas.clear();
    this->vertices.clear();
}