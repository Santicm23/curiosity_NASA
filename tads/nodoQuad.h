
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
        
        //* verificar que el nodo no tena hijos
        bool esHoja();
        
        //* insertar un elemento en la posición correspondiente
        bool insertar(Elemento& val);
        
        //* imprimir el arbol formado por los nodos en pre orden
        void preOrden();
        
        //* imprimir el arbol formado por los nodos en in orden
        void inOrden();
        
        //* imprimir el arbol formado por los nodos en pos orden
        void posOrden();
        
        //* imprimir el arbol formado por los nodos en nivel orden
        void nivelOrden();
        
        //* obtener la lista de los elementos que se encuentren en un cuadrante dado
        list<Elemento> en_cuadrante(pair<float, float> min, pair<float, float> max);
};


#include "nodoQuad.cxx"


#endif