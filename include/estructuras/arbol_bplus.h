//
// Created by ronald on 11/3/26.
//
#ifndef PROYECTO1_ARBOL_BPLUS_H
#define PROYECTO1_ARBOL_BPLUS_H
#include "../producto.h"
#include "lista_enlazada.h"
#include <string>

// nodo del arbol B+
class NodoBPlus{

public:
    bool hoja; // indica si es hoja o nodo interno

    std::string* claves; // categorias (ordenadas)
    NodoBPlus** hijos;   // hijos (solo para nodos internos)

    // en hojas: lista de productos por categoria
    ListaEnlazada<Producto*>** datos;

    int n; // cantidad actual de claves
    int t; // grado minimo

    NodoBPlus* siguiente; // enlace a la siguiente hoja (clave en B+)

    // constructor
    NodoBPlus(int t, bool hoja){
        this->t = t;
        this->hoja = hoja;

        // maximo 2t - 1 claves
        claves = new std::string[2*t - 1];

        // maximo 2t hijos
        hijos = new NodoBPlus*[2*t];

        // solo se usa en hojas
        datos = new ListaEnlazada<Producto*>*[2*t - 1];

        n = 0;
        siguiente = nullptr;
    }
};

// ARBOL B+
class ArbolBPlus{
private:
    NodoBPlus* raiz;
    int t;

    // buscar hoja donde pertenece una categoria
    NodoBPlus* buscarHoja(NodoBPlus* nodo, std::string categoria);

    void dividirHoja(NodoBPlus* hoja, std::string& nuevaClave, NodoBPlus*& nuevaHoja);
    // insercion interna
   void insertarNoLleno(NodoBPlus* nodo, Producto* producto, std::string& nuevaClave, NodoBPlus*& nuevoNodo);
    void dividirNodoInterno(NodoBPlus* nodo, std::string& nuevaClave, NodoBPlus*& nuevoNodo);
    // eliminacion completa (recursiva)
    bool eliminarRec(NodoBPlus* nodo, std::string categoria, std::string nombre);

    // fusion de nodos
    void fusionar(NodoBPlus* nodo, NodoBPlus* hermano, NodoBPlus* padre, int indice);

    void manejarSubdesbordamiento(NodoBPlus* nodo, NodoBPlus* padre, int indice);

public:
    ArbolBPlus(int t);

    void insertar(Producto* producto);

    // retorna todos los productos de una categoria
    ListaEnlazada<Producto*>* buscarCategoria(std::string categoria);

    // recorre todas las categorias (hojas) en orden
    void recorrerCategorias();

    // eliminar producto por categoria y nombre
    bool eliminar(std::string categoria, std::string nombre);
};

#endif //PROYECTO1_ARBOL_BPLUS_H