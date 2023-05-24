
#include <fstream>
#include <iostream>
#include <utility>
#include <list>
#include <map>
#include <string>
#include <sstream>
#include <vector>

#include "tads/sistema.h"

using namespace std;


//! ----- componente 1 -----

//* Comando: cargar_comandos nombre_archivo
void cargar_comandos(Sistema& sistema, vector<string> args) {
    if (args.size() != 1)
        throw runtime_error("Debe ingresar un nombre de archivo.");
    
    string extension = sistema.obtenerExtension(args[0]);

    if (extension != "txt" && extension != "csv")
        throw runtime_error("La extension es invalida. (txt o csv)");

    ifstream fs;
    string linea;
    
    fs.open(args[0]);

    if (!fs.is_open())
        throw runtime_error("'" + args[0] + "' no se encuentra o no puede leerse.");

    if (fs.peek() == EOF)
        throw runtime_error("'" + args[0] + "' no contiene comandos.");

    sistema.borrar_desplazamientos();

    int n;
    for (n = 0; !fs.eof(); n++) {
        getline(fs, linea);
        sistema.agregar_desplazamiento(linea);
        
    }
    cout << n << " comandos cargados desde '" << args[0] << "'\n";

    fs.close();
}

//* Comando: cargar_elementos nombre_archivo
void cargar_elementos(Sistema& sistema, vector<string> args) {
    if (args.size() != 1)
        throw runtime_error("Debe ingresar un nombre de archivo.");
    
    string extension = sistema.obtenerExtension(args[0]);
    
    if (extension != "txt" && extension != "csv")
        throw runtime_error("La extension es invalida. (txt o csv)");

    ifstream fs;
    string linea;
    
    fs.open(args[0]);

    if (!fs.is_open())
        throw runtime_error("'" + args[0] + "' no se encuentra o no puede leerse.");

    if (fs.peek() == EOF)
        throw runtime_error("'" + args[0] + "' no contiene elementos.");
    
    sistema.borrar_elementos();

    int n;
    for (n = 0; !fs.eof(); n++) {
        getline(fs, linea);
        sistema.agregar_elemento(linea);
    }
    cout << n << " elementos cargados desde '" << args[0] << "'\n";

    fs.close();
}

//* Comando: agregar_movimiento tipo_mov magnitud unidad_med
void agregar_movimiento(Sistema& sistema, vector<string> args) {
    // Se verifica la cantidad de argumentos y que corresponda con lo solicitado
    Movimiento::verificarDatos(args);

    sistema.agregar_desplazamiento(new Movimiento(args[0], stof(args[1]), args[2]));
    cout << "El movimiento fue agregado exitosamente" << endl;
}

//* Comando: agregar_analisis tipo_analisis objeto comentario(opcional)
void agregar_analisis(Sistema& sistema, vector<string> args) {
    // Se verifica la cantidad de argumentos y que corresponda con lo solicitado
    Analisis::verificarDatos(args);

    string comment = args[2];
    for (int i=3; i<args.size(); i++) {
        comment += " " + args[i];
    }

    Analisis* a;

    if (args.size() == 2){    
        a = new Analisis(args[0], args[1]);
    } else {
        a = new Analisis(args[0], args[1], comment);
    }
    sistema.agregar_desplazamiento(a);
    cout << "El analisis ha sido agregado exitosamente" << endl;
}

//* Comando: agregar_elementos tipo_comp tamano unidad_med coordX coordY
void agregar_elementos(Sistema& sistema, vector<string> args) {
    // Se verifica la cantidad de argumentos y que corresponda con lo solicitado
    Elemento::verificarDatos(args);

    sistema.agregar_elemento(new Elemento(args[0], stof(args[1]), args[2], stof(args[3]), stof(args[4])));
    cout<<"El elemento ha sido agregado exitosamente\n";
}

//* Comando: guardar tipo_archivo nombre_archivo
void guardar(Sistema& sistema, vector<string> args) {
    if (args.size() != 2)
        throw runtime_error("Se requiere el tipo de archivo y el nombre de archivo");

    string extension = sistema.obtenerExtension(args[1]);
    
    if (extension != "txt" && extension != "csv")
        throw runtime_error("La extension es invalida. (txt o csv)");
        
    // Guardo todos los elementos de la lista de desplazamientos y de elementos
    if(args[0]=="comandos") {
        if (sistema.getDesplazamientos().empty())
            throw runtime_error("La informacion requerida no esta almacenada en memoria");
        
        ofstream archivo(args[1]);
        if(!archivo.is_open())
            throw runtime_error("'" + args[1] + "' no se encuentra o no puede leerse.");
        
        for (Desplazamiento* despla: sistema.getDesplazamientos()) {
            archivo << despla->toString(',') << endl;
        }
    } else if(args[0]=="elementos") {
        if (sistema.getElementos().empty())
            throw runtime_error("La informacion requerida no esta almacenada en memoria");
        
        ofstream archivo(args[1]);
        if(!archivo.is_open())
            throw runtime_error("'" + args[1] + "' no se encuentra o no puede leerse.");

        for (Elemento* element: sistema.getElementos()) {
            archivo << element->toString(',') << endl;
        }
    } else {
        throw runtime_error("El tipo de archivo solo puede ser 'comandos' o 'elementos'");
    }

    cout << "La informacion de tipo '" << args[0] << "' ha sido guardada en '" << args[1] << "'\n";
    
}

//* Comando: simular_comandos coordX coordY
void simular_comandos(Sistema& sistema, vector<string> args) {
    if (args.size() != 2)
        throw runtime_error("Se requieren los parametros coordX y coordY");

    if (sistema.getDesplazamientos().empty())
        throw runtime_error("La informacion requerida no esta almacenada en memoria");
    
    float x, y;

    try {
        x = stof(args[0]);
        y = stof(args[1]); 
    } catch(const invalid_argument& e) {
        throw runtime_error("Los argumentos coordX y coordY deben ser de tipo flotante");
    }

    sistema.getRobot().setData(x, y, 0);

    for (Desplazamiento* despla: sistema.getDesplazamientos()) {
        Movimiento* tmp = dynamic_cast<Movimiento*>(despla);
        if (tmp != nullptr) {
            tmp->ejecutar(sistema.getRobot());
        }
    }

    cout << "La simulacion de los comandos, a partir de la posicion (" << x << ", " << y << "), "
        "deja al robot en la nueva posicion (" << sistema.getRobot().getX() << ", " << sistema.getRobot().getY() << ").\n";
}

//* Comando: salir
void salir(Sistema& sistema, vector<string> args) {
    if (args.size() != 0)
        throw runtime_error("No se requieren argumentos");
    sistema.salir();
    cout << "Fin del programa\n";
}


//! ----- componente 2 -----

//* Comando: ubicar_elementos
void ubicar_elementos(Sistema& sistema, vector<string> args) {
    if (args.size() != 0)
        throw runtime_error("No se requieren argumentos");

    if (sistema.getElementos().empty())
        throw runtime_error("La informacion requerida no esta almacenada en memoria.");
    
    sistema.borrar_arbol();
    
    for (Elemento* elem: sistema.getElementos()) {
        sistema.getArbolElementos().insertar(*elem);
    }

    cout << "Los elementos han sido procesados exitosamente.\n";
}

//* Comando: en_cuadrante coordX1 coordX2 coordY1 coordY2
void en_cuadrante(Sistema& sistema, vector<string> args) {
    if (args.size() != 4)
        throw runtime_error (
            "La informacion del cuadrante no corresponde a los datos esperados (x_min, x_max, y_min, y_max)."
        );

    float x1, x2, y1, y2;

    try {
        x1 = stof(args[0]);
        x2 = stof(args[1]);
        y1 = stof(args[2]);
        y2 = stof(args[3]);
    } catch (const invalid_argument& e) {
        throw runtime_error("Las coordenadas deben corresponder a numeros flotantes");
    }

    if (x2 < x1 || y2 < y1)
        throw runtime_error (
            "La informacion del cuadrante no corresponde a los datos esperados (x_min, x_max, y_min, y_max)."
        );  
    
    if (sistema.getArbolElementos().esVacio())
        throw runtime_error("Los elementos no han sido ubicados todavia (con el comando ubicar_elementos).");

    list<Elemento> l;
    
    l = sistema.getArbolElementos().en_cuadrante(make_pair(x1, y1), make_pair(x2, y2));
    
    if (l.empty()) {
        cout << "No hay elementos ubicados en el cuadrante solicitado\n";
    } else {
        cout << "Los elementos ubicados en el cuadrante solicitado son:\n";
        for (Elemento elem : l) {
            cout << elem.toString() << endl;
        }
    }

}


//! ----- componente 3 -----

//* Comando: crear_mapa coeficiente_conectividad
void crear_mapa(Sistema& sistema, vector<string> args) {
    if (args.size() != 1)
        throw runtime_error("Se requiere el coeficiente conectividad");

    if (sistema.getElementos().empty())
        throw runtime_error("La informacion requerida no esta almacenada en memoria.");

    float coef;

    try {
        coef = stof(args[0]);
    } catch (const invalid_argument& e) {
        throw runtime_error("El coeficiente de conectividad debe ser un numero flotante");
    }

    if (coef < 0 || coef > 1)
        throw runtime_error("El coeficiente de conectividad debe tener un valor entre 0 y 1");
    
    sistema.borrar_mapa();

    int vecinos = round(coef * sistema.getElementos().size());

    if (vecinos == sistema.getElementos().size())
        vecinos--; //? no puede tenerse a si mismo como arista (1 arista menos del total como maximo)

    for (Elemento* el: sistema.getElementos()) {
        if (!sistema.getMapa().existeVertice(el)) {
            sistema.getMapa().InsVertice(el);
        }
    }
    
    for (Elemento* el: sistema.getElementos()) {
        int v1 = sistema.getMapa().idVertice(el);

        for (pair<Elemento*, float> p: sistema.elementos_cercanos(el, vecinos)) {
            int v2 = sistema.getMapa().idVertice(p.first);

            sistema.getMapa().InsArco(v1, v2, p.second);
        }
    }

    cout << "El mapa se ha generado exitosamente. Cada elemento tiene " << vecinos << " vecinos.\n";

    // for (Elemento* e: sistema.getMapa().getVertices()) {
    //     int id = sistema.getMapa().idVertice(e);
    //     cout << id;
    //     cout << " -> { ";
    //     for (int id_tmp: sistema.getMapa().sucesores(id)) {
    //         cout << "(" << sistema.getMapa().CostoArco(id, id_tmp) << "," << id_tmp << "); ";
    //     }
    //     cout << "}\n";
    // }
}


//* Comando: ruta_mas_larga
void ruta_mas_larga(Sistema& sistema, vector<string> args) {
    if (args.size() != 0)
        throw runtime_error("No se requieren argumentos");

    else if (sistema.getMapa().getVertices().empty())
        throw runtime_error("El mapa no ha sido generado todavía (con el comando crear_mapa))");    
    
    //1) Realizar algoritmo de Floyd-Warshall, cambiando las condiciones de menor por mayor
    //2) Buscar dentro de la matriz final el mayor valor y determinar los dos vertices que lo generan
    //3) Reconstruír la ruta a través de las matrices de predecesores, mientras se suma la longitud de los arcos
    //4) Imprimir todos los valores hallados, a su vez que la lista
    
    //Realizar algoritmo de Floyd-Warshall, cambiando las condiciones de menor por mayor

    int n = sistema.getMapa().getVertices().size(); //Cantidad de nodos del grafo

    float ***D = new float**[n + 1];
    for (int i = 0; i <= n; i++) {
        D[i] = new float*[n];
        for (int j = 0; j < n; j++) {
            D[i][j] = new float[n];
        }
    }

    for (int i = 0; i < n; i++) { //Llenar D(0) con la definición matemática (matriz de adyacencia)
        for (int j = 0; j < n; j++) {
            if (i == j)
                D[0][i][j] = 0;
            else
                D[0][i][j] = sistema.getMapa().CostoArco(i, j); 
                /*Se puede dentro de un solo condicional, puesto que si no existe el arco, automáticamente se asignará un -1,
                que dado el contexto del problema, es un valor que no se puede dar como costo de un arco*/
        }
    }

    int ***P = new int**[n + 1]; //Arreglo de n matrices n x n (en Floyd-Warsahll es la matriz de nodos anteriores)
    for (int i = 0; i <= n; i++) {
        P[i] = new int*[n];
        for (int j = 0; j < n; j++) {
            P[i][j] = new int[n];
        }
    }

    for (int i = 0; i < n; i++) { //Llenar P(0) con la definición matemática
        for (int j = 0; j < n; j++) {
            if (i == j || sistema.getMapa().CostoArco(i, j) == -1)
                P[0][i][j] = -1; //En vez de null, se utiliza -1 ya que por definición no puede haber un vertice previo -1
            else if (i != j && sistema.getMapa().CostoArco(i, j) >= 0)
                P[0][i][j] = i;
        }
    }

    for (int k = 1; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {         
                D[k][i][j] = sistema.dist(k, i, j);
                if ((D[k-1][i][k] + D[k-1][k][j]) >= D[k-1][i][j])
                    P[k][i][j] = P[k-1][k][j]; //Si el camino con k es mayor, asignarlo a la lista de predecesores
                else 
                    P[k][i][j] = P[k-1][i][j];
            }
        }
    }

    //Buscar dentro de la matriz final el mayor valor y determinar los dos vertices que lo generan

    float max = 0;
    int vInicial = 0, vFinal = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (D[n][i][j] > max)
                max = D[n][i][j];
                vInicial = i;
                vFinal = j;
        }
    }

    //Reconstruír la ruta a través de las matrices de predecesores, mientras se suma la longitud de los arcos

    queue<int> ruta;
    float longitud = 0;
    ruta.push(vFinal);
    while (P[n][vInicial][vFinal] != vInicial) {
        ruta.push(P[n][vInicial][vFinal]);
        longitud += sistema.getMapa().CostoArco(P[n][vInicial][vFinal], vFinal);
        vFinal = P[n][vInicial][vFinal];
    }
    ruta.push(vInicial);
    longitud += sistema.getMapa().CostoArco(vInicial, vFinal);

    //Imprimir todos los valores hallados, a su vez que la lista

    cout << "Los puntos de interés más alejados entre sí son: " << vInicial << " y " << vFinal << endl;
    cout << "La ruta que los conecta tiene una longitud total de " << longitud << " y pasa por los siguientes elementos: ";
    int i = 1;
    while (!ruta.empty()) {
        Elemento* elem = sistema.getMapa().InfoVertice(ruta.front());
        cout << "Elemento " << i << ")\tTipo: " << elem->getTipoElemento() << "\tPosicion: (" << elem->getCoordenadaX() << ", " << elem->getCoordenadaY() << ")" << endl;
        ruta.pop();
        i++;
    }

    for (int i = 0; i < n+1; i++) {
        for (int j = 0; j < n; j++) {
            delete[] D[i][j];
            delete[] P[i][j];
        }
        delete[] D[i];
        delete[] P[i];
    }
    delete[] D;
    delete[] P;
}

//! ----- comandos y funciones adicionales -----

//* Comando: ayuda nombre_comando(opcional)
void ayuda(Sistema& sistema, vector<string> args) {
    if (args.empty()){
        for (pair<const string,ComandoSistema<Sistema>> tupla: sistema.getComandos()) {
            cout << "\t" << tupla.first << endl;
        }
    } else if (args.size() == 1) {
        if (sistema.comando_existe(args[0])) {
            cout << "\t" << sistema.getComandos()[args[0]].getDescripcion() << endl;
        } else {
            throw runtime_error("No se encontro el comando '" + args[0] + "'");
        }
    } else {
        throw runtime_error("El comando 'ayuda' recibe maximo un argumento");
    }
}

// inicializar los maps donde se guarda la descripcion y la funcion correspondiente a cada comando
void llenarComandosSistema(Sistema& sistema) {
    // comando name, comando description
    // comando name, comando callback function

    sistema.agregar_comando(
        "cargar_comandos",
        "Comando: cargar_comandos nombre_archivo\n"
        "Carga en memoria los comandos de desplazamiento contenidos en el archivo identificado por nombre_archivo, "
        "es decir, utiliza adecuadamente las estructuras lineales para cargar la informacion de los comandos en memoria. "
        "Si dentro de la misma sesion de trabajo ya se han cargado otros archivos de comandos (usando el comando "
        "cargar_comandos), la informacion debe sobreescribirse en memoria, es decir, no se deben combinar informaciones "
        "de comandos de diferentes archivos.",
        cargar_comandos
    );

    sistema.agregar_comando(
        "cargar_elementos",
        "Comando: cargar_elementos nombre_archivo\n"
        "Carga en memoria los comandos de desplazamiento contenidos en el archivo identificado por nombre_archivo, "
        "es decir, utiliza adecuadamente las estructuras lineales para cargar la informacion de los comandos "
        "en memoria. Si dentro de la misma sesion de trabajo ya se han cargado otros archivos de comandos "
        "(usando el comando cargar_comandos), la informacion debe sobreescribirse en memoria, es decir, no se "
        "deben combinar informaciones de comandos de diferentes archivos.",
        cargar_elementos
    );
    
    sistema.agregar_comando(
        "agregar_movimiento",
        "Comando: agregar_movimiento tipo_mov magnitud unidad_med\n"
        "Agrega el comando de movimiento descrito a la lista de comandos del robot \"Curiosity\". El movimiento puede "
        "ser de dos tipos: avanzar o girar. La magnitud corresponde al valor del movimiento; si es avanzar, el numero "
        "de unidades que se espera avanzar, si es girar la cantidad de grados que debe girar. La unidad de medida "
        "corresponde a la convencion con la que se mide la magnitud del movimiento (centimetros, metros, grados, ...). "
        "Si no se envia la informacion completa y adecuada del comando de movimiento, este no puede agregarse a la "
        "lista de los comandos que se enviaran al robot desde la tierra.",
        agregar_movimiento
    );

    sistema.agregar_comando(
        "agregar_analisis",
        "Comando: agregar_analisis tipo_analisis objeto comentario(opcional) "
        "Agrega el comando de analisis descrito a la lista de comandos del robot \"Curiosity\". El analisis puede "
        "ser de tres tipos: fotografiar, composicion o perforar. El objeto es el nombre del elemento que se quiere "
        "analizar (roca, arena, monticulo, ...). El comentario es opcional y permite agregar mas informacion sobre "
        "el elemento o el analisis, este comentario estara encerrado entre comillas simples (ejemplo: 'roca_cuadrante_32'). "
        "Si no se envia la informacion completa y adecuada del comando de analisis, este no puede agregarse a la lista "
        "de los comandos que se enviaran al robot desde la tierra.",
        agregar_analisis
    );

    sistema.agregar_comando(
        "agregar_elementos",
        "Comando: agregar_elementos tipo_comp tamano unidad_med coordX coordY\n"
        "Agrega el componente o elemento descrito a la lista de puntos de interes del robot \"Curiosity\". El tipo "
        "de componente puede ser uno entre roca, crater, monticulo o duna. El tamano es un valor real que da "
        "cuenta de que tan grande es el elemento; y la unidad de medida complementa este valor con la convencion "
        "que se uso para su medicion (centimetros, metros, ...). Finalmente, las coordenadas x y y corresponden "
        "a numeros reales que permiten conocer la ubicacion del elemento en el sistema de coordenadas del suelo "
        "marciano utilizado por el vehiculo. Si no se envia la informacion completa y adecuada del elemento, "
        "este no puede agregarse a la lista de puntos de interes que se enviaran al robot desde la tierra.",
        agregar_elementos
    );
    
    sistema.agregar_comando(
        "guardar",
        "Comando: guardar tipo_archivo nombre_archivo\n"
        "Guarda en el archivo nombre_archivo la informacion solicitada de acuerdo al tipo de archivo: 'comandos' "
        "almacena en el archivo la informacion de comandos de movimiento y de analisis que debe ejecutar el robot, "
        "'elementos' almacena en el archivo la informacion de los componentes o puntos e interes conocidos en el suelo "
        "marciano.",
        guardar
    );

    sistema.agregar_comando(
        "simular_comandos",
        "Comando: simular_comandos coordX coordY\n"
        "Permite simular el resultado de los comandos de movimiento que se enviaran al robot \"Curiosity\" desde "
        "la Tierra, facilitando asi la validacion de la nueva posicion en la que podria ubicarse. Para ejecutarse "
        "adecuadamente, requiere conocer la posicion actual (coordenadas x y y) del vehiculo. Hay que tener en cuenta "
        "que solo los comandos de movimiento son necesarios, no los de analisis.",
        simular_comandos
    );

    sistema.agregar_comando(
        "salir",
        "Comando: salir\n"
        "Termina la ejecucion de la aplicacion.",
        salir
    );

    sistema.agregar_comando(
        "ubicar_elementos",
        "Comando: ubicar_elementos\n"
        "El comando debe utilizar la informacion de puntos de interes almacenada en memoria para ubicarlos en "
        "una estructura de datos jerarquica adecuada, que permita luego realizar consultas geograficas sobre estos "
        "elementos. Si alguno de los elementos no puede agregarse adecuadamente, debe generarse un mensaje de error, "
        "pero deben terminarse de procesar todos los elementos almacenados en memoria.",
        ubicar_elementos
    );
    
    sistema.agregar_comando(
        "crear_mapa",
        "Comando: crear_mapa coeficiente_conectividad\n"
        "El comando debe utilizar la informacion de puntos de interes almacenada en memoria para ubicarlos en una "
        "estructura no lineal y conectarlos entre si teniendo en cuenta el coeficiente de conectividad dado. El "
        "objetivo es que cada elemento este conectado a los demas elementos mas cercanos a el, midiendo la cercania "
        "a traves de la distancia euclidiana entre los elementos. Esta distancia euclidiana tambien se utiliza como "
        "el peso o etiqueta de la conexion entre los elementos. Con el coeficiente de conectividad se identifica la "
        "cantidad de vecinos que puede tener cada elemento tomando como base el total de elementos que se ubicaran "
        "en el mapa (ejemplo: si se van a ubicar 35 elementos, y el coeficiente de conectividad es 0.4, la cantidad "
        "de vecinos que cada elemento debe tener es 35 * 0.4 = 14).",
        crear_mapa
    );
    
    sistema.agregar_comando(
        "en_cuadrante",
        "Comando: en_cuadrante coordX1 coordX2 coordY1 coordY2\n"
        "Permite utilizar la estructura creada con el comando anterior para retornar una lista de "
        "los componentes o elementos que estan dentro del cuadrante geografico descrito por los limites de coordenadas "
        "en x y y. Es necesario haber ejecutado el comando ubicar_elementos para poder realizar "
        "la busqueda por cuadrantes. Los limites de coordenadas deben garantizar que coordX1 < coordX2 y "
        "coordY1 < coordY2.",
        en_cuadrante
    );
    
    sistema.agregar_comando(
        "ruta_mas_larga",
        "Comando: ruta_mas_larga\n"
        "Con el mapa ya creado, el comando permite identificar los dos componentes mas alejados entre si de acuerdo "
        "a las conexiones generadas. Es importante aclarar que el comando retorna los elementos mas alejados de "
        "acuerdo a las conexiones que se encuentran en el mapa, no los elementos que esten a mayor distancia "
        "euclidiana entre si. Al encontrar esa ruta mas larga dentro del mapa, el comando imprime en pantalla los "
        "elementos de origen y destino, la longitud total de la ruta, y la secuencia de elementos que hay que seguir "
        "para ir del elemento origen al elemento destino.",
        ruta_mas_larga
    );

    sistema.agregar_comando(
        "ayuda",
        "Comando: ayuda nombre_comando(opcional)\n"
        "Permite la visualizacion de la descripcion de cada uno de los comandos.",
        ayuda
    );
}


//! ----- main -----

int main() {
    char delim = ' ';
    string lineaComando, comando, palabra;

    Sistema sistema;
    llenarComandosSistema(sistema);

    cout << " --- Curiosity --- \n";

    do {
        // vector de argumentos del comando ingresado
        vector<string> args;

        cout << "$ ";
        getline(cin, lineaComando);


        stringstream stream(lineaComando);
        getline(stream, comando, delim);

        while (getline(stream, palabra, delim))
            args.push_back(palabra);

        try {
            if (lineaComando == "")
                continue;
            sistema.ejecutar(comando, args);
        } catch (const runtime_error& e) {
            cerr << "Error: " << e.what() << '\n';
        }

    } while (comando!="salir");
}