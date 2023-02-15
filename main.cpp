
#include<iostream>
#include<string>
#include<sstream>
#include<map>

using namespace std;


void salir(string) {};

void ayuda(string command) {
    cout<<"cargar_comandos      \n"
        <<"cargar_elementos     \n"
        <<"agregar_movimiento   \n"
        <<"agregar_analisis     \n"
        <<"agregar_elemento     \n"
        <<"guardar              \n"
        <<"simular_comandos     \n"
        <<"ubicar_elementos     \n"
        <<"en_cuadrante         \n"
        <<"crear_mapa           \n"
        <<"ruta_mas_larga       \n";
}

void cargar_comandos(string command) {
    string parametro1,parametro2;
    stringstream partir(command);
    partir>>parametro1>>parametro1;
    cout<<"1."<<parametro1<<endl;
}

int main(){
    string command, word;

    map<string, void(*)(string)> commands;
    commands.insert({"salir", salir});
    commands.insert({"ayuda", ayuda});
    commands.insert({"cargar_comandos", cargar_comandos});

    do {
        cout<<"$ ";
        getline(cin, command);

        stringstream stream(command);
        getline(stream, word, ' ');

        if (command == "") {
            continue;
        } else if (commands.count(word) > 0){
                commands[word](command);
        } else {
            cerr << "El comando no existe" << '\n';
        }
            
    }while (command!="salir");
}