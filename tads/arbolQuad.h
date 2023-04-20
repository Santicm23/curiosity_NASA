
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
        
        ArbolQuad(Elemento& val);
        
        ~ArbolQuad();
        
        Elemento& datoRaiz();
        
        NodoQuad* obtenerRaiz();

        void fijarRaiz(NodoQuad* n_raiz);
        
        //* verificar que el arbol este vacio
        bool esVacio();
        
        //* verificar que el arbol no tenga hijos
        bool esHoja();
        
        //* insertar un elemento en la posición correspondiente
        bool insertar(Elemento& val);
        
        //* imprimir el arbol en pre orden
        void preOrden();
        
        //* imprimir el arbol en in orden
        void inOrden();
        
        //* imprimir el arbol en pos orden
        void posOrden();
        
        //* imprimir el arbol en nivel orden
        void nivelOrden();
        
        //* obtener la lista de los elementos que se encuentren en un cuadrante dado
        list<Elemento> en_cuadrante(pair<float, float> min, pair<float, float> max);
};


#include "arbolQuad.cxx"


#endif