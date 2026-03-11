//
// Created by ronald on 11/3/26.
//

#ifndef PROYECTO1_LISTA_ENLAZADA_H
#define PROYECTO1_LISTA_ENLAZADA_H
// nodo generico de la lista
// T puede ser cualquier tipo (en nuestro caso normalmente sera Producto*)
template <typename T>
class NodoLista {

public:
    T dato;                        // informacion almacenada en el nodo
    NodoLista<T>* siguiente;       // puntero al siguiente nodo

    NodoLista(T dato) {
        this->dato = dato;         // guardamos el dato recibido
        this->siguiente = nullptr; // inicialmente no apunta a nadie
    }
};

// clase lista enlazada generica
template <typename T>
class ListaEnlazada {

private:
    NodoLista<T>* cabeza; // primer nodo de la lista
    int tamanio;

public:
    ListaEnlazada() {
        cabeza = nullptr; // al inicio la lista no tiene nodos
        tamanio = 0;      // tamaño inicial es 0
    }

    // destructor de la lista
    ~ListaEnlazada() {
        NodoLista<T>* actual = cabeza;
        while(actual != nullptr) {
            NodoLista<T>* temp = actual;  // guardamos el nodo actual
            actual = actual->siguiente;   // avanzamos al siguiente nodo
            delete temp;                  // liberamos memoria del nodo
        }
    }

    // inserta un elemento al inicio de la lista
    void insertarInicio(T dato) {
        NodoLista<T>* nuevo = new NodoLista<T>(dato); // creamos nodo nuevo
        nuevo->siguiente = cabeza; // el nuevo nodo apunta al antiguo primero
        cabeza = nuevo;            // ahora el nuevo nodo es la cabeza
        tamanio++;                 // aumentamos el tamaño de la lista
    }

    // inserta un elemento al final de la lista
    void insertarFinal(T dato) {
        NodoLista<T>* nuevo = new NodoLista<T>(dato); // creamos nodo nuevo
        // si la lista esta vacia el nuevo nodo sera la cabeza
        if(cabeza == nullptr) {
            cabeza = nuevo;
            tamanio++;
            return;
        }
        // recorremos la lista hasta encontrar el ultimo nodo
        NodoLista<T>* actual = cabeza;

        while(actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }

        // el ultimo nodo ahora apunta al nuevo nodo
        actual->siguiente = nuevo;
        tamanio++;
    }

    // busca un elemento usando una funcion de comparacion
    // la funcion comparar define cuando dos elementos se consideran iguales
    T buscar(bool (*comparar)(T, T), T clave) {

        NodoLista<T>* actual = cabeza;

        while(actual != nullptr) {

            // si la funcion comparar devuelve true encontramos el elemento
            if(comparar(actual->dato, clave)) {
                return actual->dato;
            }
            actual = actual->siguiente; // avanzamos al siguiente nodo
        }

        // si no se encontro nada devolvemos nullptr
        return nullptr;
    }

    // elimina un elemento de la lista
    // tambien utiliza una funcion de comparacion
    bool eliminar(bool (*comparar)(T, T), T clave) {
        NodoLista<T>* actual = cabeza;
        NodoLista<T>* anterior = nullptr;

        while(actual != nullptr) {

            if(comparar(actual->dato, clave)) {

                // si el nodo a eliminar es la cabeza
                if(anterior == nullptr) {
                    cabeza = actual->siguiente;
                }
                else {
                    anterior->siguiente = actual->siguiente;
                }
                delete actual; // liberamos memoria
                tamanio--;
                return true;
            }
            anterior = actual;
            actual = actual->siguiente;
        }
        return false;
    }

    // devuelve el tamaño actual de la lista
    int obtenerTamanio() {
        return tamanio;
    }

    // indica si la lista esta vacia
    bool estaVacia() {
        return cabeza == nullptr;
    }

    // recorre toda la lista ejecutando una funcion sobre cada elemento
    void recorrer(void (*funcion)(T)) {
        NodoLista<T>* actual = cabeza;
        while(actual != nullptr) {

            funcion(actual->dato); // ejecutamos la funcion recibida
            actual = actual->siguiente;
        }
    }

    // devuelve el puntero a la cabeza
    NodoLista<T>* obtenerCabeza() {
        return cabeza;
    }
};
#endif //PROYECTO1_LISTA_ENLAZADA_H