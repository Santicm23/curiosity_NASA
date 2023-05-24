
#ifndef GRAFO
#define GRAFO

#include <utility>
#include <list>
#include <set>

#include "vertice.h"

using namespace std;


class Grafo {

    using Arista = pair<float, int>;
    
    private:
        list<Vertice> vertices; //* la posición en la lista corresponde al número de vértice.
        list<set<Arista>> aristas;
        
    public:
        Grafo();

        //* Retorna la información de Tipo T almacenada en el vértice
        Elemento* InfoVertice(int v);
        
        //* Obtener el id de un vertice dado
        int idVertice(Elemento* v);

        //* Agregar vértice v al final de la lista de vértices con Infovertice de tipo T.
        void InsVertice(Elemento* v);
        
        //* Ver si un elemento dado ya existe en  el grafo
        bool existeVertice(Elemento* v);

        //* inserta un arco con costo c entre los vértices v1 y v2
        void InsArco(int v1, int v2, float c);

        //* Elimina el arco entre los vértices v1 y v2
        void ElimArco(int v1, int v2);

        //* Marca el vértice v
        void MarcarVertice(int v);
        
        //* Desmarca el vértice v
        void DesmarcarVertice(int v);

        //* Desmarca todos los vértices del grafo
        void DesmarcarGrafo();
        
        //* Retorna true si el vértice v está marcado, false en caso contrario
        bool MarcadoVertice(int v);

        //* Retorna el número de vértices que tiene el grafo
        int OrdenGrafo() const;

        //* Retorna el costo del arco existente entre v1 y v2. Sino existe un arco entre los dos vértices retorna -1
        float CostoArco(int v1, int v2);
        
        //* Retorna una lista con los vértices del grafo. Cada ver de la lista tiene la información (tipo T) de cada vértice
        list<Elemento*> getVertices();
        
        //* Elimina el vértice v del Grafo
        // void ElimVertice(int v);

        //* Retorna la lista enteros con los sucesores del vértice v1
        list<int> sucesores(int v) ;

        //* Borra la información almacenada en el grafo
        void borrar();
};

#include "grafo.cxx"


#endif