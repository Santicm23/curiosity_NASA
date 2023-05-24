
#include <iostream>
#include <queue>
#include <list>

#include "nodoQuad.h"
#include "elemento.h"

using namespace std;


NodoQuad::NodoQuad() {
    this->hijoSupIzq = nullptr;
    this->hijoSupDer = nullptr;
    this->hijoInfIzq = nullptr;
    this->hijoInfDer = nullptr;
}

NodoQuad::NodoQuad(Elemento& val) {
    this->dato = val;
    this->hijoSupIzq = nullptr;
    this->hijoSupDer = nullptr;
    this->hijoInfIzq = nullptr;
    this->hijoInfDer = nullptr;
}

NodoQuad::~NodoQuad() {
    delete this->hijoSupIzq;
    this->hijoSupIzq = nullptr;
    delete this->hijoSupDer;
    this->hijoSupDer = nullptr;
    delete this->hijoInfIzq;
    this->hijoInfIzq = nullptr;
    delete this->hijoInfDer;
    this->hijoInfDer = nullptr;
}

Elemento& NodoQuad::obtenerDato() {
    return this->dato;
}

void NodoQuad::fijarDato(Elemento& val) {
    this->dato = val;
}

NodoQuad* NodoQuad::obtenerHijoSupIzq() {
    return this->hijoSupIzq;
}

NodoQuad* NodoQuad::obtenerHijoSupDer() {
    return this->hijoSupDer;
}

NodoQuad* NodoQuad::obtenerHijoInfIzq() {
    return this->hijoInfIzq;
}

NodoQuad* NodoQuad::obtenerHijoInfDer() {
    return this->hijoInfDer;
}

void NodoQuad::fijarHijoSupIzq(NodoQuad* sizq) {
    this->hijoSupIzq = sizq;
}

void NodoQuad::fijarHijoSupDer(NodoQuad* sder) {
    this->hijoSupDer = sder;
}

void NodoQuad::fijarHijoInfIzq(NodoQuad* iizq) {
    this->hijoInfIzq = iizq;
}

void NodoQuad::fijarHijoInfDer(NodoQuad* ider) {
    this->hijoInfDer = ider;
}

bool NodoQuad::esHoja() {
    if (this->hijoSupIzq == nullptr && this->hijoSupDer == nullptr && this->hijoInfIzq == nullptr && this->hijoInfDer == nullptr)
        return true;
    return false;
}

bool NodoQuad::insertar(Elemento& val) {
    pair<float, float> punto1 = val.getPunto();
    pair<float, float> punto2 = this->dato.getPunto();
    
    if (this->hijoSupIzq == nullptr && punto1.first <= punto2.first && punto1.second > punto2.second) {
        this->fijarHijoSupIzq(new NodoQuad(val));
        return true;

    } else if (this->hijoSupDer == nullptr && punto1.first > punto2.first && punto1.second > punto2.second) {
        this->fijarHijoSupDer(new NodoQuad(val));
        return true;

    } else if (this->hijoInfIzq == nullptr && punto1.first <= punto2.first && punto1.second <= punto2.second) {
        this->fijarHijoInfIzq(new NodoQuad(val));
        return true;

    } else if (this->hijoInfDer == nullptr && punto1.first > punto2.first && punto1.second <= punto2.second) {
        this->fijarHijoInfDer(new NodoQuad(val));
        return true;

    } else {
        if (punto1.first <= punto2.first && punto1.second > punto2.second) {
            return this->hijoSupIzq->insertar(val);

        } else if (punto1.first > punto2.first && punto1.second > punto2.second) {
            return this->hijoSupDer->insertar(val);
            
        } else if (punto1.first <= punto2.first && punto1.second <= punto2.second) {
            return this->hijoInfIzq->insertar(val);

        } else if (punto1.first > punto2.first && punto1.second <= punto2.second) {
            return this->hijoInfDer->insertar(val);
        }
    }
    return false;
}

void NodoQuad::preOrden() {
    cout << this->dato.toString() << " ";
    if (this->hijoSupIzq != nullptr) {
        this->hijoSupIzq->preOrden();
    }
    if (this->hijoSupDer != nullptr) {
        this->hijoSupDer->preOrden();
    }
    if (this->hijoInfIzq != nullptr) {
        this->hijoInfIzq->preOrden();
    }
    if (this->hijoInfDer != nullptr) {
        this->hijoInfDer->preOrden();
    }
}

void NodoQuad::inOrden() {
    if (this->hijoSupIzq != nullptr) {
        this->hijoSupIzq->inOrden();
    }
    if (this->hijoSupDer != nullptr) {
        this->hijoSupDer->inOrden();
    }
    cout << this->dato.toString() << " ";
    if (this->hijoInfIzq != nullptr) {
        this->hijoInfIzq->inOrden();
    }
    if (this->hijoInfDer != nullptr) {
        this->hijoInfDer->inOrden();
    }
}

void NodoQuad::posOrden() {
    if (this->hijoSupIzq != nullptr) {
        this->hijoSupIzq->posOrden();
    }
    if (this->hijoSupDer != nullptr) {
        this->hijoSupDer->posOrden();
    }
    if (this->hijoInfIzq != nullptr) {
        this->hijoInfIzq->posOrden();
    }
    if (this->hijoInfDer != nullptr) {
        this->hijoInfDer->posOrden();
    }
    cout << this->dato.toString() << " ";
}

void NodoQuad::nivelOrden() {
    queue<NodoQuad*> cola;
    cola.push(this);
    while (!cola.empty()) {
        NodoQuad* nodo = cola.front();
        cola.pop();
        cout << nodo->dato.toString() << " ";
        if (nodo->hijoSupIzq != nullptr) {
            cola.push(nodo->hijoSupIzq);
        }
        if (nodo->hijoSupDer != nullptr) {
            cola.push(nodo->hijoSupDer);
        }
        if (nodo->hijoInfIzq != nullptr) {
            cola.push(nodo->hijoInfIzq);
        }
        if (nodo->hijoInfDer != nullptr) {
            cola.push(nodo->hijoInfDer);
        }
    }
}

list<Elemento> NodoQuad::en_cuadrante(pair<float, float> min, pair<float, float> max) {
    list<Elemento> l;
    if (this == nullptr) 
        return list<Elemento>();
    
    else if (this->esHoja()) {
        if (this->obtenerDato().estaEnCuadrante(min, max))
            return list<Elemento>({this->obtenerDato()});        
        else 
            return list<Elemento>();    

    } 
    
    else {
        pair<float, float> punto = this->obtenerDato().getPunto();

        //La raíz está en el cuadrante
        
        if (this->obtenerDato().estaEnCuadrante(min, max)) 
            l.push_back(this->obtenerDato());

        //if min cuadrante x < nodoRaizX() && min cuadrante y < nodoRaizY(){}
            //El nodo raíz se encuentra dentro del cuadrante
            //Puede que todos los hijos se encuentren dentro del cuadrante

        else if (min.first <= punto.first && min.second <= punto.second){
            l.splice(l.end(), this->hijoSupIzq->en_cuadrante(min, max));
            l.splice(l.end(), this->hijoSupDer->en_cuadrante(min, max));
            l.splice(l.end(), this->hijoInfIzq->en_cuadrante(min, max));
            l.splice(l.end(), this->hijoInfDer->en_cuadrante(min, max));
        }

        //if min cuadrante x < nodoRaizX() && min cuadrante y > nodoRaizY(){}
            //Puede que los hijos SupDer y SupIzq se encuentren dentro del cuadrante

        else if (min.first <= punto.first && min.second > punto.second){
            l.splice(l.end(), this->hijoSupIzq->en_cuadrante(min, max));
            l.splice(l.end(), this->hijoSupDer->en_cuadrante(min, max));
        }

        //if min cuadrante x > nodoRaizX() && min cuadrante y < nodoRaizY(){}
            //Puede que los hijos SupDer e InfDer se encuentren dentro del cuadrante

        else if (min.first > punto.first && min.second <= punto.second){
            l.splice(l.end(), this->hijoSupDer->en_cuadrante(min, max));
            l.splice(l.end(), this->hijoInfDer->en_cuadrante(min, max));
        }

        //if min cuadrante x > nodoRaizX() && min cuadrante y > nodoRaizY(){}
            //Puede que el hijoSupDer se encuentre dentro del cuadrante

        else 
            l.splice(l.end(), this->hijoSupDer->en_cuadrante(min, max));

        return l;
    }
}