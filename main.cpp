
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