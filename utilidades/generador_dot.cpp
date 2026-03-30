//
// Created by ronald on 11/3/26.
//
#include "../include/utilidades/generador_dot.h"
#include <fstream>

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