#include "grafo.h"

using namespace std;


Grafo::Grafo() {}

Grafo::~Grafo() {
    for (Vertice* v: this->vertices) {
        delete v;
    }
}

int Grafo::idVertice(Elemento* el) {
    for (Vertice* v: this->vertices) {
        if (v->getElemento() == el) {
            return v->getId();
        }
    }
    throw runtime_error("El elemento no se encuentra en el mapa");
}

Elemento* Grafo::InfoVertice(int v) {
    for (Vertice* vertice: vertices) {
        if (vertice->getId() == v) {
            return vertice->getElemento();
        }
    }
    throw runtime_error("El vertice no existe en el grafo.");
}

void Grafo::InsVertice(Elemento* v) {
    int k;
    if (vertices.empty()) {
        k = 1;
    } else {
        k = (*vertices.rbegin())->getId() + 1;
    }
    vertices.push_back(new Vertice(k, v));
}

bool Grafo::existeVertice(Elemento* el) {
    for (Vertice* v: this->vertices) {
        if (v->getElemento() == el) {
            return true;
        }
    }
    return false;
}

void Grafo::InsArco(int v1, int v2, float c) {
    Vertice* tempo1 = nullptr;
    Vertice* tempo2 = nullptr;
    for (Vertice* vertice : vertices) {
        if (vertice->getId() == v1) {
            tempo1 = vertice;
        }
        if (vertice->getId() == v2) {
            tempo2 = vertice;
        }
        if (tempo1 != nullptr && tempo2 != nullptr) {
            break;
        }
    }
    if (tempo1 != nullptr && tempo2 != nullptr) {
        tempo1->insertarArista(c, tempo2);
    } else {
        throw runtime_error("No se encontraron los vertices indicados.");
    }
}

void Grafo::ElimArco(int v1, int v2) {
    Vertice* tempo1 = nullptr;
    Vertice* tempo2 = nullptr;
    for (Vertice* vertice : vertices) {
        if (vertice->getId() == v1) {
            tempo1 = vertice;
        }
        if (vertice->getId() == v2) {
            tempo2 = vertice;
        }
        if (tempo1 != nullptr && tempo2 != nullptr) {
            break;
        }
    }
    if (tempo1 != nullptr && tempo2 != nullptr) {
        tempo1->eliminarArista(tempo2);
        tempo2->eliminarArista(tempo1);
    } else {
        throw std::runtime_error("No se encontraron los vertices indicados.");
    }
}

int Grafo::OrdenGrafo() const {
    return vertices.size();
}

int Grafo::CostoArco(int v1, int v2) {
    Vertice* tempo1 = nullptr;
    Vertice* tempo2 = nullptr;
    for (Vertice* vertice : vertices) {
        if (vertice->getId() == v1) {
            tempo1 = vertice;
        }
        if (vertice->getId() == v2) {
            tempo2 = vertice;
        }
        if (tempo1 != nullptr && tempo2 != nullptr) {
            break;
        }
    }
    if (tempo1 != nullptr && tempo2 != nullptr) {
        return tempo1->retornarCosto(tempo2);
    } else {
        throw runtime_error("No se encontraron los vertices indicados.");
    }
}

bool Grafo::MarcadoVertice(int v) {
    Vertice* tempo1 = nullptr;
    for (Vertice* vertice : vertices) {
        if (vertice->getId() == v) {
            tempo1 = vertice;
            return tempo1->getmarcado();
        }
    }
    throw runtime_error("Vertice no encontrado");
}

void Grafo::DesmarcarGrafo() {
    for (Vertice* vertice: this->vertices) {
        vertice->desmarcar();
    }
}

void Grafo::DesmarcarVertice(int v) {
    for (Vertice* vertice: vertices) {
        if (vertice->getId() == v) {
            vertice->desmarcar();
            return; 
        }
    }
    
    throw runtime_error("Vertice no encontrado");
}

void Grafo::MarcarVertice(int v) {
    for (Vertice* vertice: vertices) {
        if (vertice->getId() == v) {
            vertice->marcar();
            return; 
        }
    }
    
    throw runtime_error("Vertice no encontrado");
}

list<Elemento*> Grafo::getVertices() {
    list<Elemento*> elemVertices;
    for (Vertice* v: this->vertices) {
        elemVertices.push_back(v->getElemento());
    }
    return elemVertices;
}

list<int> Grafo::sucesores(int v) {
    for (Vertice* vertice: vertices) {
        if (vertice->getId() == v) {
            return vertice->getAdyacentes();
        }
    }
    throw runtime_error("El vertice no existe en el grafo.");
}