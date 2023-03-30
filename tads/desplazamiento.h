
#ifndef DESPLAZAMIENTO
#define DESPLAZAMIENTO


#include <string>

#include "robotCuriosity.h"

using namespace std;


class Desplazamiento {
    public:
        // static void verificarDatos();
        virtual string toString(char delim) = 0;
};

#endif