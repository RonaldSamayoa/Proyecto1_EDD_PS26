//
// Created by ronald on 11/3/26.
//
#include "../include/utilidades/generador_dot.h"
#include <fstream>
#include <iostream>

// funcion auxiliar recursiva para recorrer el arbol AVL
void recorrerAVL(std::ofstream& archivo, NodoAVL* nodo){
    // caso base: nodo nulo
    if(nodo == nullptr)
        return;

    // ===== CREAR NODO =====
    // usamos la direccion de memoria como identificador unico
    archivo << "\"" << nodo << "\" [label=\""
            << nodo->producto->nombre << "\"];\n";

    // ===== HIJO IZQUIERDO =====
    if(nodo->izquierda != nullptr){

        // crear conexion
        archivo << "\"" << nodo << "\" -> \"" << nodo->izquierda << "\";\n";

        // recorrer recursivamente
        recorrerAVL(archivo, nodo->izquierda);
    }

    // ===== HIJO DERECHO =====
    if(nodo->derecha != nullptr){

        archivo << "\"" << nodo << "\" -> \"" << nodo->derecha << "\";\n";

        recorrerAVL(archivo, nodo->derecha);
    }
}

// genera archivo .dot del arbol AVL
void GeneradorDOT::generarAVL(ArbolAVL& arbol, std::string nombreArchivo){
    std::ofstream archivo(nombreArchivo);

    if(!archivo.is_open()){
        return;
    }

    // encabezado de Graphviz
    archivo << "digraph AVL {\n";
    archivo << "node [shape=record];\n";

    // obtener raiz
    NodoAVL* raiz = arbol.obtenerRaiz();

    // recorrer arbol
    recorrerAVL(archivo, raiz);

    archivo << "}\n";

    archivo.close();
}

// funcion auxiliar para recorrer el arbol B
void recorrerB(std::ofstream& archivo, NodoB* nodo){
    // caso base
    if(nodo == nullptr)
        return;

    // ===== CREAR ETIQUETA DEL NODO =====
    // un nodo B puede tener varias claves, las mostramos separadas por |
    std::string label = "";

    for(int i = 0; i < nodo->n; i++){

        // usamos la fecha como identificador visual
        label += nodo->claves[i]->fecha_caducidad;

        if(i < nodo->n - 1)
            label += " | ";
    }

    // escribir nodo en DOT
    archivo << "\"" << nodo << "\" [label=\"" << label << "\"];\n";

    // ===== RECORRER HIJOS =====
    if(!nodo->hoja){

        for(int i = 0; i <= nodo->n; i++){

            if(nodo->hijos[i] != nullptr){

                // crear conexion padre -> hijo
                archivo << "\"" << nodo << "\" -> \"" << nodo->hijos[i] << "\";\n";

                // llamada recursiva
                recorrerB(archivo, nodo->hijos[i]);
            }
        }
    }
}

// genera archivo .dot del arbol B
void GeneradorDOT::generarB(ArbolB& arbol, std::string nombreArchivo){
    std::ofstream archivo(nombreArchivo);

    if(!archivo.is_open()){
        return;
    }

    archivo << "digraph BTree {\n";
    archivo << "node [shape=record];\n";

    // obtener raiz
    NodoB* raiz = arbol.obtenerRaiz();

    // recorrer todo el arbol
    recorrerB(archivo, raiz);

    archivo << "}\n";
    archivo.close();
}

// funcion recursiva para recorrer el arbol B+
void recorrerBPlus(std::ofstream& archivo, NodoBPlus* nodo){

    if(nodo == nullptr)
        return;

    // ===== CREAR NODO =====
    archivo << "\"" << nodo << "\" [label=\"";

    // mostrar todas las claves del nodo
    for(int i = 0; i < nodo->n; i++){
        archivo << nodo->claves[i];

        if(i < nodo->n - 1)
            archivo << " | ";
    }

    archivo << "\"];\n";

    // ===== SI NO ES HOJA, CONECTAR HIJOS =====
    if(!nodo->hoja){

        for(int i = 0; i <= nodo->n; i++){

            if(nodo->hijos[i] != nullptr){

                // crear conexion
                archivo << "\"" << nodo << "\" -> \"" << nodo->hijos[i] << "\";\n";

                // recorrer hijo
                recorrerBPlus(archivo, nodo->hijos[i]);
            }
        }
    }
}

void GeneradorDOT::generarBPlus(ArbolBPlus& arbol, std::string nombreArchivo){

    std::ofstream archivo(nombreArchivo);

    if(!archivo.is_open()){
        std::cout << "Error al crear archivo B+\n";
        return;
    }

    archivo << "digraph BPlus {\n";
    archivo << "node [shape=record];\n";

    // obtener raiz
    NodoBPlus* raiz = arbol.obtenerRaiz();

    // recorrer arbol
    recorrerBPlus(archivo, raiz);

    archivo << "}\n";
    archivo.close();
}