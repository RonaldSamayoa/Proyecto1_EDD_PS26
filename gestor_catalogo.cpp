//
// Created by ronald on 11/3/26.
//
#include "include/gestor_catalogo.h"
#include <iostream>

// constructor
GestorCatalogo::GestorCatalogo(int capacidadHash, int gradoB)
    : hash(capacidadHash), arbolB(gradoB), arbolBPlus(gradoB) {
    //inicializar lista ordenada por nombre
    listaOrdenada = new ListaOrdenada<Producto *>(compararNombreOrden);
}

// insertar en todas las estructuras
bool GestorCatalogo::insertarProducto(Producto* producto){

    // insertar en lista base
    lista.insertarFinal(producto);

    //lista ordenada
    listaOrdenada->insertar(producto);

    // insertar en estructuras
    avl.insertar(producto);
    hash.insertar(producto);
    arbolB.insertar(producto);
    arbolBPlus.insertar(producto);

    return true;
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

ListaEnlazada<Producto*> GestorCatalogo::buscarPorRango(std::string inicio, std::string fin){
    return arbolB.buscarRango(inicio, fin);
}

// ===== ELIMINACION =====

void GestorCatalogo::eliminarProducto(std::string nombre){

    // buscar el producto en el AVL
    Producto* producto = avl.buscar(nombre);

    if(producto == nullptr){
        std::cout << "Producto no encontrado\n";
        return;
    }

    // eliminar de AVL
    avl.eliminar(nombre);

    // eliminar de Hash (codigo)
    hash.eliminar(producto->codigo_barra);

    // eliminar de Arbol B (fecha)
    arbolB.eliminar(producto->fecha_caducidad);

    arbolBPlus.eliminar(producto->categoria, nombre);

    // eliminar de lista enlazada
    lista.eliminar([](Producto* a, Producto* b){
        return a->nombre == b->nombre;
    }, producto);

    // eliminar de lista ordenada
    listaOrdenada->eliminar([](Producto* a, Producto* b){
        return a->nombre == b->nombre;
    }, producto);

    std::cout << "Producto eliminado correctamente\n";
}

void imprimirProducto(Producto* p){
    std::cout << p->nombre << std::endl;
}

void GestorCatalogo::listarTodos(){
    // recorre la lista base (orden de insercion)
    lista.recorrer(imprimirProducto);
}

void GestorCatalogo::listarOrdenado(){
    listaOrdenada->recorrer(imprimirProducto);
}