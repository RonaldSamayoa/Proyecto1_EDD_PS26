//
// Created by ronald on 11/3/26.
//
#include "../include/estructuras/arbol_b.h"

// constructor del arbol B
ArbolB::ArbolB(int t){
    this->t = t;

    // inicialmente el arbol esta vacio
    raiz = nullptr;
}

// inserta un producto en el arbol B
void ArbolB::insertar(Producto* producto){
    // si el arbol esta vacio se crea la raiz
    if(raiz == nullptr){

        raiz = new NodoB(t, true); // nodo hoja
        raiz->claves[0] = producto; // primera clave
        raiz->n = 1;
        return;
    }

    // si la raiz esta llena se debe dividir
    if(raiz->n == 2*t - 1){

        // crear nueva raiz
        NodoB* nuevaRaiz = new NodoB(t, false);

        // la antigua raiz pasa a ser hijo
        nuevaRaiz->hijos[0] = raiz;

        // dividir la raiz
        dividirHijo(nuevaRaiz, 0, raiz);

        // decidir a que hijo bajar
        int i = 0;
        if(producto->fecha_caducidad > nuevaRaiz->claves[0]->fecha_caducidad)
            i++;

        insertarNoLleno(nuevaRaiz->hijos[i], producto);

        // actualizar raiz
        raiz = nuevaRaiz;
    }
    else{
        // si no esta llena, insertar directamente
        insertarNoLleno(raiz, producto);
    }
}

// inserta en un nodo que no esta lleno
void ArbolB::insertarNoLleno(NodoB* nodo, Producto* producto){

    int i = nodo->n - 1;

    // CASO HOJA
    if(nodo->hoja){

        // mover claves mayores hacia la derecha para abrir espacio a la nueva clave
        while(i >= 0 &&
              producto->fecha_caducidad < nodo->claves[i]->fecha_caducidad){

            nodo->claves[i+1] = nodo->claves[i];
            i--;
              }

        // insertar en la posicion correcta
        nodo->claves[i+1] = producto;

        nodo->n++;
    }
    else{
        // buscar el hijo donde debe ir el producto
        while(i >= 0 &&
              producto->fecha_caducidad < nodo->claves[i]->fecha_caducidad){
            i--;
              }

        i++; // posicion del hijo

        // si el hijo esta lleno hay que dividirlo
        if(nodo->hijos[i]->n == 2*t - 1){

            dividirHijo(nodo, i, nodo->hijos[i]);

            // decidir si ir al hijo izquierdo o derecho despues del split
            if(producto->fecha_caducidad > nodo->claves[i]->fecha_caducidad)
                i++;
        }

        insertarNoLleno(nodo->hijos[i], producto);
    }
}

// divide un nodo hijo que esta lleno
void ArbolB::dividirHijo(NodoB* padre, int indice, NodoB* hijo){
    // crear nuevo nodo que almacenara la mitad derecha
    NodoB* nuevo = new NodoB(t, hijo->hoja);

    // el nuevo nodo tendra t-1 claves
    nuevo->n = t - 1;

    // copiar las ultimas (t-1) claves al nuevo nodo
    for(int j = 0; j < t-1; j++){
        nuevo->claves[j] = hijo->claves[j + t];
    }

    // si no es hoja, copiar tambien los hijos
    if(!hijo->hoja){
        for(int j = 0; j < t; j++){
            nuevo->hijos[j] = hijo->hijos[j + t];
        }
    }

    // reducir numero de claves del hijo original
    hijo->n = t - 1;

    // mover los hijos del padre para hacer espacio
    for(int j = padre->n; j >= indice + 1; j--){
        padre->hijos[j + 1] = padre->hijos[j];
    }

    // enlazar el nuevo hijo
    padre->hijos[indice + 1] = nuevo;

    // mover claves del padre para hacer espacio
    for(int j = padre->n - 1; j >= indice; j--){
        padre->claves[j + 1] = padre->claves[j];
    }

    // subir la clave central al padre
    padre->claves[indice] = hijo->claves[t - 1];

    padre->n++;
}

// buscar producto por fecha
Producto* ArbolB::buscarRec(NodoB* nodo, std::string fecha){
    int i = 0;

    // encontrar la primera clave >= fecha
    while(i < nodo->n && fecha > nodo->claves[i]->fecha_caducidad){
        i++;
    }

    // si encontramos la clave
    if(i < nodo->n && fecha == nodo->claves[i]->fecha_caducidad){
        return nodo->claves[i];
    }

    // si es hoja no existe
    if(nodo->hoja)
        return nullptr;

    // bajar al hijo correspondiente
    return buscarRec(nodo->hijos[i], fecha);
}

// funcion publica de busqueda (por fecha)
Producto* ArbolB::buscar(std::string fecha){

    if(raiz == nullptr)
        return nullptr;

    return buscarRec(raiz, fecha);
}

// busca productos dentro de un rango de fechas
ListaEnlazada<Producto*> ArbolB::buscarRango(std::string inicio, std::string fin){
    ListaEnlazada<Producto*> resultado;

    if(raiz != nullptr){
        buscarRangoRec(raiz, inicio, fin, resultado);
    }
    return resultado;
}

// recorrido del arbol para encontrar elementos en rango
void ArbolB::buscarRangoRec(NodoB* nodo, std::string inicio, std::string fin, ListaEnlazada<Producto*>& resultado){
    int i;

    // recorrer cada clave del nodo
    for(i = 0; i < nodo->n; i++){

        // si no es hoja, primero explorar hijo izquierdo
        if(!nodo->hoja){
            buscarRangoRec(nodo->hijos[i], inicio, fin, resultado);
        }

        std::string fecha = nodo->claves[i]->fecha_caducidad;

        // si la fecha esta dentro del rango la agregamos
        if(fecha >= inicio && fecha <= fin){
            resultado.insertarFinal(nodo->claves[i]);
        }

        // si ya pasamos el rango, podemos cortar
        if(fecha > fin){
            return;
        }
    }

    // procesar el ultimo hijo
    if(!nodo->hoja){
        buscarRangoRec(nodo->hijos[i], inicio, fin, resultado);
    }
}

void ArbolB::eliminar(std::string fecha){
    if(raiz == nullptr)
        return;

    eliminarRec(raiz, fecha);

    // si la raiz se queda sin claves
    if(raiz->n == 0){
        NodoB* temp = raiz;

        // si era hoja, el arbol queda vacio
        if(raiz->hoja){
            raiz = nullptr;
        }
        else{
            // si no, el primer hijo se convierte en nueva raiz
            raiz = raiz->hijos[0];
        }
        delete temp;
    }
}

int ArbolB::encontrarClave(NodoB* nodo, std::string fecha){
    int idx = 0;

    // buscamos la primera clave >= fecha
    while(idx < nodo->n && nodo->claves[idx]->fecha_caducidad < fecha)
        idx++;

    return idx;
}

void ArbolB::eliminarRec(NodoB* nodo, std::string fecha){
    int idx = encontrarClave(nodo, fecha);

    // CASO 1: la clave está en este nodo
    if(idx < nodo->n && nodo->claves[idx]->fecha_caducidad == fecha){

        // si es hoja, eliminar directo
        if(nodo->hoja)
            eliminarDeHoja(nodo, idx);
        else
            eliminarDeInterno(nodo, idx);
    }
    else{
        // si es hoja, no existe
        if(nodo->hoja)
            return;

        bool ultimo = (idx == nodo->n);

        // si el hijo tiene menos de t claves, arreglar antes de bajar
        if(nodo->hijos[idx]->n < t)
            llenar(nodo, idx);

        // si hicimos merge puede cambiar la posición
        if(ultimo && idx > nodo->n)
            eliminarRec(nodo->hijos[idx - 1], fecha);
        else
            eliminarRec(nodo->hijos[idx], fecha);
    }
}

void ArbolB::eliminarDeHoja(NodoB* nodo, int idx){
    // mover todas las claves una posicion a la izquierda
    for(int i = idx + 1; i < nodo->n; i++){
        nodo->claves[i - 1] = nodo->claves[i];
    }
    nodo->n--;
}

void ArbolB::eliminarDeInterno(NodoB* nodo, int idx){
    Producto* clave = nodo->claves[idx];

    // CASO A: el hijo izquierdo tiene al menos t claves
    if(nodo->hijos[idx]->n >= t){

        // obtener el predecesor (mayor del subarbol izquierdo)
        Producto* pred = obtenerPredecesor(nodo, idx);

        // reemplazar la clave actual
        nodo->claves[idx] = pred;

        // eliminar recursivamente el predecesor
        eliminarRec(nodo->hijos[idx], pred->fecha_caducidad);
    }

    // CASO B: el hijo derecho tiene al menos t claves
    else if(nodo->hijos[idx + 1]->n >= t){

        // obtener el sucesor (menor del subarbol derecho)
        Producto* succ = obtenerSucesor(nodo, idx);

        // reemplazar la clave
        nodo->claves[idx] = succ;

        // eliminar recursivamente el sucesor
        eliminarRec(nodo->hijos[idx + 1], succ->fecha_caducidad);
    }

    // CASO C: ambos hijos tienen t-1 → hacer merge
    else{

        // fusionar hijo izquierdo, clave y hijo derecho
        fusionar(nodo, idx);

        // ahora la clave está en el hijo fusionado
        eliminarRec(nodo->hijos[idx], clave->fecha_caducidad);
    }
}

Producto* ArbolB::obtenerSucesor(NodoB* nodo, int idx){
    NodoB* actual = nodo->hijos[idx + 1];

    // ir siempre al hijo mas izquierdo
    while(!actual->hoja){
        actual = actual->hijos[0];
    }

    // la primera clave es el sucesor
    return actual->claves[0];
}

Producto* ArbolB::obtenerPredecesor(NodoB* nodo, int idx){
    NodoB* actual = nodo->hijos[idx];

    // ir siempre al hijo mas derecho
    while(!actual->hoja){
        actual = actual->hijos[actual->n];
    }

    // la ultima clave es el predecesor
    return actual->claves[actual->n - 1];
}

void ArbolB::llenar(NodoB* nodo, int idx){
    // si el hermano izquierdo tiene suficientes claves
    if(idx != 0 && nodo->hijos[idx - 1]->n >= t){
        pedirPrestadoIzq(nodo, idx);
    }

    // si el hermano derecho tiene suficientes claves
    else if(idx != nodo->n && nodo->hijos[idx + 1]->n >= t){
        pedirPrestadoDer(nodo, idx);
    }

    // si ninguno puede prestar → fusionar
    else{
        // si es el ultimo hijo, fusionar con el izquierdo
        if(idx != nodo->n)
            fusionar(nodo, idx);
        else
            fusionar(nodo, idx - 1);
    }
}

void ArbolB::pedirPrestadoIzq(NodoB* nodo, int idx){
    NodoB* hijo = nodo->hijos[idx];
    NodoB* hermano = nodo->hijos[idx - 1];

    // mover claves del hijo hacia la derecha para abrir espacio
    for(int i = hijo->n - 1; i >= 0; i--){
        hijo->claves[i + 1] = hijo->claves[i];
    }

    // si no es hoja, mover tambien los hijos
    if(!hijo->hoja){
        for(int i = hijo->n; i >= 0; i--){
            hijo->hijos[i + 1] = hijo->hijos[i];
        }
    }

    // bajar la clave del padre al hijo
    hijo->claves[0] = nodo->claves[idx - 1];

    // si hay hijos, mover el ultimo hijo del hermano
    if(!hijo->hoja){
        hijo->hijos[0] = hermano->hijos[hermano->n];
    }

    // subir la ultima clave del hermano al padre
    nodo->claves[idx - 1] = hermano->claves[hermano->n - 1];

    hijo->n++;
    hermano->n--;
}

void ArbolB::pedirPrestadoDer(NodoB* nodo, int idx){
    NodoB* hijo = nodo->hijos[idx];
    NodoB* hermano = nodo->hijos[idx + 1];

    // bajar la clave del padre al hijo
    hijo->claves[hijo->n] = nodo->claves[idx];

    // si no es hoja, mover el primer hijo del hermano
    if(!hijo->hoja){
        hijo->hijos[hijo->n + 1] = hermano->hijos[0];
    }

    // subir la primera clave del hermano al padre
    nodo->claves[idx] = hermano->claves[0];

    // mover claves del hermano hacia la izquierda
    for(int i = 1; i < hermano->n; i++){
        hermano->claves[i - 1] = hermano->claves[i];
    }

    // mover hijos si no es hoja
    if(!hermano->hoja){
        for(int i = 1; i <= hermano->n; i++){
            hermano->hijos[i - 1] = hermano->hijos[i];
        }
    }

    hijo->n++;
    hermano->n--;
}

//merge
void ArbolB::fusionar(NodoB* nodo, int idx){
    NodoB* hijo = nodo->hijos[idx];
    NodoB* hermano = nodo->hijos[idx + 1];

    // bajar la clave del padre al hijo (queda en medio)
    hijo->claves[t - 1] = nodo->claves[idx];

    // copiar claves del hermano al hijo
    for(int i = 0; i < hermano->n; i++){
        hijo->claves[i + t] = hermano->claves[i];
    }

    // copiar hijos si no es hoja
    if(!hijo->hoja){
        for(int i = 0; i <= hermano->n; i++){
            hijo->hijos[i + t] = hermano->hijos[i];
        }
    }

    // mover claves del padre hacia la izquierda
    for(int i = idx + 1; i < nodo->n; i++){
        nodo->claves[i - 1] = nodo->claves[i];
    }

    // mover hijos del padre
    for(int i = idx + 2; i <= nodo->n; i++){
        nodo->hijos[i - 1] = nodo->hijos[i];
    }

    // actualizar tamaños
    hijo->n += hermano->n + 1;
    nodo->n--;

    // liberar memoria del hermano
    delete hermano;
}
