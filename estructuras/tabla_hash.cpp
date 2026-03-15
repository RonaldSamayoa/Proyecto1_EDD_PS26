//
// Created by ronald on 11/3/26.
//
#include "../include/estructuras/tabla_hash.h"

// constructor de la tabla hash
TablaHash::TablaHash(int capacidad){

    this->capacidad = capacidad;

    // crear arreglo de listas
    tabla = new ListaEnlazada<Producto*>*[capacidad];

    // inicializar cada posicion con una lista vacia
    for(int i = 0; i < capacidad; i++){
        tabla[i] = new ListaEnlazada<Producto*>();
    }
}

// destructor de la tabla hash
TablaHash::~TablaHash(){
    // liberar cada lista
    for(int i = 0; i < capacidad; i++){
        delete tabla[i];
    }
    // liberar el arreglo de listas
    delete[] tabla;
}

// transforma el codigo de barras en un indice del arreglo
int TablaHash::funcionHash(std::string codigo){

    int suma = 0;

    // recorrer caracteres del codigo
    for(char c : codigo){
        suma = suma * 31 + c;
    }

    // obtener posicion dentro del arreglo
    return suma % capacidad;
}

// insertar producto en la tabla
void TablaHash::insertar(Producto* producto){

    // calcular indice hash
    int indice = funcionHash(producto->codigo_barra);

    // insertar producto en la lista correspondiente
    tabla[indice]->insertarInicio(producto);
}

// buscar producto por codigo de barras
Producto* TablaHash::buscar(std::string codigo){

    int indice = funcionHash(codigo);

    // recorrer la lista del indice calculado
    NodoLista<Producto*>* actual = tabla[indice]->obtenerCabeza();

    while(actual != nullptr){

        // comparar codigo de barras
        if(actual->dato->codigo_barra == codigo){
            return actual->dato;
        }

        actual = actual->siguiente;
    }

    return nullptr;
}

//funcion auxiliar para comparar productos, se usa en la eliminacion de la lista enlazada
bool TablaHash::compararCodigo(Producto* a, Producto* b){

    return a->codigo_barra == b->codigo_barra;
}

// eliminar producto de la tabla hash
bool TablaHash::eliminar(std::string codigo){

    int indice = funcionHash(codigo);

    // crear producto temporal solo para usar como clave
    Producto* clave = new Producto();
    clave->codigo_barra = codigo;

    // eliminar usando la funcion eliminar de la lista enlazada
    bool eliminado = tabla[indice]->eliminar(compararCodigo, clave);

    delete clave;

    return eliminado;
}
