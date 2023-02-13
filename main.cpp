
#include<iostream>
#include<string>

using namespace std;


int main(){
    string command;
    do  {
        cout<<"\n$ ";
        cin>>command;

        cout<<"comando: "<<command;

        if (command == "") {

        } else if (command == "ayuda") {
            
        } else if (command == "\n") {
            
        }
    }while (command!="quit");
}