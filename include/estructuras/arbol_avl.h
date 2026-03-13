//
// Created by ronald on 11/3/26.
//

#ifndef PROYECTO1_ARBOL_AVL_H
#define PROYECTO1_ARBOL_AVL_H
#include "../producto.h"
#include <string>

class NodoAVL {
public:
    Producto* producto;

    NodoAVL* izquierda;
    NodoAVL* derecha;

    int altura;

    NodoAVL(Producto* p);
};

//Clase para arbol avl
class ArbolAVL {
private:
    NodoAVL* raiz;
    int altura(NodoAVL* nodo);
    int maximo(int a, int b);
    int factorBalance(NodoAVL* nodo);

    NodoAVL* rotacionII(NodoAVL* y);
    NodoAVL* rotacionDD(NodoAVL* x);
    NodoAVL* rotacionID(NodoAVL* nodo);
    NodoAVL* rotacionDI(NodoAVL* nodo);

    NodoAVL* insertarRec(NodoAVL* nodo, Producto* producto);
    NodoAVL* eliminarRec(NodoAVL* nodo, std::string nombre);

    NodoAVL* nodoMinimo(NodoAVL* nodo);

    Producto* buscarRec(NodoAVL* nodo, std::string nombre);

    void inorderRec(NodoAVL* nodo);

public:

    ArbolAVL();

    void insertar(Producto* producto);

    void eliminar(std::string nombre);

    Producto* buscar(std::string nombre);

    void inorder();
};
#endif //PROYECTO1_ARBOL_AVL_H