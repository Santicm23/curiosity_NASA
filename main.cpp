
#include<iostream>
#include<string>
#include<sstream>
#include<map>
#include<vector>

using namespace std;


map<string, string> commandHelps;
map<string, void(*)(vector<string>)> commands;

void salir(vector<string>) {}

void cargar_comandos(vector<string> args) {}
void cargar_elementos(vector<string> args) {}
void agregar_movimiento(vector<string> args) {}
void agregar_analisis(vector<string> args) {}
void agregar_elemento(vector<string> args) {}
void b(vector<string> args) {}

void ayuda(vector<string> args) {
    if (args.empty()){
        for(map<string, string>::iterator it = commandHelps.begin(); it != commandHelps.end(); ++it) {
            cout << "\t" << it->first << endl;
        }
    } else if (args.size() == 1) {
        if (commandHelps.count(args[0]) > 0) {
            cout << "\t" << commandHelps[args[0]] << endl;
        } else {
            cout << "ERROR: No se encontro el comando '" << args[0] << "'\n";
        }
    } else {
        cout << "ERROR: El comando 'ayuda' solo recibe un argumento\n";
    }
}

void fillMaps(map<string, string> &descMap, map<string, void(*)(vector<string>)>&exeMap) {
    // command name, command description
    // command name, command callback function

    descMap.insert({"cargar_comandos",
        "Comando: cargar_comandos nombre_archivo\n"
        "Carga en memoria los comandos de desplazamiento contenidos en el archivo identificado por nombre_archivo, "
        "es decir, utiliza adecuadamente las estructuras lineales para cargar la informacion de los comandos en memoria. "
        "Si dentro de la misma sesion de trabajo ya se han cargado otros archivos de comandos (usando el comando "
        "cargar_comandos), la informacion debe sobreescribirse en memoria, es decir, no se deben combinar informaciones "
        "de comandos de diferentes archivos."
    });
    exeMap.insert({"cargar_comandos", cargar_comandos});
    descMap.insert({"cargar_elementos",
        "comando: cargar_elementos nombre_archivo\n"
        "Carga en memoria los datos de puntos de interes o elementos contenidos en el archivo "
        "identificado por nombre_archivo , es decir, utiliza adecuadamente las estructuras lineales para cargar "
        "la informacion de los elementos en memoria. Si dentro de la misma sesion de trabajo ya se han cargado "
        "otros archivos de puntos de interes (usando el comando cargar_elementos), la informacion debe "
        "sobreescribirse en memoria, es decir, no se deben combinar informaciones de elementos de diferentes "
        "archivos."
    });
    exeMap.insert({"cargar_elementos", cargar_elementos});
    descMap.insert({"agregar_movimiento",
        "comando: agregar_movimiento tipo_mov magnitud unidad_med\n"
        "Agrega el comando de movimiento descrito a la lista de comandos del robot 'Curiosity'. " 
        "El movimiento puede ser de dos tipos: avanzar o girar. La magnitud corresponde al valor del "
        "movimiento, si es avanzar, el numero de unidades que se espera avanzar, si es girar la cantidad de grados" 
        "que debe girar. La unidad de medida corresponde a la convencion con la que se mide la magnitud del "
        "movimiento (centimetros, metros, grados, ...). Si no se envia la informacion completa y adecuada "
        " del comando de movimiento, este no puede agregarse a la lista de los comandos que se enviaran al robot "
        "desde la tierra."
    });
    exeMap.insert({"agregar_movimiento",agregar_movimiento});

    descMap.insert({"agregar_analisis",
        "comando: agregar_analisis tipo_analisis objeto comentario\n"
        "Agrega el comando de analisis descrito a la lista de comandos del robot 'Curiosity'. El "
        "analisis puede ser de tres tipos: fotografiar, composicion o perforar. El objeto es el nombre del "
        "elemento que se quiere analizar (roca, arena, monticulo, ...). El comentario es opcional y permite agregar "
        "mas informacion sobre el elemento o el analisis, este comentario estara encerrado entre comillas simples "
        "(ejemplo: 'roca_cuadrante_32'). Si no se envia la informacion completa y adecuada del comando de "
        "analisis, este no puede agregarse a la lista de los comandos que se enviaran al robot desde la tierra."
    });
    exeMap.insert({"agregar_analisis",agregar_analisis});

    descMap.insert({"agregar_elemento",
        "comando: agregar_elemento tipo_comp tamano unidad_med coordX coordY\n"
        "Agrega el componente o elemento descrito a la lista de puntos de interes del robot 'Curiosity'. "
        "El tipo de componente puede ser uno entre roca, crater, monticulo o duna. El tamano "
        "es un valor real que da cuenta de que tan grande es el elemento, y la unidad de medida complementa "
        "este valor con la convencion que se uso para su medicion (centimetros, metros, ...). Finalmente, las "
        "coordenadas x y y corresponden a numeros reales que permiten conocer la ubicacion del elemento en "
        "el sistema de coordenadas del suelo marciano utilizado por el vehiculo. Si no se envia la informacion "
        "completa y adecuada del elemento, este no puede agregarse a la lista de puntos de interes que se enviaran "
        "al robot desde la tierra."
    });
    exeMap.insert({"agregar_elemento",agregar_elemento});
    descMap.insert({"salir",
        "Comando: salir\n"
        "\tTermina la ejecución de la aplicación."
    });
    exeMap.insert({"salir", salir});

    descMap.insert({"ayuda",
        "Comando: ayuda | ayuda nombre_comando\n"
        "\tPermite la visualizacion de la descripción de cada uno de los comandos"
    });
    exeMap.insert({"ayuda", ayuda});

}

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

        if (commandLine == "") {
            continue;
        } else if (commands.count(command) > 0) {
            commands[command](args);
        } else {
            cout << "ERROR: El comando '"<< command <<"' no existe" << '\n';
        }

    } while (command!="salir");
}