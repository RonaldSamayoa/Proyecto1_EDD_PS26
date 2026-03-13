//
// Created by ronald on 11/3/26.
//
#include "../include/estructuras/arbol_avl.h"
// constructor del nodo AVL
// inicializa los punteros de hijos en nullptr
NodoAVL::NodoAVL(Producto* p){
    producto = p;
    izquierda = nullptr;
    derecha = nullptr;
    altura = 1; // nodo nuevo inicia como hoja
}

// constructor del arbol
ArbolAVL::ArbolAVL(){
    raiz = nullptr;
}

// devuelve la altura de un nodo
// si el nodo no existe se considera altura 0
int ArbolAVL::altura(NodoAVL* nodo){

    if(nodo == nullptr)
        return 0;

    return nodo->altura;
}

// devuelve el mayor entre dos numeros
// se usa para recalcular alturas del AVL, la altura siempre es: 1 + max(altura hijo izquierdo, altura hijo derecho)
int ArbolAVL::maximo(int a, int b){
    if(a > b)
        return a; // si a es mayor se devuelve directamente

    return b; // si a es mayor se devuelve directamente
}

// calcula el factor de balance del nodo
// balance = altura izquierda - altura derecha
int ArbolAVL::factorBalance(NodoAVL* nodo){
    if(nodo == nullptr)
        return 0;
    return altura(nodo->izquierda) - altura(nodo->derecha);
}

// ROTACION II
// ocurre cuando el desbalance se produce
// en el hijo izquierdo del hijo izquierdo
NodoAVL* ArbolAVL::rotacionII(NodoAVL* y){

    NodoAVL* x = y->izquierda;
    NodoAVL* T2 = x->derecha;

    // x pasa a ser la nueva raiz del subarbol
    x->derecha = y;

    // el subarbol derecho de x se convierte
    // en el hijo izquierdo de y
    y->izquierda = T2;

    // actualizar alturas despues de modificar la estructura
    y->altura = 1 + maximo(altura(y->izquierda), altura(y->derecha));
    x->altura = 1 + maximo(altura(x->izquierda), altura(x->derecha));

    return x;
}

// ROTACION DD
// ocurre cuando el desbalance esta
// en el hijo derecho del hijo derecho
NodoAVL* ArbolAVL::rotacionDD(NodoAVL* x){

    NodoAVL* y = x->derecha;
    NodoAVL* T2 = y->izquierda;

    // y se convierte en la nueva raiz del subarbol
    y->izquierda = x;

    // el subarbol izquierdo de y pasa a ser
    // el hijo derecho de x
    x->derecha = T2;

    // actualizar alturas
    x->altura = 1 + maximo(altura(x->izquierda), altura(x->derecha));
    y->altura = 1 + maximo(altura(y->izquierda), altura(y->derecha));

    return y;
}

// ROTACION ID
// primero se corrige el hijo izquierdo
// luego se aplica rotacion II
NodoAVL* ArbolAVL::rotacionID(NodoAVL* nodo){

    nodo->izquierda = rotacionDD(nodo->izquierda);

    return rotacionII(nodo);
}

// ROTACION DI
// primero se corrige el hijo derecho
// luego se aplica rotacion DD
NodoAVL* ArbolAVL::rotacionDI(NodoAVL* nodo){

    nodo->derecha = rotacionII(nodo->derecha);

    return rotacionDD(nodo);
}

// insercion recursiva en el AVL
// primero se inserta normal
// luego se verifica si se necesita rebalanceo
NodoAVL* ArbolAVL::insertarRec(NodoAVL* nodo, Producto* producto){

    // insercion normal
    if(nodo == nullptr)
        return new NodoAVL(producto);

    if(producto->nombre < nodo->producto->nombre)
        nodo->izquierda = insertarRec(nodo->izquierda, producto);

    else if(producto->nombre > nodo->producto->nombre)
        nodo->derecha = insertarRec(nodo->derecha, producto);

    else
        return nodo; // no se permiten duplicados


    // actualizar altura del nodo actual
    nodo->altura = 1 + maximo(altura(nodo->izquierda), altura(nodo->derecha));

    int balance = factorBalance(nodo);

    // CASOS DE DESBALANCE
    // II
    if(balance > 1 && producto->nombre < nodo->izquierda->producto->nombre)
        return rotacionII(nodo);

    // DD
    if(balance < -1 && producto->nombre > nodo->derecha->producto->nombre)
        return rotacionDD(nodo);

    // ID
    if(balance > 1 && producto->nombre > nodo->izquierda->producto->nombre)
        return rotacionID(nodo);

    // DI
    if(balance < -1 && producto->nombre < nodo->derecha->producto->nombre)
        return rotacionDI(nodo);

    return nodo;
}

// busca el nodo mas a la izquierda del subarbol
// en eliminacion se usa como sucesor inorder al eliminar un nodo con dos hijos
NodoAVL* ArbolAVL::nodoMinimo(NodoAVL* nodo){

    NodoAVL* actual = nodo;
    // avanzamos siempre hacia el hijo izquierdo hasta encontrar el nodo que ya no tenga hijo izquierdo
    while(actual->izquierda != nullptr)
        actual = actual->izquierda;
    // ese nodo es el menor del subarbol
    return actual;
}

// eliminacion recursiva
// aplica los 3 casos clasicos de eliminacion
// luego rebalancea el AVL
NodoAVL* ArbolAVL::eliminarRec(NodoAVL* nodo, std::string nombre){
    // si el nodo actual es nulo el elemento no existe en el arbol
    if(nodo == nullptr)
        return nodo;

    // buscar el nodo a eliminar
    // si el nombre buscado es menor que el nodo actual seguimos buscando en el subarbol izquierdo
    if(nombre < nodo->producto->nombre)
        nodo->izquierda = eliminarRec(nodo->izquierda, nombre);

    // si es mayor seguimos por el subarbol derecho
    else if(nombre > nodo->producto->nombre)
        nodo->derecha = eliminarRec(nodo->derecha, nombre);

    else{ // se llega al nodo que debe eliminarse
        // Caso 1 y 2: nodo con 0 o 1 hijo
        if(nodo->izquierda == nullptr || nodo->derecha == nullptr){

            NodoAVL* temp;
            //determinamos cual hijo existe (o si existe alguno)
            if(nodo->izquierda != nullptr)
                temp = nodo->izquierda;
            else
                temp = nodo->derecha;

            // nodo hoja (no tiene hijos)
            if(temp == nullptr){
                //se guarda el nodo actual
                temp = nodo;
                nodo = nullptr;
            }
            else{
                // nodo con un hijo: copiar datos del hijo al nodo actual
                *nodo = *temp;
            }
            //liberamos el nodo eliminado
            delete temp;
        }

        // Caso 3: nodo con dos hijos
        else{

            // se obtiene el sucesor inorder (el  nodo mas pequenio del subarbol derecho
            NodoAVL* temp = nodoMinimo(nodo->derecha);

            // se copia el producto del sucesor en el nodo actual
            nodo->producto = temp->producto;

            // se elimina el sucesor del subarbol derecho
            nodo->derecha = eliminarRec(nodo->derecha, temp->producto->nombre);
        }
    }


    // si despues de  eliminar el arbol queda vacio
    if(nodo == nullptr)
        return nodo;


    // actualizar altura
    nodo->altura = 1 + maximo(altura(nodo->izquierda), altura(nodo->derecha));
    //verificar balance del avl
    int balance = factorBalance(nodo);


    // rebalanceo del arbol
    // desbalance izquierda-izquierda
    if(balance > 1 && factorBalance(nodo->izquierda) >= 0)
        return rotacionII(nodo);

    // desbalance izquierda-derecha
    if(balance > 1 && factorBalance(nodo->izquierda) < 0)
        return rotacionID(nodo);

    // desbalance derecha-derecha
    if(balance < -1 && factorBalance(nodo->derecha) <= 0)
        return rotacionDD(nodo);

    // desbalance derecha-izquierda
    if(balance < -1 && factorBalance(nodo->derecha) > 0)
        return rotacionDI(nodo);

    // si no hubo desbalance el nodo se mantiene igual
    return nodo;
}

// busqueda binaria dentro del AVL
Producto* ArbolAVL::buscarRec(NodoAVL* nodo, std::string nombre){

    if(nodo == nullptr)
        return nullptr;

    if(nombre == nodo->producto->nombre)
        return nodo->producto;

    if(nombre < nodo->producto->nombre)
        return buscarRec(nodo->izquierda, nombre);

    return buscarRec(nodo->derecha, nombre);
}

// recorrido inorder: permite obtener los productos ordenados por nombre
void ArbolAVL::inorderRec(NodoAVL* nodo){

    if(nodo == nullptr)
        return;

    inorderRec(nodo->izquierda);
    inorderRec(nodo->derecha);
}

void ArbolAVL::insertar(Producto* producto){
    raiz = insertarRec(raiz, producto);
}

void ArbolAVL::eliminar(std::string nombre){
    raiz = eliminarRec(raiz, nombre);
}

Producto* ArbolAVL::buscar(std::string nombre){
    return buscarRec(raiz, nombre);
}

void ArbolAVL::inorder(){
    inorderRec(raiz);
}