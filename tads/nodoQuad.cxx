
#include <iostream>
#include <queue>

#include "nodoQuad.h"

using namespace std;


NodoQuad::NodoQuad() {
    this->hijoSupIzq = nullptr;
    this->hijoSupDer = nullptr;
    this->hijoInfIzq = nullptr;
    this->hijoInfDer = nullptr;
}

NodoQuad::NodoQuad(punto val) {
    dato = val;
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

punto& NodoQuad::obtenerDato() {
    return this->dato;
}

void NodoQuad::fijarDato(punto val) {
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
    return (
        this->hijoSupIzq == nullptr
        && this->hijoSupDer == nullptr
        && this->hijoInfIzq == nullptr
        && this->hijoInfDer == nullptr
    );
}

bool NodoQuad::insertar(punto& val) {
    if (this->hijoSupIzq == nullptr && val.x < this->dato.x && val.y > this->dato.y) {
        this->fijarHijoSupIzq(new NodoQuad(val));
        return true;

    } else if (this->hijoSupDer == nullptr && val.x > this->dato.x && val.y > this->dato.y) {
        this->fijarHijoSupDer(new NodoQuad(val));
        return true;

    } else if (this->hijoInfDer == nullptr && val.x > this->dato.x && val.y <= this->dato.y) {
        this->fijarHijoInfDer(new NodoQuad(val));
        return true;

    } else if (this->hijoInfIzq == nullptr && val.x < this->dato.x && val.y < this->dato.y) {
        this->fijarHijoInfIzq(new NodoQuad(val));
        return true;

    } else {
        if (val.x < this->dato.x && val.y > this->dato.y) {
            return this->hijoSupIzq->insertar(val);

        } else if (val.x > this->dato.x && val.y > this->dato.y) {
            return this->hijoSupDer->insertar(val);
            
        } else if (val.x > this->dato.x && val.y < this->dato.y) {
            return this->hijoInfDer->insertar(val);
            
        } else if (val.x < this->dato.x && val.y < this->dato.y) {
            return this->hijoInfIzq->insertar(val);

        }
    }
    return false;
}

void NodoQuad::preOrden() {
    cout << this->dato << " ";
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
    cout << this->dato << " ";
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
    cout << this->dato << " ";
}

void NodoQuad::nivelOrden() {
    queue<NodoQuad*> cola;
    cola.push(this);
    while (!cola.empty()) {
        NodoQuad* nodo = cola.front();
        cola.pop();
        cout << nodo->dato << " ";
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