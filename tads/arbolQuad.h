
#ifndef ARBOLQUAD
#define ARBOLQUAD

#include<iostream>


#include "nodoQuad.h"

using namespace std;


class ArbolQuad {
    protected:
        NodoQuad* raiz;
    public:
        ArbolQuad();
        ArbolQuad(punto& val);
        ~ArbolQuad();
        punto& datoRaiz();
        NodoQuad* obtenerRaiz();
        void fijarRaiz(NodoQuad* n_raiz);
        bool esVacio();
        bool esHoja();
        bool insertar(punto& val);
        void preOrden();
        void inOrden();
        void posOrden();
        void nivelOrden();
};


#include "arbolQuad.cxx"


#endif