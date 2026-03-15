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

    // funcion hash que convierte el codigo de barras en un indice
    int funcionHash(std::string codigo);

    // funcion auxiliar para comparar productos por codigo de barras
    static bool compararCodigo(Producto* a, Producto* b);

public:

    // constructor
    TablaHash(int capacidad);

    // destructor
    ~TablaHash();

    // insertar producto en la tabla
    void insertar(Producto* producto);

    // buscar producto por codigo de barras
    Producto* buscar(std::string codigo);

    // eliminar producto por codigo de barras
    bool eliminar(std::string codigo);

};
#endif //PROYECTO1_TABLA_HASH_H