//
// Created by ronald on 11/3/26.
//

#ifndef PROYECTO1_LISTA_ORDENADA_H
#define PROYECTO1_LISTA_ORDENADA_H
#include "lista_enlazada.h"

// lista generica que mantiene sus elementos ordenados
template<typename T>
class ListaOrdenada{

private:

    // primer nodo de la lista
    NodoLista<T>* cabeza;

    // cantidad de elementos
    int tamanio;

    // funcion que define el criterio de orden
    bool (*comparar)(T,T);

public:

    // constructor
    ListaOrdenada(bool (*comparar)(T,T)){

        // al inicio la lista esta vacia
        cabeza = nullptr;

        // no hay elementos
        tamanio = 0;

        // guardamos el criterio de orden
        this->comparar = comparar;
    }

    // insertar manteniendo orden
    void insertar(T dato){

        // crear nodo nuevo
        NodoLista<T>* nuevo = new NodoLista<T>(dato);

        // caso 1: lista vacia
        if(cabeza == nullptr){

            cabeza = nuevo;
            tamanio++;
            return;
        }

        // caso 2: insertar al inicio
        if(comparar(dato, cabeza->dato)){

            nuevo->siguiente = cabeza;
            cabeza = nuevo;

            tamanio++;
            return;
        }

        // recorrer lista para encontrar posicion
        NodoLista<T>* actual = cabeza;

        while(actual->siguiente != nullptr &&
              !comparar(dato, actual->siguiente->dato)){

            actual = actual->siguiente;
              }

        // insertar nodo
        nuevo->siguiente = actual->siguiente;
        actual->siguiente = nuevo;

        tamanio++;
    }

    // recorrer lista
    void recorrer(void (*funcion)(T)){

        NodoLista<T>* actual = cabeza;

        while(actual != nullptr){

            funcion(actual->dato);
            actual = actual->siguiente;
        }
    }

    // obtener tamaño
    int obtenerTamanio(){
        return tamanio;
    }

    // verificar si esta vacia
    bool estaVacia(){
        return cabeza == nullptr;
    }

};
#endif //PROYECTO1_LISTA_ORDENADA_H