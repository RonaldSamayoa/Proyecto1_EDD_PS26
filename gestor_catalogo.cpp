//
// Created by ronald on 11/3/26.
//
#include "include/gestor_catalogo.h"

// constructor
GestorCatalogo::GestorCatalogo(int capacidadHash, int gradoB)
    : hash(capacidadHash), arbolB(gradoB), arbolBPlus(gradoB) {
}

// insertar en todas las estructuras
bool GestorCatalogo::insertarProducto(Producto* producto){

    // insertar en lista base
    lista.insertarFinal(producto);

    // insertar en estructuras
    avl.insertar(producto);
    hash.insertar(producto);
    arbolB.insertar(producto);
    arbolBPlus.insertar(producto);

    return true; // luego puedes manejar errores
}

// ===== BUSQUEDAS =====

Producto* GestorCatalogo::buscarPorNombre(std::string nombre){
    return avl.buscar(nombre);
}

Producto* GestorCatalogo::buscarPorCodigo(std::string codigo){
    return hash.buscar(codigo);
}

Producto* GestorCatalogo::buscarPorFecha(std::string fecha){
    return arbolB.buscar(fecha);
}

ListaEnlazada<Producto*>* GestorCatalogo::buscarPorCategoria(std::string categoria){
    return arbolBPlus.buscarCategoria(categoria);
}

// ===== ELIMINACION =====

void GestorCatalogo::eliminarProducto(std::string nombre){

    // eliminar del AVL (principal)
    avl.eliminar(nombre);

}