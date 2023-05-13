
#ifndef VERTICE
#define VERTICE


#include <utility>
#include <list>

#include "elemento.h"

using namespace std;


class Vertice {
    using Arista = pair<float, Vertice*>;
    private:
        Elemento* elemento;
        list<Arista> adyacentes;
        bool marcado=false;
        int id;

    public:
        Vertice();
        Vertice(int id, Elemento* elemento);
        Vertice(int id, Elemento* elemento, list<Arista> adyacentes);
        ~Vertice();
        void insertarArista(float distancia, Vertice* verticeDestino);
        float retornarCosto(Vertice* verticeDestino);
        void eliminarArista(Vertice* verticeDestino);
        int getId();
        void setId(int k);
        Elemento* getElemento();
        bool getmarcado();
        list<int> getAdyacentes();
        void marcar();
        void desmarcar();
        bool estaMarcado();
};

#include "vertice.cxx"


#endif