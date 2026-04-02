//
// Created by ronald on 11/3/26.
//
#include "include/gestor_catalogo.h"
#include <iostream>
#include "include/utilidades/temporizador.h"
#include <regex> // para validar fecha

// constructor
GestorCatalogo::GestorCatalogo(int capacidadHash, int gradoB)
    : hash(capacidadHash), arbolB(gradoB), arbolBPlus(gradoB) {
    //inicializar lista ordenada por nombre
    listaOrdenada = new ListaOrdenada<Producto *>(compararNombreOrden);
}

// insertar en todas las estructuras
bool GestorCatalogo::insertarProducto(Producto* producto){
    std::string error;

    if(!validarProducto(producto, error)){
        std::cout << "Error en producto [" << producto->nombre << "]: "
                  << error << std::endl;
        return false;
    }

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

bool GestorCatalogo::insertarProductoSinValidar(Producto* producto){
    lista.insertarFinal(producto);
    listaOrdenada->insertar(producto);
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

// compara tiempos de busqueda entre lista y AVL
void GestorCatalogo::compararBusqueda(std::string nombre){
    Temporizador tLista, tAVL;

    Producto* encontradoLista = nullptr;
    Producto* encontradoAVL = nullptr;

    // numero de veces que se repite la busqueda
    // esto se hace porque una sola busqueda es demasiado rapida
    // y puede dar tiempo 0, entonces repetimos muchas veces
    // para obtener un tiempo medible y comparable
    int repeticiones = 10000;

    // ===== BUSQUEDA EN LISTA =====
    tLista.iniciar();
    // repetimos la busqueda muchas veces
    for(int i = 0; i < repeticiones; i++){
        NodoLista<Producto*>* actual = lista.obtenerCabeza();

        while(actual != nullptr){

            if(actual->dato->nombre == nombre){
                encontradoLista = actual->dato;
                break;
            }
            actual = actual->siguiente;
        }
    }
    tLista.detener();

    // ===== BUSQUEDA EN AVL =====
    tAVL.iniciar();
    // igual, repetimos muchas veces
    for(int i = 0; i < repeticiones; i++){
        encontradoAVL = avl.buscar(nombre);
    }

    tAVL.detener();

    // ===== RESULTADOS =====
    std::cout << "\n===== RESULTADOS =====\n";

    std::cout << "Lista (tiempo en milisegundos): "
              << tLista.obtenerMilisegundos() << std::endl;

    std::cout << "AVL (tiempo en milisegundos): "
              << tAVL.obtenerMilisegundos() << std::endl;

    if(encontradoAVL)
        std::cout << "Producto encontrado: " << encontradoAVL->nombre << std::endl;
    else
        std::cout << "Producto no encontrado\n";
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

ArbolAVL& GestorCatalogo::obtenerAVL(){
    return avl;
}

ArbolB& GestorCatalogo::obtenerArbolB(){
    return arbolB;
}

ArbolBPlus& GestorCatalogo::obtenerArbolBPlus(){
    return arbolBPlus;
}

// valida si un producto es correcto
bool GestorCatalogo::validarProducto(Producto* p, std::string& error){
    // ===== CAMPOS VACIOS =====
    if(p->nombre.empty() || p->codigo_barra.empty() || p->categoria.empty()
       || p->fecha_caducidad.empty() || p->marca.empty()){
        error = "Campos vacios";
        return false;
       }

    // ===== CODIGO DUPLICADO =====
    if(buscarPorCodigo(p->codigo_barra) != nullptr){
        error = "Codigo duplicado";
        return false;
    }

    // ===== NOMBRE DUPLICADO =====
    if(buscarPorNombre(p->nombre) != nullptr){
        error = "Nombre duplicado";
        return false;
    }

    // ===== FORMATO DE FECHA (YYYY-MM-DD) =====
    std::regex formatoFecha("^\\d{4}-\\d{2}-\\d{2}$");

    if(!std::regex_match(p->fecha_caducidad, formatoFecha)){
        error = "Formato de fecha invalido (YYYY-MM-DD)";
        return false;
    }

    // ===== VALIDACION REAL DE FECHA =====
    int anio = std::stoi(p->fecha_caducidad.substr(0,4));
    int mes  = std::stoi(p->fecha_caducidad.substr(5,2));
    int dia  = std::stoi(p->fecha_caducidad.substr(8,2));

    // validar mes
    if(mes < 1 || mes > 12){
        error = "Mes invalido";
        return false;
    }

    // dias por mes
    int diasMes[] = {31,28,31,30,31,30,31,31,30,31,30,31};

    // validar dia
    if(dia < 1 || dia > diasMes[mes-1]){
        error = "Dia invalido";
        return false;
    }

    // ===== PRECIO =====
    if(p->precio <= 0){
        error = "Precio negativo o igual a cero";
        return false;
    }

    // ===== STOCK =====
    if(p->stock <= 0){
        error = "Stock negativo o igual a cero";
        return false;
    }

    return true; //correcto
}

bool GestorCatalogo::validarProductoSimple(Producto* p, std::string& error){

    if(p->nombre.empty() || p->codigo_barra.empty() || p->categoria.empty()
       || p->fecha_caducidad.empty() || p->marca.empty()){
        error = "Campos vacios";
        return false;
       }

    std::regex formatoFecha("^\\d{4}-\\d{2}-\\d{2}$");

    if(!std::regex_match(p->fecha_caducidad, formatoFecha)){
        error = "Formato de fecha invalido (YYYY-MM-DD)";
        return false;
    }

    // ===== VALIDACION REAL DE FECHA =====
    int anio = std::stoi(p->fecha_caducidad.substr(0,4));
    int mes  = std::stoi(p->fecha_caducidad.substr(5,2));
    int dia  = std::stoi(p->fecha_caducidad.substr(8,2));

    // validar mes
    if(mes < 1 || mes > 12){
        error = "Mes invalido";
        return false;
    }

    // dias por mes
    int diasMes[] = {31,28,31,30,31,30,31,31,30,31,30,31};

    // validar dia
    if(dia < 1 || dia > diasMes[mes-1]){
        error = "Dia invalido";
        return false;
    }

    if(p->precio <= 0){
        error = "Precio invalido";
        return false;
    }

    if(p->stock <= 0){
        error = "Stock invalido";
        return false;
    }

    return true;
}