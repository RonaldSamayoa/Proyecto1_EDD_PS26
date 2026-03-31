//
// Created by ronald on 11/3/26.
//
#ifndef PROYECTO1_GESTOR_CATALOGO_H
#define PROYECTO1_GESTOR_CATALOGO_H
#include "producto.h"

// estructuras
#include "estructuras/arbol_avl.h"
#include "estructuras/tabla_hash.h"
#include "estructuras/arbol_b.h"
#include "estructuras/arbol_bplus.h"
#include "estructuras/lista_enlazada.h"
#include "estructuras/lista_ordenada.h"

class GestorCatalogo {

private:

    ArbolAVL avl;                          // busqueda por nombre
    TablaHash hash;                        // busqueda por codigo
    ArbolB arbolB;                         // busqueda por fecha
    ArbolBPlus arbolBPlus;                 // busqueda por categoria
    ListaEnlazada<Producto*> lista;        // base de datos general
    ListaOrdenada<Producto*>* listaOrdenada; // lista ordenada por nombre

public:

    // constructor
    GestorCatalogo(int capacidadHash, int gradoB);

    // insertar producto en TODAS las estructuras
    bool insertarProducto(Producto* producto);

    // busquedas
    Producto* buscarPorNombre(std::string nombre);
    Producto* buscarPorCodigo(std::string codigo);
    Producto* buscarPorFecha(std::string fecha);
    ListaEnlazada<Producto*>* buscarPorCategoria(std::string categoria);
    ListaEnlazada<Producto*> buscarPorRango(std::string inicio, std::string fin);
    // comparacion de busqueda (lista vs AVL)
    void compararBusqueda(std::string nombre);
    ArbolAVL& obtenerAVL();
    ArbolB& obtenerArbolB();
    ArbolBPlus& obtenerArbolBPlus();
    void listarTodos();
    void listarOrdenado();

    // eliminar
    void eliminarProducto(std::string nombre);

    // valida producto antes de insertar
    bool validarProducto(Producto* p, std::string& error);

};
#endif //PROYECTO1_GESTOR_CATALOGO_H