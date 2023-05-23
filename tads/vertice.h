#ifndef VERTICE
#define VERTICE
#include "elemento.h"
#include <set>
#include <list>
using namespace std;

class Vertice
{
    using Arista = std::pair<float, Vertice>;
    private:
        Elemento elemento;
        std::set<Arista> adyacentes;
        bool marcado=false;
        int id;

    public:
        Vertice();
        Vertice(Elemento elemento,std::set<Arista> adyacentes);
        ~Vertice();
        void insertarArista(float distancia, Vertice& verticeDestino);
        float retornarCosto(Vertice& verticeDestino);
        void eliminarArista(Vertice& verticeDestino);
        int getId();
        void setId(int k);
        Elemento getElemento();
        bool getmarcado();
        void Vertice::eliminarVertice(Vertice& v);
        std::list<int> getAdyacentes();
        void marcar();
        void desmarcar();
        bool estaMarcado();
};




#endif