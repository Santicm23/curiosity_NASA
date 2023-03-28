
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <regex>

#include "tads/sistema.h"
#include "tads/desplazamiento.h"
#include "tads/movimiento.h"
#include "tads/analisis.h"
#include "tads/elemento.h"
#include "tads/robotCuriosity.h"

using namespace std;


// ----- variables globales -----
    
// => maps de comandos de la consola:

// descripcion de cada comando
map<string, string> descComandosConsola;
// funcion de ejecucion de cada comando
map<string, void(*)(vector<string>)> comandosConsola;

// => listas de comandos del robot curiosity:

// lista de comandos de deplazamiento cargados
list<Desplazamiento*> desplazamientos;
// lista de elementos de interes cargados
list<Elemento*> elementos;

// => funciones de ayuda:

// funcion que crea y retorna un comando de desplazamiento a partir de una linea
Desplazamiento* crearDesplazamiento(string linea) {
    char delim = ' ';
    string palabra;

    stringstream ss(linea);
    vector<string> palabras;

    getline(ss, palabra, delim); 
    palabras.push_back(palabra); 

    if (palabras[0] == "avanzar" || palabras[0] == "girar") {

        while (getline(ss, palabra, delim))
            palabras.push_back(palabra);

        if (palabras.size() != 3) throw runtime_error(
            "Los comandos de movimiento requieren tipo_movimiento, magnitud y unidad_medida como argumentos");

        Movimiento::verificarDatos(palabras[0], palabras[2]);

        try {
            return new Movimiento(palabras[0], stof(palabras[1]), palabras[2]);
        } catch (const invalid_argument& e) {
            throw runtime_error("La magnitud del comando debe ser un numero flotante");
        }
        
    } else if (palabras[0] == "fotografiar" || palabras[0] == "composicion" || palabras[0] == "perforar") {
        
        getline(ss, palabra, delim);
        palabras.push_back(palabra);

        if (getline(ss, palabra))
            palabras.push_back(palabra);

        if (palabras.size() == 2) {
            return new Analisis(palabras[0], palabras[1]);
            
        } else if (palabras.size() == 3) {
            if (!regex_match(palabras[2], regex("'([a-zA_Z0-9_!.,;+/*%?¡¿@#()><= ]|-)*'"))) 
                throw runtime_error("El comentario debe estar entre comillas simples, sin acentos");
            return new Analisis(palabras[0], palabras[1], palabras[2]);

        } else throw runtime_error(
            "Los comandos de analisis requieren tipo_analisis, objeto y comentario(opcional) como argumentos");

    } else throw runtime_error("El tipo de comando no es valido");
}
// funcion que crea y retorna un elemento de interes a partir de una linea
Elemento* crearElemento(string linea) {
    char delim = ' ';
    string palabra;
    vector<string> palabras;

    stringstream ss(linea);

    while (getline(ss, palabra, delim))
        palabras.push_back(palabra);

    if (palabras.size() != 5) throw runtime_error(
        "Los comandos de movimiento requieren tipo_elemento, tamano, unidad_medida, coordenada_x, coordenada_y");
    
    if (palabras[0] != "roca" && palabras[0] != "crater" && palabras[0] != "monticulo" && palabras[0] != "duna")
        throw runtime_error("El tipo de elemento no es valido ('roca', 'crater', 'monticulo' o 'duna')");

    try {
        return new Elemento(palabras[0], stof(palabras[1]), palabras[2], stof(palabras[3]), stof(palabras[4]));
    } catch (const invalid_argument& e) {
        throw runtime_error("El tamano, y las coordenadas X y Y deben ser numeros flotantes");
    }
}
// funcion que retorna la extension de un nombre de archivo dado
string obtenerExtension(string nombreArchivo) {
    char delim = '.';
    string palabra;
    stringstream ss(nombreArchivo);
    while (getline(ss, palabra, delim)) {}
    return palabra;
}


// ----- componente 1 -----

// TODO: terminar componente para entrega 1
    // con documentacion de comandos => (diagramas, graficos, dibujos), plan de pruebas (simular_comandos)

// Comando: cargar_comandos nombre_archivo
void cargar_comandos(vector<string> args) {
    string extension = obtenerExtension(args[0]);

    if (args.size() != 1)
        throw runtime_error("Debe ingresar un nombre de archivo.");
    
    if (extension != "txt" && extension != "csv")
        throw runtime_error("La extension es invalida. (txt o csv)");

    fstream fs;
    string line;
    
    fs.open(args[0], ios::in);

    if (!fs.is_open())
        throw runtime_error("'" + args[0] + "' no se encuentra o no puede leerse.");

    if (fs.peek() == EOF)
        throw runtime_error("'" + args[0] + "' no contiene comandos.");

    desplazamientos.clear();

    int n;
    for (n = 0; !fs.eof(); n++) {
        getline(fs, line);
        desplazamientos.push_back(crearDesplazamiento(line));
    }
    cout << n << " comandos cargados cargados desde '" << args[0] << "'\n";

    fs.close();
}

// Comando: cargar_elementos nombre_archivo
void cargar_elementos(vector<string> args) {
    string extension = obtenerExtension(args[0]);

    if (args.size() != 1)
        throw runtime_error("Debe ingresar un nombre de archivo.");
    
    if (extension != "txt" && extension != "csv")
        throw runtime_error("La extension es invalida. (txt o csv)");

    fstream fs;
    string line;
    
    fs.open(args[0], ios::in);

    if (!fs.is_open())
        throw runtime_error("'" + args[0] + "' no se encuentra o no puede leerse.");

    if (fs.peek() == EOF)
        throw runtime_error("'" + args[0] + "' no contiene elementos.");
    
    int n;
    for (n = 0; !fs.eof(); n++) {
        getline(fs, line);
        elementos.push_back(crearElemento(line));
    }
    cout << n << " elementos cargados cargados desde '" << args[0] << "'\n";

    fs.close();
}

// Comando: agregar_movimiento tipo_mov magnitud unidad_med
void agregar_movimiento(vector<string> args) {
    if (args.size() != 3) //tamano de argumentos diferente
        throw runtime_error(
            "La informacion del movimiento no corresponde a los datos esperados (tipo, magnitud, unidad).");

    Movimiento::verificarDatos(args[0], args[2]); //Se usa el método implementado en Movimiento para verificar unidades de medida

    try { //Anadir movimiento
        desplazamientos.push_back(new Movimiento(args[0], stof((args[1])), args[2])); //Se envia referencia al Movimiento m, que fue previamente instanciado
        cout << "El movimiento fue agregado exitosamente!" << endl;
    } catch (const invalid_argument& e) { 
        throw runtime_error("La magnitud debe ser un numero flotante");
    }
}

// Comando: agregar_analisis tipo_analisis objeto comentario(opcional)
void agregar_analisis(vector<string> args) {
    string comment = args[2];
    for (int i=3; i<args.size(); i++) {
        comment += " " + args[i];
    }
    if (args.size() < 2) //tamano de argumentos distinto
        throw runtime_error(
            "La informacion del analisis no corresponde a los datos esperados (tipo, objeto, comentario opcional).");
    
    Analisis::verificarDatos(args[0], args[1]);

    if (args.size() == 2){    
        try { //Anadir analisis sin comentario
            desplazamientos.push_back(new Analisis(args[0], args[1], ""));
            cout<<"El analisis ha sido agregado exitosamente" << endl;
        } catch (const invalid_argument& e) {
            throw runtime_error("Error en los datos ingresados");
        }
    } else {
        if (!regex_match(comment, regex("'([a-zA_Z0-9_!.,;+/*%?¡¿@#()><= ]|-)*'")))
            throw runtime_error(
                "El comentario debe estar entre comillas simples, sin acentos");

        desplazamientos.push_back(new Analisis(args[0], args[1], comment));
        cout<<"El analisis ha sido agregado exitosamente" << endl;
    }

}

// Comando: agregar_elementos tipo_comp tamano unidad_med coordX coordY
void agregar_elementos(vector<string> args) {
    if (args.size() != 5)
        throw runtime_error(
            "La informacion del elemento no corresponde a los datos esperados (tipo, tamano, unidad, x, y)");
    
    try {
        Elemento::verificarDatos(args[0], stof(args[1]), args[2]);
        elementos.push_back(new Elemento(args[0], stof(args[1]), args[2], stof(args[3]), stof(args[4])));
        cout<<"El elemento ha sido agregado exitosamente\n";
    } catch (const invalid_argument& e) {
        throw runtime_error("El tamano, y las coordenadas X y Y deben ser numeros flotantes");
    }
}

// Comando: guardar tipo_archivo nombre_archivo
void guardar(vector<string> args) {
    string extension = obtenerExtension(args[1]);

    if (args.size() != 2)
        throw runtime_error("Se requiere el tipo de archivo y el nombre de archivo");
    
    if (extension != "txt" && extension != "csv")
        throw runtime_error("La extension es invalida. (txt o csv)");
        
    // Guardo todos los elementos de la lista de desplazamientos y de elementos
    if(args[0]=="comandos") {
        if (desplazamientos.empty())
            throw runtime_error("La informacion requerida no esta almacenada en memoria");
        
        ofstream archivo(args[1]);
        if(!archivo.is_open())
            throw runtime_error("'" + args[1] + "' no se encuentra o no puede leerse.");
        
        for (Desplazamiento* despla: desplazamientos) {
            archivo << despla->toString(',') << endl;
        }
    } else if(args[0]=="elemento") {
        if (elementos.empty())
            throw runtime_error("La informacion requerida no esta almacenada en memoria");
        
        ofstream archivo(args[1]);
        if(!archivo.is_open())
            throw runtime_error("'" + args[1] + "' no se encuentra o no puede leerse.");

        for (Elemento* element: elementos) {
            archivo << element->toString(',') << endl;
        }
    } else {
        throw runtime_error("El tipo de archivo solo puede ser desplazamiento o elemento");
    }

    cout << "La informacion de tipo "<<args[0]<<" ha sido guardada en '" << args[1] <<"'\n";
    
}

// Comando: simular_comandos coordX coordY
void simular_comandos(vector<string> args) {
    if (args.size() != 2)
        throw runtime_error("Se requieren los parametros coordX y coordY");

    if (desplazamientos.empty())
        throw runtime_error("La informacion requerida no esta almacenada en memoria");
    
    float x, y;

    try {
        x = stof(args[0]);
        y = stof(args[1]); 
    } catch(...) {
        throw runtime_error("Los argumentos coordX y coordY deben ser de tipo flotante");
    }

    RobotCuriosity robot = RobotCuriosity(x, y);

    for (Desplazamiento* despla:desplazamientos) {
        Movimiento* tmp = dynamic_cast<Movimiento*>(despla);
        if (tmp != nullptr) {
            tmp->ejecutar(robot);
        }
    }

    cout << "La simulacion de los comandos, a partir de la posicion (" << x << ", " << y << "), "
        "deja al robot en la nueva posicion (" << robot.getX() << ", " << robot.getY() << ").\n";
}

// Comando: salir
void salir(vector<string>) {
    for (Desplazamiento* desp: desplazamientos) {
        delete desp;
    }
    for (Elemento* elem: elementos) {
        delete elem;
    }
    cout << "Fin del programa\n";
}


// ----- componente 2 -----

// Comando: ubicar_elementos
void ubicar_elementos(vector<string> args) {}

// Comando: en_cuadrante coordX1 coordX2 coordY1 coordY2
void en_cuadrante(vector<string> args) {}


// ----- componente 3 -----

// Comando: crear_mapa coeficiente_conectividad
void crear_mapa(vector<string> args) {}

// Comando: ruta_mas_larga
void ruta_mas_larga(vector<string> args) {}


// ----- comandos y funciones adicionales -----

// Comando: ayuda nombre_comando(opcional)
void ayuda(vector<string> args) {
    if (args.empty()){
        for (pair<const string, string> tupla: descComandosConsola) {
            cout << "\t" << tupla.first << endl;
        }
    } else if (args.size() == 1) {
        if (descComandosConsola.count(args[0]) > 0) {
            cout << "\t" << descComandosConsola[args[0]] << endl;
        } else {
            throw runtime_error("No se encontro el comando '" + args[0] + "'");
        }
    } else {
        throw runtime_error("El comando 'ayuda' recibe maximo un argumento");
    }
}

// Funcion que inicializa los maps donde se guarda la descripcion y la funcion correspondiente a cada comando
void llenarMaps(map<string, string> &descComandosConsola, map<string, void(*)(vector<string>)> &comandosConsola) {
    // comando name, comando description
    // comando name, comando callback function

    descComandosConsola.insert({"cargar_comandos",
        "Comando: cargar_comandos nombre_archivo\n"
        "Carga en memoria los comandos de desplazamiento contenidos en el archivo identificado por nombre_archivo, "
        "es decir, utiliza adecuadamente las estructuras lineales para cargar la informacion de los comandos en memoria. "
        "Si dentro de la misma sesion de trabajo ya se han cargado otros archivos de comandos (usando el comando "
        "cargar_comandos), la informacion debe sobreescribirse en memoria, es decir, no se deben combinar informaciones "
        "de comandos de diferentes archivos."
    });
    comandosConsola.insert({"cargar_comandos", cargar_comandos});

    descComandosConsola.insert({"cargar_elementos",
        "Comando: cargar_elementos nombre_archivo\n"
        "Carga en memoria los comandos de desplazamiento contenidos en el archivo identificado por nombre_archivo, "
        "es decir, utiliza adecuadamente las estructuras lineales para cargar la informacion de los comandos "
        "en memoria. Si dentro de la misma sesion de trabajo ya se han cargado otros archivos de comandos "
        "(usando el comando cargar_comandos), la informacion debe sobreescribirse en memoria, es decir, no se "
        "deben combinar informaciones de comandos de diferentes archivos."
    });
    comandosConsola.insert({"cargar_elementos", cargar_elementos});
    
    descComandosConsola.insert({"agregar_movimiento",
        "Comando: agregar_movimiento tipo_mov magnitud unidad_med\n"
        "Agrega el comando de movimiento descrito a la lista de comandos del robot \"Curiosity\". El movimiento puede "
        "ser de dos tipos: avanzar o girar. La magnitud corresponde al valor del movimiento; si es avanzar, el numero "
        "de unidades que se espera avanzar, si es girar la cantidad de grados que debe girar. La unidad de medida "
        "corresponde a la convencion con la que se mide la magnitud del movimiento (centimetros, metros, grados, ...). "
        "Si no se envia la informacion completa y adecuada del comando de movimiento, este no puede agregarse a la "
        "lista de los comandos que se enviaran al robot desde la tierra."
    });
    comandosConsola.insert({"agregar_movimiento", agregar_movimiento});

    descComandosConsola.insert({"agregar_analisis",
        "Comando: agregar_analisis tipo_analisis objeto comentario(opcional) "
        "Agrega el comando de analisis descrito a la lista de comandos del robot \"Curiosity\". El analisis puede "
        "ser de tres tipos: fotografiar, composicion o perforar. El objeto es el nombre del elemento que se quiere "
        "analizar (roca, arena, monticulo, ...). El comentario es opcional y permite agregar mas informacion sobre "
        "el elemento o el analisis, este comentario estara encerrado entre comillas simples (ejemplo: 'roca_cuadrante_32'). "
        "Si no se envia la informacion completa y adecuada del comando de analisis, este no puede agregarse a la lista "
        "de los comandos que se enviaran al robot desde la tierra."
    });
    comandosConsola.insert({"agregar_analisis", agregar_analisis});

    descComandosConsola.insert({"agregar_elementos",
        "Comando: agregar_elementos tipo_comp tamano unidad_med coordX coordY\n"
        "Agrega el componente o elemento descrito a la lista de puntos de interes del robot \"Curiosity\". El tipo "
        "de componente puede ser uno entre roca, crater, monticulo o duna. El tamano es un valor real que da "
        "cuenta de que tan grande es el elemento; y la unidad de medida complementa este valor con la convencion "
        "que se uso para su medicion (centimetros, metros, ...). Finalmente, las coordenadas x y y corresponden "
        "a numeros reales que permiten conocer la ubicacion del elemento en el sistema de coordenadas del suelo "
        "marciano utilizado por el vehiculo. Si no se envia la informacion completa y adecuada del elemento, "
        "este no puede agregarse a la lista de puntos de interes que se enviaran al robot desde la tierra."
    });
    comandosConsola.insert({"agregar_elementos", agregar_elementos});
    
    descComandosConsola.insert({"guardar",
        "Comando: guardar tipo_archivo nombre_archivo\n"
        "Guarda en el archivo nombre_archivo la informacion solicitada de acuerdo al tipo de archivo: 'comandos' "
        "almacena en el archivo la informacion de comandos de movimiento y de analisis que debe ejecutar el robot, "
        "'elementos' almacena en el archivo la informacion de los componentes o puntos e interes conocidos en el suelo "
        "marciano."
    });
    comandosConsola.insert({"guardar", guardar});

    descComandosConsola.insert({"simular_comandos",
        "Comando: simular_comandos coordX coordY\n"
        "Permite simular el resultado de los comandos de movimiento que se enviaran al robot \"Curiosity\" desde "
        "la Tierra, facilitando asi la validacion de la nueva posicion en la que podria ubicarse. Para ejecutarse "
        "adecuadamente, requiere conocer la posicion actual (coordenadas x y y) del vehiculo. Hay que tener en cuenta "
        "que solo los comandos de movimiento son necesarios, no los de analisis."
    });
    comandosConsola.insert({"simular_comandos", simular_comandos});

    descComandosConsola.insert({"salir",
        "Comando: salir\n"
        "Termina la ejecucion de la aplicacion."
    });
    comandosConsola.insert({"salir", salir});

    descComandosConsola.insert({"ubicar_elementos",
        "Comando: ubicar_elementos\n"
        "El comando debe utilizar la informacion de puntos de interes almacenada en memoria para ubicarlos en "
        "una estructura de datos jerarquica adecuada, que permita luego realizar consultas geograficas sobre estos "
        "elementos. Si alguno de los elementos no puede agregarse adecuadamente, debe generarse un mensaje de error, "
        "pero deben terminarse de procesar todos los elementos almacenados en memoria."
    });
    comandosConsola.insert({"ubicar_elementos", ubicar_elementos});
    
    descComandosConsola.insert({"crear_mapa",
        "Comando: crear_mapa coeficiente_conectividad\n"
        "El comando debe utilizar la informacion de puntos de interes almacenada en memoria para ubicarlos en una "
        "estructura no lineal y conectarlos entre si teniendo en cuenta el coeficiente de conectividad dado. El "
        "objetivo es que cada elemento este conectado a los demas elementos mas cercanos a el, midiendo la cercania "
        "a traves de la distancia euclidiana entre los elementos. Esta distancia euclidiana tambien se utiliza como "
        "el peso o etiqueta de la conexion entre los elementos. Con el coeficiente de conectividad se identifica la "
        "cantidad de vecinos que puede tener cada elemento tomando como base el total de elementos que se ubicaran "
        "en el mapa (ejemplo: si se van a ubicar 35 elementos, y el coeficiente de conectividad es 0.4, la cantidad "
        "de vecinos que cada elemento debe tener es 35 * 0.4 = 14)."
    });
    comandosConsola.insert({"crear_mapa", crear_mapa});
    
    descComandosConsola.insert({"en_cuadrante",
        "Comando: en_cuadrante coordX1 coordX2 coordY1 coordY2\n"
        "Permite utilizar la estructura creada con el comando anterior para retornar una lista de "
        "los componentes o elementos que estan dentro del cuadrante geografico descrito por los limites de coordenadas "
        "en x y y. Es necesario haber ejecutado el comando ubicar_elementos para poder realizar "
        "la busqueda por cuadrantes. Los limites de coordenadas deben garantizar que coordX1 < coordX2 y "
        "coordY1 < coordY2."
    });
    comandosConsola.insert({"en_cuadrante", en_cuadrante});
    
    descComandosConsola.insert({"ruta_mas_larga",
        "Comando: ruta_mas_larga\n"
        "Con el mapa ya creado, el comando permite identificar los dos componentes mas alejados entre si de acuerdo "
        "a las conexiones generadas. Es importante aclarar que el comando retorna los elementos mas alejados de "
        "acuerdo a las conexiones que se encuentran en el mapa, no los elementos que esten a mayor distancia "
        "euclidiana entre si. Al encontrar esa ruta mas larga dentro del mapa, el comando imprime en pantalla los "
        "elementos de origen y destino, la longitud total de la ruta, y la secuencia de elementos que hay que seguir "
        "para ir del elemento origen al elemento destino."
    });
    comandosConsola.insert({"ruta_mas_larga", ruta_mas_larga});

    descComandosConsola.insert({"ayuda",
        "Comando: ayuda nombre_comando(opcional)\n"
        "Permite la visualizacion de la descripcion de cada uno de los comandos."
    });
    comandosConsola.insert({"ayuda", ayuda});
}


// ----- main -----

int main(){
    char delim = ' ';
    string lineaComando, comando, palabra;

    llenarMaps(descComandosConsola, comandosConsola);

    Sistema sistema;

    cout << " --- Curiosity --- \n";

    do {
        // vector de argumentos del comando ingresado
        vector<string> args;

        cout << "$ ";
        getline(cin, lineaComando);


        stringstream stream(lineaComando);
        getline(stream, comando, delim);

        while (getline(stream, palabra, delim)) {
            args.push_back(palabra);
        }

        try {
            if (lineaComando == "") {
                continue;
            } else if (comandosConsola.count(comando) > 0) {
                comandosConsola[comando](args);
            } else {
                throw runtime_error("El comando '" + comando + "' no existe");
            }
        } catch (const runtime_error& e) {
            cerr << "Error: " << e.what() << '\n';
        }

    } while (comando!="salir");
}