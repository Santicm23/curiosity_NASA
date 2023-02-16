
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

void ayuda(vector<string> args) {
    if (args.empty()){
        for(map<string, string>::iterator it = commandHelps.begin(); it != commandHelps.end(); ++it) {
            cout << "\t" << it->first << endl;
        }
    } else if (args.size() == 1){
        if (commandHelps.count(args[0]) > 0){
            cout << "\t" << commandHelps[args[0]] << endl;
        } else {
            cout << "No se encontro el comando '" << args[0] << "'\n";
        }
    } else {
        cout << "El comando 'ayuda' solo recibe un argumento\n";
    }
    
}

void fillMaps(map<string, string> &descMap, map<string, void(*)(vector<string>)>&exeMap) {
    // command name, command description
    // command name, command callback function

    descMap.insert({"cargar_comandos",
        "Carga en memoria los comandos de desplazamiento contenidos en el archivo identificado por nombre_archivo,\n"
        "es decir, utiliza adecuadamente las estructuras lineales para cargar la información de los comandos en memoria.\n"
        "Si dentro de la misma sesión de trabajo ya se han cargado otros archivos de comandos (usando el comando\n"
        "cargar_comandos), la información debe sobreescribirse en memoria, es decir, no se deben combinar informaciones\n"
        "de comandos de diferentes archivos."
    });
    exeMap.insert({"cargar_comandos", cargar_comandos});

    descMap.insert({"salir", "a"});
    exeMap.insert({"salir", salir});

    descMap.insert({"ayuda", "b"});
    exeMap.insert({"ayuda", ayuda});

}

int main(){
    string commandLine, command, word;


    fillMaps(commandHelps, commands);

    do {
        vector<string> args;

        cout<<"$ ";
        getline(cin, commandLine);


        stringstream stream(commandLine);
        getline(stream, command, ' ');

        while(getline(stream, word, ' ')){
            args.push_back(word);
        }

        if (commandLine == "") {
            continue;
        } else if (commands.count(command) > 0){
            commands[command](args);
        } else {
            cout << "El comando '"<< command <<"' no existe" << '\n';
        }
            
    }while (command!="salir");
}