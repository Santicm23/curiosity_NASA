
#ifndef VERTICE
#define VERTICE


#include <utility>
#include <set>

#include "elemento.h"

using namespace std;


class Vertice {
    using Arista = std::pair<float, Vertice>;
    private:
        Elemento* elemento;
        std::set<Arista> adyacentes;
        bool marcado=false;
        int id;

    public:
        Vertice();
        Vertice(int id, Elemento* elemento);
        Vertice(int id, Elemento* elemento, std::set<Arista> adyacentes);
        ~Vertice();
        void insertarArista(float distancia, Vertice& verticeDestino);
        float retornarCosto(Vertice& verticeDestino);
        void eliminarArista(Vertice& verticeDestino);
        int getId();
        void setId(int k);
        Elemento* getElemento();
        bool getmarcado();
        void marcar();
        void desmarcar();
        bool estaMarcado();
};




#endif