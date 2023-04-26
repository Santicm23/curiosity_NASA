
#ifndef DESPLAZAMIENTO
#define DESPLAZAMIENTO


#include <string>

#include "robotCuriosity.h"

using namespace std;


class Desplazamiento {
    public:

        //* conviertir la información del desplazamiento a un string
        virtual string toString(char delim) = 0;
};

#endif