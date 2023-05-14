
#ifndef VERTICE
#define VERTICE


#include <utility>
#include <list>

#include "elemento.h"

using namespace std;


class Vertice {
    private:
        Elemento* elemento;
        bool marcado = false;

    public:
        Vertice();
        Vertice(Elemento* elemento);
        Elemento* getElemento();
        void marcar();
        void desmarcar();
        bool estaMarcado();
};

#include "vertice.cxx"


#endif