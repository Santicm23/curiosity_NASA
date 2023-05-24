
#ifndef SISTEMA
#define SISTEMA


#include <string>
#include <list>
#include <vector>
#include <stack>
#include <map>

#include "desplazamiento.h"
#include "movimiento.h"
#include "analisis.h"
#include "elemento.h"
#include "comandoSistema.h"
#include "robotCuriosity.h"
#include "arbolQuad.h"
#include "grafo.h"

using namespace std;


//! ----- TAD Sistema ----- 

class Sistema {

    using funcion = function<void(Sistema&,vector<string>)>;

    private:
        map<string,ComandoSistema<Sistema>> comandos; //* map que contiene los comando del sistema
        list<Desplazamiento*> desplazamientos; //* lista que contiene los comandos de desplazamiento
        list<Elemento*> elementos; //* lista que contiene los elementos de interés
        ArbolQuad arbolElementos; //* QuadTree que almacena los elementos de interés en un plano cartesiano
        Grafo mapa; //* Mapa de conexión entre elementos de interés con un coeficiente de conectividad dado
        RobotCuriosity robot; //* robot de la nasa
        
    public:
        Sistema();

        Sistema(const Sistema& sistema);

        map<string,ComandoSistema<Sistema>>& getComandos();

        list<Desplazamiento*>& getDesplazamientos();

        list<Elemento*>& getElementos();

        ArbolQuad& getArbolElementos();

        RobotCuriosity& getRobot();

        Grafo& getMapa();

        //* obtener la extension de un nombre de archivo dado
        static string obtenerExtension(string nombreArchivo);

        //* agregar un comando del sistema
        void agregar_comando(string nombre, string desc, funcion func);
        
        //* cargar un comando de desplazamiento en el sistema
        void agregar_desplazamiento(Desplazamiento* desp);
        
        //* cargar un comando de desplazamiento en el sistema a partir de un string
        void agregar_desplazamiento(string linea, char delim = ',');
        
        //* cargar un elemento en el sistema
        void agregar_elemento(Elemento* elem);

        //* cargar un elemento en el sistema a partir de una string
        void agregar_elemento(string linea, char delim = ',');

        //* obtener los n elementos mas cercanos al elemento dado
        list<pair<Elemento*, float>> elementos_cercanos(Elemento* elem, int n);

        //* función distancia mayor para Floyd-Warshall (función ruta_más_larga)
        float dist(int k, int i, int j);
        
        void floydWarshall(vector<vector<int>>& matrizPredecesores, vector<vector<float>>& matrizPesos) {
            int V = matrizPredecesores.size();

            // Iteramos sobre todos los vértices y calculamos las distancias más altas
            for (int k = 0; k < V; ++k) {
                for (int i = 0; i < V; ++i) {
                    for (int j = 0; j < V; ++j) {
                        // Si el vértice k aumenta la distancia entre i y j, lo actualizamos
                        if (matrizPesos[i][k] != -1 && matrizPesos[k][j] != -1 && matrizPesos[i][k] + matrizPesos[k][j] > matrizPesos[i][j] && matrizPesos[i][j] != 0) {
                            matrizPesos[i][j] = matrizPesos[i][k] + matrizPesos[k][j];
                            matrizPredecesores[i][j] = k+1;
                        }
                    }
                }
            }
        }

        pair<list<int>, float> obtenerRutaMasLarga(vector<vector<int>>& matrizPredecesores, vector<vector<float>>& matrizPesos) {
            int V = matrizPesos.size();

            // Obtener índices de la ruta más larga
            list<int> rutaMasLarga;
            int indiceOrigen = -1;
            int indiceDestino = -1;
            float distanciaMaxima = 0.0;

            // Encontrar el par de vértices con la distancia más larga
            for (int i = 0; i < V; ++i) {
                for (int j = 0; j < V; ++j) {
                    if (matrizPesos[i][j] != -1 && matrizPesos[i][j] > distanciaMaxima) {
                        distanciaMaxima = matrizPesos[i][j];
                        indiceOrigen = i;
                        indiceDestino = j;
                    }
                }
            }

            if (indiceOrigen != -1 && indiceDestino != -1) {
                list<int> ruta;
    
                ruta.push_front(indiceDestino);

                // while (indiceOrigen != indiceDestino) {
                //     //OJO CON LOS -1
                //     indiceDestino = matrizPredecesores[indiceOrigen - 1][indiceOrigen - 1];
                //     ruta.push_front(indiceDestino);
                // }
            }
            return make_pair(rutaMasLarga, distanciaMaxima);
        }

        //* borrar los desplazamientos cargados en el sistema
        void borrar_desplazamientos();

        //* borrar los elementos cargados en el sistema
        void borrar_elementos();

        void borrar_arbol();

        void borrar_mapa();

        //* verificar que un comando existe
        bool comando_existe(string nombre);

        //* ejecutar un comando
        void ejecutar(string comando, vector<string> args);
        
        //* salir del sistema
        void salir();
};

#include "sistema.cxx"

#endif