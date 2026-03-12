//
// Created by ronald on 11/3/26.
//

#ifndef PROYECTO1_TABLA_HASH_H
#define PROYECTO1_TABLA_HASH_H
#include "lista_enlazada.h"
#include <string>
#include "../producto.h"

// tabla hash para almacenar productos usando codigo de barras como clave
class TablaHash{

private:

    // arreglo de listas enlazadas para manejar colisiones
    ListaEnlazada<Producto*>** tabla;

    // tamaño del arreglo
    int capacidad;

public:
    // constructor
    TablaHash(int capacidad){

        // guardar capacidad
        this->capacidad = capacidad;

        // crear arreglo de listas
        tabla = new ListaEnlazada<Producto*>*[capacidad];

        // inicializar cada posicion
        for(int i = 0; i < capacidad; i++){
            tabla[i] = new ListaEnlazada<Producto*>();
        }
    }

    // funcion hash que convierte el codigo de barras en un indice
    int funcionHash(std::string codigo){
        int suma = 0;
        // recorrer caracteres del codigo
        for(char c : codigo){
            suma = suma * 31 + c; // sumar valor ascii
        }

        // obtener posicion dentro del arreglo
        return suma % capacidad;
    }

    // insertar producto en la tabla
    void insertar(Producto* producto){

        // calcular indice hash
        int indice = funcionHash(producto->codigo_barra);

        // insertar producto en lista correspondiente
        tabla[indice]->insertarInicio(producto);
    }

    // buscar producto por codigo de barras
    Producto* buscar(std::string codigo){
        int indice = funcionHash(codigo);

        NodoLista<Producto*>* actual = tabla[indice]->obtenerCabeza();

        while(actual != nullptr){
            if(actual->dato->codigo_barra == codigo){
                return actual->dato;
            }
            actual = actual->siguiente;
        }
        return nullptr;
    }

};
#endif //PROYECTO1_TABLA_HASH_H