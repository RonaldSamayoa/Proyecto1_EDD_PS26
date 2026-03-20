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

        raiz->claves[0] = producto->categoria;

        // crear lista para esa categoria
        raiz->datos[0] = new ListaEnlazada<Producto*>();
        raiz->datos[0]->insertarFinal(producto);

        raiz->n = 1;
        return;
    }

    // CASO ESPECIAL: si la raiz esta llena
    if(raiz->n == 2*t - 1){

        // solo manejamos cuando la raiz es hoja (por ahora)
        if(raiz->hoja){

            std::string nuevaClave;
            NodoBPlus* nuevaHoja;

            // dividir la raiz
            dividirHoja(raiz, nuevaClave, nuevaHoja);

            // crear nueva raiz (ahora es nodo interno)
            NodoBPlus* nuevaRaiz = new NodoBPlus(t, false);

            // la clave que sube al padre
            nuevaRaiz->claves[0] = nuevaClave;

            // enlazar hijos
            nuevaRaiz->hijos[0] = raiz;
            nuevaRaiz->hijos[1] = nuevaHoja;

            nuevaRaiz->n = 1;

            // actualizar raiz
            raiz = nuevaRaiz;
        }
    }

    // buscar hoja donde insertar (despues del posible split)
    NodoBPlus* hoja = buscarHoja(raiz, producto->categoria);

    // verificar si la categoria ya existe
    for(int i = 0; i < hoja->n; i++){

        if(hoja->claves[i] == producto->categoria){

            hoja->datos[i]->insertarFinal(producto);
            return;
        }
    }

    // insertar nueva categoria en la hoja
    int i = hoja->n - 1;

    // desplazar claves mayores para mantener orden
    while(i >= 0 && producto->categoria < hoja->claves[i]){

        hoja->claves[i + 1] = hoja->claves[i];
        hoja->datos[i + 1] = hoja->datos[i];

        i--;
    }

    // insertar clave
    hoja->claves[i + 1] = producto->categoria;

    // crear lista para la categoria
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

    // reducir tamaño de la hoja original
    hoja->n = mitad;

    // enlazar hojas (MUY IMPORTANTE en B+)
    nuevaHoja->siguiente = hoja->siguiente;
    hoja->siguiente = nuevaHoja;

    // la clave que se sube es la primera de la nueva hoja
    nuevaClave = nuevaHoja->claves[0];
}