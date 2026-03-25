#include <iostream>

// estructuras
#include "include/estructuras/arbol_avl.h"
#include "include/estructuras/tabla_hash.h"
#include "include/estructuras/arbol_b.h"
#include "include/estructuras/arbol_bplus.h"
#include "include/estructuras/lista_enlazada.h"
#include "include/estructuras/lista_ordenada.h"
#include "include/gestor_catalogo.h"

#include "include/producto.h"

int main(){

    // ===== CREACION DE PRODUCTOS =====
    Producto* p1 = new Producto{"Pan", "001", "Comida", "2026-01-10", "Bimbo", 5.0, 10};
    Producto* p2 = new Producto{"Leche", "002", "Lacteos", "2026-01-05", "DosPinos", 8.0, 20};
    Producto* p3 = new Producto{"Queso", "003", "Lacteos", "2026-02-01", "Sula", 15.0, 5};


    // =====================================================
    // PRUEBA LISTA ENLAZADA
    // =====================================================
    std::cout << "\n===== LISTA ENLAZADA =====\n";

    ListaEnlazada<Producto*> lista;
    lista.insertarFinal(p1);
    lista.insertarFinal(p2);
    lista.insertarFinal(p3);

    lista.recorrer([](Producto* p){
        std::cout << p->nombre << std::endl;
    });

    std::cout << "\n===== LISTA ORDENADA (POR NOMBRE) =====\n";

    // funcion de comparacion
    auto compararNombre = [](Producto* a, Producto* b){
        return a->nombre < b->nombre;
    };

    ListaOrdenada<Producto*> listaOrd(compararNombre);

    listaOrd.insertar(p1);
    listaOrd.insertar(p2);
    listaOrd.insertar(p3);

    listaOrd.recorrer([](Producto* p){
        std::cout << p->nombre << std::endl;
    });

    // =====================================================
    // PRUEBA AVL (orden por nombre)
    // =====================================================
    std::cout << "\n===== AVL (INORDER) =====\n";

    ArbolAVL avl;
    avl.insertar(p1);
    avl.insertar(p2);
    avl.insertar(p3);

    avl.inorder(); // deberia imprimir orden alfabetico


    // =====================================================
    //PRUEBA HASH (busqueda por codigo)
    // =====================================================
    std::cout << "\n===== HASH =====\n";

    TablaHash hash(10);
    hash.insertar(p1);
    hash.insertar(p2);
    hash.insertar(p3);

    Producto* encontrado = hash.buscar("002");

    if(encontrado != nullptr){
        std::cout << "Encontrado: " << encontrado->nombre << std::endl;
    } else {
        std::cout << "No encontrado" << std::endl;
    }


    // =====================================================
    //PRUEBA ARBOL B (busqueda por fecha)
    // =====================================================
    std::cout << "\n===== ARBOL B =====\n";

    ArbolB b(3);
    b.insertar(p1);
    b.insertar(p2);
    b.insertar(p3);

    Producto* encontradoB = b.buscar("2026-01-05");

    if(encontradoB != nullptr){
        std::cout << "Encontrado (fecha): " << encontradoB->nombre << std::endl;
    } else {
        std::cout << "No encontrado en B" << std::endl;
    }


    // =====================================================
    //PRUEBA ARBOL B+ (por categoria)
    // =====================================================
    std::cout << "\n===== ARBOL B+ =====\n";

    ArbolBPlus bplus(3);
    bplus.insertar(p1);
    bplus.insertar(p2);
    bplus.insertar(p3);

    bplus.recorrerCategorias();

    std::cout << "\n===== GESTOR CATALOGO =====\n";

    GestorCatalogo gestor(10, 3);

    gestor.insertarProducto(p1);
    gestor.insertarProducto(p2);
    gestor.insertarProducto(p3);

    // buscar por nombre
    Producto* r1 = gestor.buscarPorNombre("Leche");
    if(r1 != nullptr)
        std::cout << "Nombre: " << r1->nombre << std::endl;

    // buscar por codigo
    Producto* r2 = gestor.buscarPorCodigo("003");
    if(r2 != nullptr)
        std::cout << "Codigo: " << r2->nombre << std::endl;

    // buscar por fecha
    Producto* r3 = gestor.buscarPorFecha("2026-01-10");
    if(r3 != nullptr)
        std::cout << "Fecha: " << r3->nombre << std::endl;

    // buscar por categoria
    auto listaCat = gestor.buscarPorCategoria("Lacteos");

    if(listaCat != nullptr){
        std::cout << "Categoria Lacteos:\n";
        listaCat->recorrer([](Producto* p){
            std::cout << "  - " << p->nombre << std::endl;
        });
    }

    // =====================================================
    //PRUEBA ELIMINACION AVL
    // =====================================================
    std::cout << "\n===== AVL DESPUES DE ELIMINAR 'Pan' =====\n";

    avl.eliminar("Pan");
    avl.inorder();


    return 0;
}