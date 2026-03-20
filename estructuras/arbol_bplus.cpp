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

    // si el arbol esta vacio se crea la raiz como hoja
    if(raiz == nullptr){

        raiz = new NodoBPlus(t, true);

        // primera clave
        raiz->claves[0] = producto->categoria;

        // crear lista para esa categoria
        raiz->datos[0] = new ListaEnlazada<Producto*>();
        raiz->datos[0]->insertarFinal(producto);

        raiz->n = 1;

        return;
    }

    // buscar hoja donde insertar
    NodoBPlus* hoja = buscarHoja(raiz, producto->categoria);

    // verificar si la categoria ya existe
    for(int i = 0; i < hoja->n; i++){

        if(hoja->claves[i] == producto->categoria){

            // ya existe -> solo agregamos a la lista
            hoja->datos[i]->insertarFinal(producto);
            return;
        }
    }

    // si no existe, insertamos nueva clave (sin split aun)
    int i = hoja->n - 1;

    // mover claves mayores hacia la derecha para mantener orden
    while(i >= 0 && producto->categoria < hoja->claves[i]){

        hoja->claves[i + 1] = hoja->claves[i];
        hoja->datos[i + 1] = hoja->datos[i];

        i--;
    }

    // insertar nueva categoria
    hoja->claves[i + 1] = producto->categoria;

    // crear nueva lista para esa categoria
    hoja->datos[i + 1] = new ListaEnlazada<Producto*>();
    hoja->datos[i + 1]->insertarFinal(producto);

    hoja->n++;
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