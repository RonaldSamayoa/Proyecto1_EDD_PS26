#include <iostream>
#include "include/gestor_catalogo.h"
#include "include/producto.h"

int main(){

    // =====================================================
    // CREACION DE PRODUCTOS
    // =====================================================
    Producto* p1 = new Producto{"Pan", "001", "Comida", "2026-01-10", "Bimbo", 5.0, 10};
    Producto* p2 = new Producto{"Leche", "002", "Lacteos", "2026-01-05", "DosPinos", 8.0, 20};
    Producto* p3 = new Producto{"Queso", "003", "Lacteos", "2026-02-01", "Sula", 15.0, 5};

    // =====================================================
    // CREACION DEL GESTOR
    // =====================================================
    GestorCatalogo gestor(10, 3);

    gestor.insertarProducto(p1);
    gestor.insertarProducto(p2);
    gestor.insertarProducto(p3);

    // =====================================================
    // LISTADO INICIAL
    // =====================================================
    std::cout << "\n===== LISTA GENERAL =====\n";
    gestor.listarTodos();

    std::cout << "\n===== LISTA ORDENADA =====\n";
    gestor.listarOrdenado();

    // =====================================================
    // BUSQUEDAS
    // =====================================================
    std::cout << "\n===== BUSQUEDAS =====\n";

    Producto* b1 = gestor.buscarPorNombre("Leche");
    if(b1 != nullptr)
        std::cout << "Por nombre: " << b1->nombre << std::endl;

    Producto* b2 = gestor.buscarPorCodigo("003");
    if(b2 != nullptr)
        std::cout << "Por codigo: " << b2->nombre << std::endl;

    Producto* b3 = gestor.buscarPorFecha("2026-01-10");
    if(b3 != nullptr)
        std::cout << "Por fecha: " << b3->nombre << std::endl;

    auto listaCat = gestor.buscarPorCategoria("Lacteos");
    if(listaCat != nullptr){
        std::cout << "Por categoria (Lacteos):\n";
        listaCat->recorrer([](Producto* p){
            std::cout << "  - " << p->nombre << std::endl;
        });
    }

    // =====================================================
    // ELIMINACION
    // =====================================================
    std::cout << "\n===== ELIMINAR 'Leche' =====\n";

    gestor.eliminarProducto("Leche");

    // =====================================================
    // VERIFICACION POST-ELIMINACION
    // =====================================================
    std::cout << "\n===== VERIFICACION =====\n";

    std::cout << "AVL (nombre): "
              << (gestor.buscarPorNombre("Leche") == nullptr ? "OK" : "ERROR")
              << std::endl;

    std::cout << "HASH (codigo): "
              << (gestor.buscarPorCodigo("002") == nullptr ? "OK" : "ERROR")
              << std::endl;

    std::cout << "ARBOL B (fecha): "
              << (gestor.buscarPorFecha("2026-01-05") == nullptr ? "OK" : "ERROR")
              << std::endl;

    // =====================================================
    // LISTAS DESPUES DE ELIMINAR
    // =====================================================
    std::cout << "\n===== LISTA GENERAL DESPUES =====\n";
    gestor.listarTodos();

    std::cout << "\n===== LISTA ORDENADA DESPUES =====\n";
    gestor.listarOrdenado();

    // =====================================================
    // NOTA IMPORTANTE B+
    // =====================================================
    std::cout << "\n===== CATEGORIA DESPUES (B+) =====\n";

    auto listaCat2 = gestor.buscarPorCategoria("Lacteos");
    if(listaCat2 != nullptr){
        listaCat2->recorrer([](Producto* p){
            std::cout << "  - " << p->nombre << std::endl;
        });
    }

    return 0;
}