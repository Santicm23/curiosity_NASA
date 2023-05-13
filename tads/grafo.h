
#ifndef GRAFO
#define GRAFO

#include <list>

#include "vertice.h"

using namespace std;


class Grafo {
    
    private:
        std::list<Vertice*> vertices; //* la posición en la lista corresponde al número de vértice.

    public:
        Grafo();  //Constructor por omisión

        ~Grafo();
        //!
        Elemento* InfoVertice(int v); //Retorna la información de Tipo T almacenada en el vértice
        
        int idVertice(Elemento* v);
        //!
        void InsVertice(Elemento* v); //Agregar vértice v al final de la lista de vértices con Infovertice de tipo T.
        
        bool existeVertice(Elemento* v);
        //!
        void InsArco(int v1, int v2, float c); // inserta un arco con costo c entre los vértices v1 y v2
        //!
        void ElimArco(int v1, int v2); //Elimina el arco entre los vértices v1 y v2
        //!
        void MarcarVertice(int v);//Marca el vértice v
        //!
        void DesmarcarVertice(int v);//Desmarca el vértice v
        //!
        void DesmarcarGrafo();// desmarca todos los vértices del grafo
        //!
        bool MarcadoVertice(int v);//Retorna true si el vértice v está marcado, false en caso contrario
        //!
        int OrdenGrafo() const; // Retorna el número de vértices que tiene el grafo
        //!
        float CostoArco(int v1, int v2);//Retorna el costo del arco existente entre v1 y v2. Sino existe un arco entre los dos vértices retorna -1
        //!
        list<Elemento*> getVertices(); // Retorna una lista con los vértices del grafo. Cada ver de la lista tiene la información (tipo T) de cada vértice
        //!
        // void ElimVertice(int v);//Elimina el vértice v del Grafo
        //!
        list<int> sucesores(int v) ;// retorna la lista enteros con los sucesores del vértice v1
};

#include "grafo.cxx"


#endif