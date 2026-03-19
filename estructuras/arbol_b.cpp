//
// Created by ronald on 11/3/26.
//
#include "../include/estructuras/arbol_b.h"

// constructor del arbol B
ArbolB::ArbolB(int t){
    this->t = t;

    // inicialmente el arbol esta vacio
    raiz = nullptr;
}

// inserta un producto en el arbol B
void ArbolB::insertar(Producto* producto){
    // si el arbol esta vacio se crea la raiz
    if(raiz == nullptr){

        raiz = new NodoB(t, true); // nodo hoja
        raiz->claves[0] = producto; // primera clave
        raiz->n = 1;
        return;
    }

    // si la raiz esta llena se debe dividir
    if(raiz->n == 2*t - 1){

        // crear nueva raiz
        NodoB* nuevaRaiz = new NodoB(t, false);

        // la antigua raiz pasa a ser hijo
        nuevaRaiz->hijos[0] = raiz;

        // dividir la raiz
        dividirHijo(nuevaRaiz, 0, raiz);

        // decidir a que hijo bajar
        int i = 0;
        if(producto->fecha_caducidad > nuevaRaiz->claves[0]->fecha_caducidad)
            i++;

        insertarNoLleno(nuevaRaiz->hijos[i], producto);

        // actualizar raiz
        raiz = nuevaRaiz;
    }
    else{
        // si no esta llena, insertar directamente
        insertarNoLleno(raiz, producto);
    }
}

// inserta en un nodo que no esta lleno
void ArbolB::insertarNoLleno(NodoB* nodo, Producto* producto){

    int i = nodo->n - 1;

    // CASO HOJA
    if(nodo->hoja){

        // mover claves mayores hacia la derecha para abrir espacio a la nueva clave
        while(i >= 0 &&
              producto->fecha_caducidad < nodo->claves[i]->fecha_caducidad){

            nodo->claves[i+1] = nodo->claves[i];
            i--;
              }

        // insertar en la posicion correcta
        nodo->claves[i+1] = producto;

        nodo->n++;
    }
    else{
        // buscar el hijo donde debe ir el producto
        while(i >= 0 &&
              producto->fecha_caducidad < nodo->claves[i]->fecha_caducidad){
            i--;
              }

        i++; // posicion del hijo

        // si el hijo esta lleno hay que dividirlo
        if(nodo->hijos[i]->n == 2*t - 1){

            dividirHijo(nodo, i, nodo->hijos[i]);

            // decidir si ir al hijo izquierdo o derecho despues del split
            if(producto->fecha_caducidad > nodo->claves[i]->fecha_caducidad)
                i++;
        }

        insertarNoLleno(nodo->hijos[i], producto);
    }
}

// divide un nodo hijo que esta lleno
void ArbolB::dividirHijo(NodoB* padre, int indice, NodoB* hijo){

    // crear nuevo nodo que almacenara la mitad derecha
    NodoB* nuevo = new NodoB(t, hijo->hoja);

    // el nuevo nodo tendra t-1 claves
    nuevo->n = t - 1;

    // copiar las ultimas (t-1) claves al nuevo nodo
    for(int j = 0; j < t-1; j++){
        nuevo->claves[j] = hijo->claves[j + t];
    }

    // si no es hoja, copiar tambien los hijos
    if(!hijo->hoja){
        for(int j = 0; j < t; j++){
            nuevo->hijos[j] = hijo->hijos[j + t];
        }
    }

    // reducir numero de claves del hijo original
    hijo->n = t - 1;

    // mover los hijos del padre para hacer espacio
    for(int j = padre->n; j >= indice + 1; j--){
        padre->hijos[j + 1] = padre->hijos[j];
    }

    // enlazar el nuevo hijo
    padre->hijos[indice + 1] = nuevo;

    // mover claves del padre para hacer espacio
    for(int j = padre->n - 1; j >= indice; j--){
        padre->claves[j + 1] = padre->claves[j];
    }

    // subir la clave central al padre
    padre->claves[indice] = hijo->claves[t - 1];

    padre->n++;
}

// buscar producto por fecha
Producto* ArbolB::buscarRec(NodoB* nodo, std::string fecha){

    int i = 0;

    // encontrar la primera clave >= fecha
    while(i < nodo->n && fecha > nodo->claves[i]->fecha_caducidad){
        i++;
    }

    // si encontramos la clave
    if(i < nodo->n && fecha == nodo->claves[i]->fecha_caducidad){
        return nodo->claves[i];
    }

    // si es hoja no existe
    if(nodo->hoja)
        return nullptr;

    // bajar al hijo correspondiente
    return buscarRec(nodo->hijos[i], fecha);
}

// funcion publica
Producto* ArbolB::buscar(std::string fecha){

    if(raiz == nullptr)
        return nullptr;

    return buscarRec(raiz, fecha);
}