
#ifndef NODOQUAD
#define NODOQUAD


#include<iostream>

#include "elemento.h"


using namespace std;


class NodoQuad {
    protected:
        Elemento dato;
        NodoQuad* hijoSupIzq;
        NodoQuad* hijoSupDer;
        NodoQuad* hijoInfIzq;
        NodoQuad* hijoInfDer;
    public:
        NodoQuad();
        NodoQuad(Elemento& val);
        ~NodoQuad();
        Elemento& obtenerDato();
        void fijarDato(Elemento& val);
        NodoQuad* obtenerHijoSupIzq();
        NodoQuad* obtenerHijoSupDer();
        NodoQuad* obtenerHijoInfIzq();
        NodoQuad* obtenerHijoInfDer();
        void fijarHijoSupIzq(NodoQuad* sizq);
        void fijarHijoSupDer(NodoQuad* sder);
        void fijarHijoInfIzq(NodoQuad* iizq);
        void fijarHijoInfDer(NodoQuad* ider);
        bool esHoja();
        bool insertar(Elemento& val);
        void preOrden();
        void inOrden();
        void posOrden();
        void nivelOrden();
        list<Elemento> en_cuadrante(pair<float, float> min, pair<float, float> max);
};


#include "nodoQuad.cxx"


#endif