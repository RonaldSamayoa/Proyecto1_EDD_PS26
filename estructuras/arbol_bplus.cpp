//
// Created by ronald on 11/3/26.
//
#include "../include/estructuras/arbol_bplus.h"

// constructor del arbol B+
ArbolBPlus::ArbolBPlus(int t){
    this->t = t;
    raiz = nullptr; // inicialmente el arbol esta vacio
}

// busca la hoja donde deberia estar una categoria
NodoBPlus* ArbolBPlus::buscarHoja(NodoBPlus* nodo, std::string categoria){

    // si ya es hoja, devolvemos directamente
    if(nodo->hoja)
        return nodo;

    int i = 0;

    // encontrar el hijo adecuado segun la categoria
    while(i < nodo->n && categoria > nodo->claves[i]){
        i++;
    }

    // bajar recursivamente al hijo correspondiente
    return buscarHoja(nodo->hijos[i], categoria);
}

// inserta un producto
void ArbolBPlus::insertar(Producto* producto){

    // arbol vacio → crear raiz hoja
    if(raiz == nullptr){

        raiz = new NodoBPlus(t, true);

        raiz->claves[0] = producto->categoria;
        raiz->datos[0] = new ListaEnlazada<Producto*>();
        raiz->datos[0]->insertarFinal(producto);

        raiz->n = 1;
        return;
    }

    std::string nuevaClave;       // clave que sube si hay split
    NodoBPlus* nuevoNodo = nullptr; // nuevo nodo creado por split

    // insercion recursiva
    insertarNoLleno(raiz, producto, nuevaClave, nuevoNodo);

    // si la raiz se dividio, crear nueva raiz
    if(nuevoNodo != nullptr){

        NodoBPlus* nuevaRaiz = new NodoBPlus(t, false);

        nuevaRaiz->claves[0] = nuevaClave;
        nuevaRaiz->hijos[0] = raiz;
        nuevaRaiz->hijos[1] = nuevoNodo;

        nuevaRaiz->n = 1;

        raiz = nuevaRaiz;
    }
}

// busca todos los productos de una categoria
ListaEnlazada<Producto*>* ArbolBPlus::buscarCategoria(std::string categoria){

    if(raiz == nullptr)
        return nullptr;

    // encontrar hoja donde deberia estar
    NodoBPlus* hoja = buscarHoja(raiz, categoria);

    // buscar dentro de la hoja
    for(int i = 0; i < hoja->n; i++){

        if(hoja->claves[i] == categoria){
            return hoja->datos[i]; // devolvemos la lista completa
        }
    }

    return nullptr; // no existe la categoria
}

// divide una hoja en dos cuando esta llena
void ArbolBPlus::dividirHoja(NodoBPlus* hoja, std::string& nuevaClave, NodoBPlus*& nuevaHoja){

    // crear nueva hoja
    nuevaHoja = new NodoBPlus(t, true);

    // punto medio de division
    int mitad = t;

    // copiar la mitad derecha a la nueva hoja
    for(int i = mitad, j = 0; i < hoja->n; i++, j++){
        nuevaHoja->claves[j] = hoja->claves[i];
        nuevaHoja->datos[j] = hoja->datos[i];
        nuevaHoja->n++;
    }

    // ajustar tamanio de la hoja original
    hoja->n = mitad;

    // enlazar hojas
    nuevaHoja->siguiente = hoja->siguiente;
    hoja->siguiente = nuevaHoja;

    // la clave que se sube es la primera de la nueva hoja
    nuevaClave = nuevaHoja->claves[0];
}

void ArbolBPlus::insertarNoLleno(NodoBPlus* nodo, Producto* producto, std::string& nuevaClave, NodoBPlus*& nuevoNodo){

    // CASO 1: nodo hoja
    if(nodo->hoja){

        // buscar si ya existe la categoria
        for(int i = 0; i < nodo->n; i++){
            if(nodo->claves[i] == producto->categoria){
                nodo->datos[i]->insertarFinal(producto);
                nuevoNodo = nullptr;
                return;
            }
        }

        // insertar normalmente
        int i = nodo->n - 1;

        while(i >= 0 && producto->categoria < nodo->claves[i]){
            nodo->claves[i+1] = nodo->claves[i];
            nodo->datos[i+1] = nodo->datos[i];
            i--;
        }

        nodo->claves[i+1] = producto->categoria;
        nodo->datos[i+1] = new ListaEnlazada<Producto*>();
        nodo->datos[i+1]->insertarFinal(producto);

        nodo->n++;

        // si no hay desbordamiento terminamos
        if(nodo->n < 2*t){
            nuevoNodo = nullptr;
            return;
        }

        // SPLIT DE HOJA
        dividirHoja(nodo, nuevaClave, nuevoNodo);
        return;
    }

    // CASO 2: nodo interno
    int i = nodo->n - 1;

    // buscar hijo adecuado
    while(i >= 0 && producto->categoria < nodo->claves[i]){
        i--;
    }
    i++;

    std::string claveSube;
    NodoBPlus* nuevoHijo = nullptr;

    // insertar recursivamente en hijo
    insertarNoLleno(nodo->hijos[i], producto, claveSube, nuevoHijo);

    // si no hubo split en el hijo no hay nada que hacer
    if(nuevoHijo == nullptr){
        nuevoNodo = nullptr;
        return;
    }

    // buscar posicion correcta para insertar la clave subida
    int pos = i;

    while(pos < nodo->n && nodo->claves[pos] < claveSube){
        pos++;
    }

    // mover claves e hijos para abrir espacio
    for(int j = nodo->n; j > pos; j--){
        nodo->claves[j] = nodo->claves[j-1];
        nodo->hijos[j+1] = nodo->hijos[j];
    }

    // insertar nueva clave y nuevo hijo
    nodo->claves[pos] = claveSube;
    nodo->hijos[pos+1] = nuevoHijo;

    nodo->n++;

    // si no hay desbordamiento
    if(nodo->n < 2*t){
        nuevoNodo = nullptr;
        return;
    }
}