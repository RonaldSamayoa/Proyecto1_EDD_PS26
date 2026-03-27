//
// Created by ronald on 11/3/26.
//
#include "../include/estructuras/arbol_bplus.h"
#include <iostream>

// constructor del arbol B+
ArbolBPlus::ArbolBPlus(int t){
    this->t = t;
    raiz = nullptr; // inicialmente el arbol esta vacio
}

// busca la hoja donde deberia estar una categoria
NodoBPlus* ArbolBPlus::buscarHoja(NodoBPlus* nodo, std::string categoria){

    // si ya es hoja, devolvemos directamente
    if(nodo->hoja)
        return nodo;

    int i = 0;

    // encontrar el hijo adecuado usando >= para ir al hijo derecho en caso de igualdad
    while(i < nodo->n && categoria >= nodo->claves[i]){
        i++;
    }

    // bajar recursivamente al hijo correspondiente
    return buscarHoja(nodo->hijos[i], categoria);
}

// inserta un producto
void ArbolBPlus::insertar(Producto* producto){

    // arbol vacio → crear raiz hoja
    if(raiz == nullptr){

        raiz = new NodoBPlus(t, true);

        raiz->claves[0] = producto->categoria;
        raiz->datos[0] = new ListaEnlazada<Producto*>();
        raiz->datos[0]->insertarFinal(producto);

        raiz->n = 1;
        return;
    }

    std::string nuevaClave;       // clave que sube si hay split
    NodoBPlus* nuevoNodo = nullptr; // nuevo nodo creado por split

    // insercion recursiva
    insertarNoLleno(raiz, producto, nuevaClave, nuevoNodo);

    // si la raiz se dividio, crear nueva raiz
    if(nuevoNodo != nullptr){

        NodoBPlus* nuevaRaiz = new NodoBPlus(t, false);

        nuevaRaiz->claves[0] = nuevaClave;
        nuevaRaiz->hijos[0] = raiz;
        nuevaRaiz->hijos[1] = nuevoNodo;

        nuevaRaiz->n = 1;

        raiz = nuevaRaiz;
    }
}

// busca todos los productos de una categoria
ListaEnlazada<Producto*>* ArbolBPlus::buscarCategoria(std::string categoria){

    // si el arbol esta vacio no hay nada que buscar
    if(raiz == nullptr)
        return nullptr;

    // bajar hasta la hoja donde deberia estar la categoria
    NodoBPlus* hoja = buscarHoja(raiz, categoria);

    // recorrer claves de la hoja
    for(int i = 0; i < hoja->n; i++){
        //si encontramos la categoria  devolvemos su lista
        if(hoja->claves[i] == categoria){
            return hoja->datos[i]; // devolvemos la lista completa
        }
    }
    // no existe la categoria
    return nullptr;
}

// divide una hoja en dos cuando esta llena
void ArbolBPlus::dividirHoja(NodoBPlus* hoja, std::string& nuevaClave, NodoBPlus*& nuevaHoja){

    // crear nueva hoja
    nuevaHoja = new NodoBPlus(t, true);

    // punto medio de division
    int mitad = t;

    // copiar la mitad derecha a la nueva hoja
    for(int i = mitad, j = 0; i < hoja->n; i++, j++){
        nuevaHoja->claves[j] = hoja->claves[i];
        nuevaHoja->datos[j] = hoja->datos[i];
        nuevaHoja->n++;
    }

    // ajustar tamanio de la hoja original
    hoja->n = mitad;

    // enlazar hojas
    nuevaHoja->siguiente = hoja->siguiente;
    hoja->siguiente = nuevaHoja;

    // la clave que se sube es la primera de la nueva hoja
    nuevaClave = nuevaHoja->claves[0];
}

void ArbolBPlus::insertarNoLleno(NodoBPlus* nodo, Producto* producto, std::string& nuevaClave, NodoBPlus*& nuevoNodo){

    // CASO 1: nodo hoja
    if(nodo->hoja){

        // buscar si ya existe la categoria
        for(int i = 0; i < nodo->n; i++){
            if(nodo->claves[i] == producto->categoria){
                nodo->datos[i]->insertarFinal(producto);
                nuevoNodo = nullptr;
                return;
            }
        }

        // insertar normalmente
        int i = nodo->n - 1;

        while(i >= 0 && producto->categoria < nodo->claves[i]){
            nodo->claves[i+1] = nodo->claves[i];
            nodo->datos[i+1] = nodo->datos[i];
            i--;
        }

        nodo->claves[i+1] = producto->categoria;
        nodo->datos[i+1] = new ListaEnlazada<Producto*>();
        nodo->datos[i+1]->insertarFinal(producto);

        nodo->n++;

        // si no hay desbordamiento terminamos
        if(nodo->n < 2*t){
            nuevoNodo = nullptr;
            return;
        }

        // SPLIT DE HOJA
        dividirHoja(nodo, nuevaClave, nuevoNodo);
        return;
    }

    // CASO 2: nodo interno
    int i = nodo->n - 1;

    // buscar hijo adecuado
    while(i >= 0 && producto->categoria < nodo->claves[i]){
        i--;
    }
    i++;

    std::string claveSube;
    NodoBPlus* nuevoHijo = nullptr;

    // insertar recursivamente en hijo
    insertarNoLleno(nodo->hijos[i], producto, claveSube, nuevoHijo);

    // si no hubo split en el hijo no hay nada que hacer
    if(nuevoHijo == nullptr){
        nuevoNodo = nullptr;
        return;
    }

    // buscar posicion correcta para insertar la clave subida
    int pos = i;

    while(pos < nodo->n && nodo->claves[pos] < claveSube){
        pos++;
    }

    // mover claves e hijos para abrir espacio
    for(int j = nodo->n; j > pos; j--){
        nodo->claves[j] = nodo->claves[j-1];
        nodo->hijos[j+1] = nodo->hijos[j];
    }

    // insertar nueva clave y nuevo hijo
    nodo->claves[pos] = claveSube;
    nodo->hijos[pos+1] = nuevoHijo;

    nodo->n++;

    // si no hay desbordamiento
    if(nodo->n < 2*t){
        nuevoNodo = nullptr;
        return;
    }

    // si hay desbordamiento en nodo interno
    if(nodo->n >= 2*t){
        dividirNodoInterno(nodo, nuevaClave, nuevoNodo);
        return;
    }
}

void ArbolBPlus::dividirNodoInterno(NodoBPlus* nodo, std::string& nuevaClave, NodoBPlus*& nuevoNodo){

    // crear nuevo nodo interno (NO hoja)
    nuevoNodo = new NodoBPlus(t, false);

    int mitad = t; // punto de division

    // la clave que sube al padre es la del medio
    nuevaClave = nodo->claves[mitad];

    // mover claves a la derecha (sin incluir la que sube)
    int j = 0;
    for(int i = mitad + 1; i < nodo->n; i++){
        nuevoNodo->claves[j] = nodo->claves[i];
        j++;
    }

    // mover hijos correspondientes
    j = 0;
    for(int i = mitad + 1; i <= nodo->n; i++){
        nuevoNodo->hijos[j] = nodo->hijos[i];
        j++;
    }

    // actualizar tamanios
    nuevoNodo->n = nodo->n - mitad - 1;
    nodo->n = mitad;
}

// recorre todas las categorias del arbol B+ en orden y utiliza los punteros 'siguiente' para ir hoja por hoja
void ArbolBPlus::recorrerCategorias(){

    // si el arbol esta vacio no hay nada que mostrar
    if(raiz == nullptr)
        return;

    NodoBPlus* actual = raiz;

    // bajar hasta la hoja mas a la izquierda
    while(!actual->hoja){
        actual = actual->hijos[0];
    }

    // recorrer todas las hojas usando el puntero siguiente
    while(actual != nullptr){

        // recorrer todas las claves (categorias) de la hoja actual
        for(int i = 0; i < actual->n; i++){

            // imprimir nombre de categoria
            std::cout << "Categoria: " << actual->claves[i] << std::endl;

            // recorrer lista de productos de esa categoria
            actual->datos[i]->recorrer([](Producto* p){
                std::cout << "  - " << p->nombre << std::endl;
            });
        }

        // avanzar a la siguiente hoja
        actual = actual->siguiente;
    }
}

// elimina un producto de una categoria en el arbol B+
bool ArbolBPlus::eliminar(std::string categoria, std::string nombre){
    if(raiz == nullptr)
        return false;

    bool eliminado = eliminarRec(raiz, categoria, nombre);

    // si la raiz queda vacia y no es hoja, bajar un nivel
    if(raiz->n == 0 && !raiz->hoja){
        raiz = raiz->hijos[0];
    }
    return eliminado;
}

// elimina recursivamente en el arbol B+
bool ArbolBPlus::eliminarRec(NodoBPlus* nodo, std::string categoria, std::string nombre){
    // ===== CASO 1: nodo hoja =====
    if(nodo->hoja){
        // recorrer claves (categorias)
        for(int i = 0; i < nodo->n; i++){

            if(nodo->claves[i] == categoria){

                // funcion de comparacion por nombre
                auto comparar = [](Producto* a, Producto* b){
                    return a->nombre == b->nombre;
                };

                // producto temporal para comparar
                Producto dummy;
                dummy.nombre = nombre;

                // eliminar de la lista
                bool eliminado = nodo->datos[i]->eliminar(comparar, &dummy);

                if(!eliminado)
                    return false;

                // si la lista queda vacia eliminamos la categoria
                if(nodo->datos[i]->estaVacia()){

                    delete nodo->datos[i];

                    // mover claves y datos hacia la izquierda
                    for(int j = i; j < nodo->n - 1; j++){
                        nodo->claves[j] = nodo->claves[j+1];
                        nodo->datos[j] = nodo->datos[j+1];
                    }

                    nodo->n--;
                }

                return true;
            }
        }
        // categoria no encontrada
        return false;
    }

    // ===== CASO 2: nodo interno =====
    int i = 0;

    // buscar hijo donde podria estar la categoria
    while(i < nodo->n && categoria >= nodo->claves[i]){
        i++;
    }

    // bajar recursivamente
    bool eliminado = eliminarRec(nodo->hijos[i], categoria, nombre);

    if(!eliminado)
        return false;

    // verificar si el hijo tiene menos claves de las permitidas
    if(nodo->hijos[i]->n < (t - 1)){
        // arreglar el arbol
        manejarSubdesbordamiento(nodo->hijos[i], nodo, i);
    }
    return true;
}

// maneja subdesbordamiento en un nodo
void ArbolBPlus::manejarSubdesbordamiento(NodoBPlus* nodo, NodoBPlus* padre, int indice){

    // ===== 1. INTENTAR CON HERMANO IZQUIERDO =====
    if(indice > 0){
        NodoBPlus* hermanoIzq = padre->hijos[indice - 1];

        // si el hermano puede prestar
        if(hermanoIzq->n >= t){

            // ===== CASO HOJA =====
            if(nodo->hoja){
                // mover claves del nodo a la derecha para abrir espacio
                for(int i = nodo->n; i > 0; i--){
                    nodo->claves[i] = nodo->claves[i-1];
                    nodo->datos[i] = nodo->datos[i-1];
                }

                // tomar la ultima clave del hermano izquierdo
                nodo->claves[0] = hermanoIzq->claves[hermanoIzq->n - 1];
                nodo->datos[0] = hermanoIzq->datos[hermanoIzq->n - 1];

                nodo->n++;
                hermanoIzq->n--;

                // actualizar clave en el padre
                padre->claves[indice - 1] = nodo->claves[0];
            }

            // ===== CASO NODO INTERNO =====
            else{

                // mover claves e hijos del nodo a la derecha
                for(int i = nodo->n; i > 0; i--){
                    nodo->claves[i] = nodo->claves[i-1];
                    nodo->hijos[i+1] = nodo->hijos[i];
                }

                nodo->hijos[1] = nodo->hijos[0];

                // bajar clave del padre
                nodo->claves[0] = padre->claves[indice - 1];

                // subir clave del hermano al padre
                padre->claves[indice - 1] = hermanoIzq->claves[hermanoIzq->n - 1];

                // mover hijo correspondiente
                nodo->hijos[0] = hermanoIzq->hijos[hermanoIzq->n];

                nodo->n++;
                hermanoIzq->n--;
            }
            return; // ya resolvimos
        }
    }

    // ===== 2. INTENTAR CON HERMANO DERECHO =====
    if(indice < padre->n){
        NodoBPlus* hermanoDer = padre->hijos[indice + 1];

        // si puede prestar
        if(hermanoDer->n >= t){

            // ===== CASO HOJA =====
            if(nodo->hoja){
                // tomar la primera clave del hermano derecho
                nodo->claves[nodo->n] = hermanoDer->claves[0];
                nodo->datos[nodo->n] = hermanoDer->datos[0];

                nodo->n++;

                // mover claves del hermano a la izquierda
                for(int i = 0; i < hermanoDer->n - 1; i++){
                    hermanoDer->claves[i] = hermanoDer->claves[i+1];
                    hermanoDer->datos[i] = hermanoDer->datos[i+1];
                }

                hermanoDer->n--;

                // actualizar clave en el padre
                padre->claves[indice] = hermanoDer->claves[0];
            }

            // ===== CASO NODO INTERNO =====
            else{
                // bajar clave del padre
                nodo->claves[nodo->n] = padre->claves[indice];

                // subir clave del hermano al padre
                padre->claves[indice] = hermanoDer->claves[0];
                // mover hijo correspondiente
                nodo->hijos[nodo->n + 1] = hermanoDer->hijos[0];

                nodo->n++;

                // mover claves e hijos del hermano
                for(int i = 0; i < hermanoDer->n - 1; i++){
                    hermanoDer->claves[i] = hermanoDer->claves[i+1];
                    hermanoDer->hijos[i] = hermanoDer->hijos[i+1];
                }
                hermanoDer->hijos[hermanoDer->n - 1] = hermanoDer->hijos[hermanoDer->n];
                hermanoDer->n--;
            }
            return; // ya resolvimos
        }
    }

    // ===== 3. SI NO SE PUEDE PRESTAR, FUSIONAR =====
    // intentar fusion con hermano izquierdo
    if(indice > 0){
        NodoBPlus* hermanoIzq = padre->hijos[indice - 1];
        fusionar(hermanoIzq, nodo, padre, indice - 1);
    }
    else{
        // fusion con hermano derecho
        NodoBPlus* hermanoDer = padre->hijos[indice + 1];
        fusionar(nodo, hermanoDer, padre, indice);
    }
}

// fusiona dos nodos en uno solo
void ArbolBPlus::fusionar(NodoBPlus* nodo, NodoBPlus* hermano, NodoBPlus* padre, int indice){
    // ===== CASO HOJA =====
    if(nodo->hoja){

        // copiar todas las claves y datos del hermano al nodo
        for(int i = 0; i < hermano->n; i++){
            nodo->claves[nodo->n + i] = hermano->claves[i];
            nodo->datos[nodo->n + i] = hermano->datos[i];
        }

        nodo->n += hermano->n;

        // ajustar lista enlazada de hojas
        nodo->siguiente = hermano->siguiente;

        // eliminar hermano
        delete hermano;
    }

    // ===== CASO NODO INTERNO =====
    else{
        // bajar clave del padre al nodo
        nodo->claves[nodo->n] = padre->claves[indice];

        // copiar claves del hermano
        for(int i = 0; i < hermano->n; i++){
            nodo->claves[nodo->n + 1 + i] = hermano->claves[i];
        }

        // copiar hijos del hermano
        for(int i = 0; i <= hermano->n; i++){
            nodo->hijos[nodo->n + 1 + i] = hermano->hijos[i];
        }

        nodo->n += hermano->n + 1;
        // eliminar hermano
        delete hermano;
    }

    // ===== AJUSTAR PADRE =====
    // mover claves del padre
    for(int i = indice; i < padre->n - 1; i++){
        padre->claves[i] = padre->claves[i + 1];
    }

    // mover hijos del padre
    for(int i = indice + 1; i < padre->n; i++){
        padre->hijos[i] = padre->hijos[i + 1];
    }
    padre->n--;
}