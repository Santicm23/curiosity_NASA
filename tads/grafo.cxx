#include "grafo.h"

using namespace std;


Grafo::Grafo() {}

Vertice Grafo::InfoVertice(int v) {
    for (Vertice& vertice : vertices) {
        if (vertice.getId() == v) {
            return vertice;
        }
    }
    throw std::runtime_error("El vértice no existe en el grafo.");
}

void Grafo::InsVertice(Vertice v) {
    int k = vertices.rbegin()->getId();
    vertices.push_back(v);
    vertices.rbegin()->setId(k + 1);
}

void Grafo::InsArco(int v1, int v2, float c) {
    Vertice* tempo1 = nullptr;
    Vertice* tempo2 = nullptr;
    for (Vertice& vertice : vertices) {
        if (vertice.getId() == v1) {
            tempo1 = &vertice;
        }
        if (vertice.getId() == v2) {
            tempo2 = &vertice;
        }
        if (tempo1 != nullptr && tempo2 != nullptr) {
            break;
        }
    }
    if (tempo1 != nullptr && tempo2 != nullptr) {
        tempo1->insertarArista(c,*tempo2);
    } else {
        throw std::runtime_error("No se encontraron los vértices indicados.");
    }
}

void Grafo::ElimArco(int v1, int v2) {
    Vertice* tempo1 = nullptr;
    Vertice* tempo2 = nullptr;
    for (Vertice& vertice : vertices) {
        if (vertice.getId() == v1) {
            tempo1 = &vertice;
        }
        if (vertice.getId() == v2) {
            tempo2 = &vertice;
        }
        if (tempo1 != nullptr && tempo2 != nullptr) {
            break;
        }
    }
    if (tempo1 != nullptr && tempo2 != nullptr) {
        tempo1->eliminarArista(*tempo2);
        tempo2->eliminarArista(*tempo1);
    } else {
        throw std::runtime_error("No se encontraron los vértices indicados.");
    }
}

int Grafo::OrdenGrafo() const {
    return vertices.size();
}

int Grafo::CostoArco(int v1, int v2) {
    Vertice* tempo1 = nullptr;
    Vertice* tempo2 = nullptr;
    for (Vertice& vertice : vertices) {
        if (vertice.getId() == v1) {
            tempo1 = &vertice;
        }
        if (vertice.getId() == v2) {
            tempo2 = &vertice;
        }
        if (tempo1 != nullptr && tempo2 != nullptr) {
            break;
        }
    }
    if (tempo1 != nullptr && tempo2 != nullptr) {
        return tempo1->retornarCosto(*tempo2);
    } else {
        throw std::runtime_error("No se encontraron los vértices indicados.");
    }
}

bool Grafo::MarcadoVertice(int v)
{
    Vertice* tempo1 = nullptr;
    for (Vertice& vertice : vertices) {
        if (vertice.getId() == v) {
            tempo1 = &vertice;
            return tempo1->getmarcado();
        }
    }
    throw std::runtime_error("Vertice no encontrado");
}
 void Grafo::DesmarcarGrafo()
 {
    for(Vertice& vertice:vertices)
    {
        vertice.desmarcar();
    }
 }

 void Grafo::DesmarcarVertice(int v)
{
    for (Vertice& vertice : vertices) {
        if (vertice.getId() == v) {
            vertice.desmarcar();
            return; 
        }
    }
    
    throw std::runtime_error("Vertice no encontrado");
}

void Grafo::MarcarVertice(int v)
{
    for (Vertice& vertice : vertices) {
        if (vertice.getId() == v) {
            vertice.marcar();
            return; 
        }
    }
    
    throw std::runtime_error("Vertice no encontrado");
}

list<Vertice> Grafo::getvertices() 
{
    return vertices;
}

 void Grafo::ElimVertice(int v)
{
    for (auto it = vertices.begin(); it != vertices.end(); ++it) {
        if (it->getId() == v) {
            Vertice vertice = *it; 
            it = vertices.erase(it); 
            for (Vertice& v : vertices) { 
                v.eliminarVertice(vertice); 
            }
            return;
        }
    }
    throw std::runtime_error("Vertice no encontrado");
}

std::list<int> Grafo::sucesores(int v1) 
{
    for (Vertice& vertice : vertices) {
        if (vertice.getId() == v1) {
            return vertice.getAdyacentes();
        }
    }
    return std::list<int>();
    throw std::runtime_error("Vertice no encontrado");
}