
#include<iostream>
#include<string>
#include<sstream>

using namespace std;


int main(){
    string command;
    do  {
        cout<<"$ ";
        getline(cin,command);
        cout<<command<<endl;
        if (command == "") 
        {

        }
        if (command.find("cargar_comandos")!=string::npos)
        {
            string parametro1,parametro2;
            stringstream partir(command);
            partir>>parametro1>>parametro1;
            cout<<"1."<<parametro1<<endl;
            
        } 
        else if(command == "cargar_elementos")
        {
            string a;
        }
        else if(command=="agregar_movimiento")
        {
            string a;
        }
        else if(command=="agregar_analisis")
        {
            string a;
        }
        else if(command=="agregar_elemento")
        {
            string a;
        }
        else if(command=="guardar")
        {
            string a;
        }
        else if(command=="simular_comandos")
        {
            string a;
        }
        else if(command=="ubicar_elementos")
        {
            string a;
        }
        else if(command=="en_cuadrante")
        {
            string a;
        }
        else if(command=="crear_mapa")
        {
            
        }
        else if(command=="ruta_mas_larga")
        {
            
        }
        else if (command == "ayuda") 
        {
            cout<<"cargar_comandos      "<<"\n"
                <<"cargar_elementos     "<<"\n"
                <<"agregar_movimiento   "<<"\n"
                <<"agregar_analisis     "<<"\n"
                <<"agregar_elemento     "<<"\n"
                <<"guardar              "<<"\n"
                <<"simular_comandos     "<<"\n"
                <<"ubicar_elementos     "<<"\n"
                <<"en_cuadrante         "<<"\n"
                <<"crear_mapa           "<<"\n"
                <<"ruta_mas_larga       "<<"\n";
        }
        else if (command == "ayuda cargar_comandos")
        {

        } 
        else if(command == "ayuda cargar_elementos")
        {

        }
        else if(command=="ayuda agregar_movimiento")
        {
            
        }
        else if(command=="ayuda agregar_analisis")
        {
            
        }
        else if(command=="ayuda agregar_elemento")
        {
            
        }
        else if(command=="ayuda guardar")
        {
            
        }
        else if(command=="ayuda simular_comandos")
        {
            
        }
        else if(command=="ayuda ubicar_elementos")
        {
            
        }
        else if(command=="ayuda en_cuadrante")
        {
            
        }
        else if(command=="ayuda crear_mapa")
        {
            
        }
        else if(command=="ayuda ruta_mas_larga")
        {
            
        }
        else{
            cout<<"Aprende a escribir\n";
        }
            
    }while (command!="salir");
}