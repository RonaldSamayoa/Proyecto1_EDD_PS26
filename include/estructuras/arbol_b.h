//
// Created by ronald on 11/3/26.
//

#ifndef PROYECTO1_ARBOL_B_H
#define PROYECTO1_ARBOL_B_H
#include "../producto.h"
#include "lista_enlazada.h"

// nodo del arbol B
class NodoB{

public:

    Producto** claves; //productos (ordenados por fecha)
    NodoB** hijos;  //punteros a hijos

    int n;  // numero actual de claves en el nodo
    bool hoja; // indica si el nodo es hoja
    int t; // grado minimo del arbol (define capacidad)

    // constructor
    NodoB(int t, bool hoja){
        this->t = t;
        this->hoja = hoja;

        // reservar memoria para claves (maximo 2t - 1)
        claves = new Producto*[2*t - 1];

        // reservar memoria para hijos (maximo 2t)
        hijos = new NodoB*[2*t];

        // inicialmente no hay claves
        n = 0;
    }
};

// ARBOL B
class ArbolB{

private:
    NodoB* raiz; // nodo raiz
    int t;       // grado minimo

    void insertarNoLleno(NodoB* nodo, Producto* producto);
    void dividirHijo(NodoB* padre, int indice, NodoB* hijo);
    Producto* buscarRec(NodoB* nodo, std::string fecha);
    void buscarRangoRec(NodoB* nodo, std::string inicio, std::string fin, ListaEnlazada<Producto*>& resultado);

    void eliminarRec(NodoB* nodo, std::string fecha);
    int encontrarClave(NodoB* nodo, std::string fecha);

    void eliminarDeHoja(NodoB* nodo, int idx);
    void eliminarDeInterno(NodoB* nodo, int idx);

    Producto* obtenerPredecesor(NodoB* nodo, int idx);
    Producto* obtenerSucesor(NodoB* nodo, int idx);

    void llenar(NodoB* nodo, int idx);

    void pedirPrestadoIzq(NodoB* nodo, int idx);
    void pedirPrestadoDer(NodoB* nodo, int idx);

    void fusionar(NodoB* nodo, int idx);

public:
    ArbolB(int t);

    void insertar(Producto* producto);

    Producto* buscar(std::string fecha);
    ListaEnlazada<Producto*> buscarRango(std::string inicio, std::string fin);
    void eliminar(std::string fecha);
};

#endif //PROYECTO1_ARBOL_B_H