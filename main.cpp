
#include<fstream>
#include<iostream>
#include<map>
#include<string>
#include<sstream>
#include<vector>

using namespace std;


// ----- variables globales -----

map<string, string> commandHelps;
map<string, void(*)(vector<string>)> commands;


// ----- componente 1 -----

void cargar_comandos(vector<string> args) {
    if (args.size() != 1)
        throw runtime_error("Debe ingresar un nombre de archivo y solo uno.");

    fstream fs;
    string line;
    
    fs.open(args[0], ios::in);

    if (!fs.is_open())
        throw runtime_error("'" + args[0] + "' no se encuentra o no puede leerse.");

    if (fs.peek() == EOF)
        throw runtime_error("'" + args[0] + "' no contiene comandos.");
    
    while(!fs.eof()) {
        getline(fs, line);
        cout << line << endl;
    }

    fs.close();
    
}

void cargar_elementos(vector<string> args) {}

void agregar_movimiento(vector<string> args) {}

void agregar_analisis(vector<string> args) {}

void agregar_elementos(vector<string> args) {}

void guardar(vector<string> args) {}

void simular_comandos(vector<string> args) {}

void salir(vector<string>) {}


// ----- componente 2 -----

void ubicar_elementos(vector<string> args) {}

void en_cuadrante(vector<string> args) {}


// ----- componente 3 -----

void crear_mapa(vector<string> args) {}

void ruta_mas_larga(vector<string> args) {}


// ----- comandos y funciones adicionales -----

void ayuda(vector<string> args) {
    if (args.empty()){
        for(map<string, string>::iterator it = commandHelps.begin(); it != commandHelps.end(); ++it) {
            cout << "\t" << it->first << endl;
        }
    } else if (args.size() == 1) {
        if (commandHelps.count(args[0]) > 0) {
            cout << "\t" << commandHelps[args[0]] << endl;
        } else {
            throw runtime_error("No se encontro el comando '" + args[0] + "'");
        }
    } else {
        throw runtime_error("El comando 'ayuda' recibe maximo un argumento");
    }
}

void fillMaps(map<string, string> &descMap, map<string, void(*)(vector<string>)>&exeMap) {
    // command name, command description
    // command name, command callback function

    descMap.insert({"ayuda",
        "Comando: ayuda | ayuda nombre_comando\n"
        "\tPermite la visualizacion de la descripcion de cada uno de los comandos."
    });
    exeMap.insert({"ayuda", ayuda});

    descMap.insert({"cargar_comandos",
        "Comando: cargar_comandos nombre_archivo\n"
        "\tCarga en memoria los comandos de desplazamiento contenidos en el archivo identificado por nombre_archivo,\n"
        "\tes decir, utiliza adecuadamente las estructuras lineales para cargar la informacion de los comandos en memoria.\n"
        "\tSi dentro de la misma sesion de trabajo ya se han cargado otros archivos de comandos (usando el comando\n"
        "\tcargar_comandos), la informacion debe sobreescribirse en memoria, es decir, no se deben combinar informaciones\n"
        "\tde comandos de diferentes archivos."
    });
    exeMap.insert({"cargar_comandos", cargar_comandos});

    descMap.insert({"cargar_elementos",
        "Comando: cargar_elementos nombre_archivo\n"
        "\tCarga en memoria los comandos de desplazamiento contenidos en el archivo identificado por nombre_archivo,\n"
        "\tes decir, utiliza adecuadamente las estructuras lineales para cargar la informacion de los comandos\n"
        "\ten memoria. Si dentro de la misma sesion de trabajo ya se han cargado otros archivos de comandos\n"
        "\t(usando el comando cargar_comandos), la informacion debe sobreescribirse en memoria, es decir, no se\n"
        "\tdeben combinar informaciones de comandos de diferentes archivos."
    });
    exeMap.insert({"cargar_elementos", cargar_elementos});
    
    descMap.insert({"agregar_movimiento",
        "Comando: agregar_movimiento tipo_mov magnitud unidad_med\n"
        "\tAgrega el comando de movimiento descrito a la lista de comandos del robot \"Curiosity\". El movimiento puede\n"
        "\tser de dos tipos: avanzar o girar. La magnitud corresponde al valor del movimiento; si es avanzar, el numero\n"
        "\tde unidades que se espera avanzar, si es girar la cantidad de grados que debe girar. La unidad de medida\n"
        "\tcorresponde a la convencion con la que se mide la magnitud del movimiento (centimetros, metros, grados, ...).\n"
        "\tSi no se envia la informacion completa y adecuada del comando de movimiento, este no puede agregarse a la\n"
        "\tlista de los comandos que se enviaran al robot desde la tierra."
    });
    exeMap.insert({"agregar_movimiento", agregar_movimiento});

    descMap.insert({"agregar_analisis",
        "Comando: agregar_analisis tipo_analisis objeto comentario\n"
        "\tAgrega el comando de analisis descrito a la lista de comandos del robot \"Curiosity\". El analisis puede\n"
        "\tser de tres tipos: fotografiar, composicion o perforar. El objeto es el nombre del elemento que se quiere\n"
        "\tanalizar (roca, arena, monticulo, ...). El comentario es opcional y permite agregar mas informacion sobre\n"
        "\tel elemento o el analisis, este comentario estara encerrado entre comillas simples (ejemplo: 'roca_cuadrante_32').\n"
        "\tSi no se envia la informacion completa y adecuada del comando de analisis, este no puede agregarse a la lista\n"
        "\tde los comandos que se enviaran al robot desde la tierra."
    });
    exeMap.insert({"agregar_analisis", agregar_analisis});

    descMap.insert({"agregar_elementos",
        "Comando: agregar_elementos tipo_comp tamaño unidad_med coordX coordY\n"
        "\tAgrega el componente o elemento descrito a la lista de puntos de interes del robot \"Curiosity\". El tipo\n"
        "\tde componente puede ser uno entre roca, crater, monticulo o duna. El tamaño es un valor real que da\n"
        "\tcuenta de que tan grande es el elemento; y la unidad de medida complementa este valor con la convencion\n"
        "\tque se uso para su medicion (centimetros, metros, ...). Finalmente, las coordenadas x y y corresponden\n"
        "\ta numeros reales que permiten conocer la ubicacion del elemento en el sistema de coordenadas del suelo\n"
        "\tmarciano utilizado por el vehiculo. Si no se envia la informacion completa y adecuada del elemento,\n"
        "\teste no puede agregarse a la lista de puntos de interes que se enviaran al robot desde la tierra."
    });
    exeMap.insert({"agregar_elementos", agregar_elementos});
    
    descMap.insert({"guardar",
        "Comando: guardar tipo_archivo nombre_archivo\n"
        "\tGuarda en el archivo nombre_archivo la informacion solicitada de acuerdo al tipo de archivo: comandos\n"
        "\talmacena en el archivo la informacion de comandos de movimiento y de analisis que debe ejecutar el robot,\n"
        "\telementos almacena en el archivo la informacion de los componentes o puntos e interes conocidos en el suelo\n"
        "\tmarciano."
    });
    exeMap.insert({"guardar", guardar});

    descMap.insert({"simular_comandos",
        "Comando: simular_comandos coordX coordY\n"
        "\tPermite simular el resultado de los comandos de movimiento que se enviaran al robot \"Curiosity\" desde\n"
        "\tla Tierra, facilitando asi la validacion de la nueva posicion en la que podria ubicarse. Para ejecutarse\n"
        "\tadecuadamente, requiere conocer la posicion actual (coordenadas x y y) del vehiculo. Hay que tener en cuenta\n"
        "\tque solo los comandos de movimiento son necesarios, no los de analisis."
    });
    exeMap.insert({"simular_comandos", simular_comandos});

    descMap.insert({"salir",
        "Comando: salir\n"
        "\tTermina la ejecucion de la aplicacion."
    });
    exeMap.insert({"salir", salir});

    descMap.insert({"ubicar_elementos",
        "Comando: ubicar_elementos\n"
        "\tEl comando debe utilizar la informacion de puntos de interes almacenada en memoria para ubicarlos en\n"
        "\tuna estructura de datos jerarquica adecuada, que permita luego realizar consultas geograficas sobre estos\n"
        "\telementos. Si alguno de los elementos no puede agregarse adecuadamente, debe generarse un mensaje de error,\n"
        "\tpero deben terminarse de procesar todos los elementos almacenados en memoria."
    });
    exeMap.insert({"ubicar_elementos", ubicar_elementos});
    
    descMap.insert({"crear_mapa",
        "Comando: crear_mapa coeficiente_conectividad\n"
        "\tEl comando debe utilizar la informacion de puntos de interes almacenada en memoria para ubicarlos en una\n"
        "\testructura no lineal y conectarlos entre si teniendo en cuenta el coeficiente de conectividad dado. El\n"
        "\tobjetivo es que cada elemento este conectado a los demas elementos mas cercanos a el, midiendo la cercania\n"
        "\ta traves de la distancia euclidiana entre los elementos. Esta distancia euclidiana tambien se utiliza como\n"
        "\tel peso o etiqueta de la conexion entre los elementos. Con el coeficiente de conectividad se identifica la\n"
        "\tcantidad de vecinos que puede tener cada elemento tomando como base el total de elementos que se ubicaran\n"
        "\ten el mapa (ejemplo: si se van a ubicar 35 elementos, y el coeficiente de conectividad es 0.4, la cantidad\n"
        "\tde vecinos que cada elemento debe tener es 35 * 0.4 = 14)."
    });
    exeMap.insert({"crear_mapa", crear_mapa});
    
    descMap.insert({"ruta_mas_larga",
        "Comando: ruta_mas_larga\n"
        "\tCon el mapa ya creado, el comando permite identificar los dos componentes mas alejados entre si de acuerdo\n"
        "\ta las conexiones generadas. Es importante aclarar que el comando retorna los elementos mas alejados de\n"
        "\tacuerdo a las conexiones que se encuentran en el mapa, no los elementos que esten a mayor distancia\n"
        "\teuclidiana entre si. Al encontrar esa ruta mas larga dentro del mapa, el comando imprime en pantalla los\n"
        "\telementos de origen y destino, la longitud total de la ruta, y la secuencia de elementos que hay que seguir\n"
        "\tpara ir del elemento origen al elemento destino."
    });
    exeMap.insert({"ruta_mas_larga", ruta_mas_larga});


}


// ----- main -----

int main(){
    char delim = ' ';
    string commandLine, command, word;


    fillMaps(commandHelps, commands);

    do {
        vector<string> args;

        cout<<"$ ";
        getline(cin, commandLine);


        stringstream stream(commandLine);
        getline(stream, command, delim);

        while(getline(stream, word, delim)) {
            args.push_back(word);
        }

        try {
            if (commandLine == "") {
                continue;
            } else if (commands.count(command) > 0) {
                commands[command](args);
            } else {
                throw runtime_error("El comando '" + command + "' no existe");
            }
        } catch(const runtime_error& e) {
            cerr << "Error: " << e.what() << '\n';
        }

    } while (command!="salir");
}