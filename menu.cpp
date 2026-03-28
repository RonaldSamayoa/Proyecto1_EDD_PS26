//
// Created by ronald on 28/3/26.
//

#include "menu.h"
#include <iostream>

Menu::Menu(GestorCatalogo& g) : gestor(g) {}

// bucle principal
void Menu::iniciar(){

    int opcion;

    do{
        mostrarMenu();
        std::cin >> opcion;

        switch(opcion){
            case 1: opcionInsertar(); break;
            case 2: opcionBuscarNombre(); break;
            case 3: opcionBuscarCodigo(); break;
            case 4: opcionBuscarCategoria(); break;
            case 5: opcionBuscarRango(); break;
            case 6: opcionEliminar(); break;
            case 7: opcionListar(); break;
            case 8: opcionListarOrdenado(); break;
            case 9: opcionComparar(); break;
            case 10: opcionCSV(); break;
            case 11: opcionDOT(); break;
            case 0: std::cout << "Saliendo...\n"; break;
            default: std::cout << "Opcion invalida\n";
        }

    }while(opcion != 0);
}

// mostrar opciones
void Menu::mostrarMenu(){

    std::cout << "\n===== MENU =====\n";
    std::cout << "1. Agregar producto\n";
    std::cout << "2. Buscar por nombre\n";
    std::cout << "3. Buscar por codigo\n";
    std::cout << "4. Buscar por categoria\n";
    std::cout << "5. Buscar por rango de caducidad\n";
    std::cout << "6. Eliminar producto\n";
    std::cout << "7. Listar productos\n";
    std::cout << "8. Listar productos ordenados\n";
    std::cout << "9. Comparar busquedas\n";
    std::cout << "10. Cargar desde CSV\n";
    std::cout << "11. Visualizar arboles (.dot)\n";
    std::cout << "0. Salir\n";
    std::cout << "Seleccione una opcion: ";
}

// ===== IMPLEMENTADAS =====

void Menu::opcionInsertar(){

    Producto* p = new Producto();

    std::cout << "Nombre: ";
    std::cin >> p->nombre;

    std::cout << "Codigo: ";
    std::cin >> p->codigo_barra;

    std::cout << "Categoria: ";
    std::cin >> p->categoria;

    std::cout << "Fecha (YYYY-MM-DD): ";
    std::cin >> p->fecha_caducidad;

    std::cout << "Marca: ";
    std::cin >> p->marca;

    std::cout << "Precio: ";
    std::cin >> p->precio;

    std::cout << "Stock: ";
    std::cin >> p->stock;

    gestor.insertarProducto(p);

    std::cout << "Producto agregado\n";
}

void Menu::opcionBuscarNombre(){

    std::string nombre;
    std::cout << "Nombre: ";
    std::cin >> nombre;

    Producto* p = gestor.buscarPorNombre(nombre);

    if(p)
        std::cout << "Encontrado: " << p->nombre << std::endl;
    else
        std::cout << "No encontrado\n";
}

void Menu::opcionBuscarCodigo(){

    std::string codigo;
    std::cout << "Codigo: ";
    std::cin >> codigo;

    Producto* p = gestor.buscarPorCodigo(codigo);

    if(p)
        std::cout << "Encontrado: " << p->nombre << std::endl;
    else
        std::cout << "No encontrado\n";
}

void Menu::opcionBuscarCategoria(){

    std::string categoria;
    std::cout << "Categoria: ";
    std::cin >> categoria;

    auto lista = gestor.buscarPorCategoria(categoria);

    if(lista){
        lista->recorrer([](Producto* p){
            std::cout << " - " << p->nombre << std::endl;
        });
    } else {
        std::cout << "Categoria no encontrada\n";
    }
}

void Menu::opcionEliminar(){

    std::string nombre;
    std::cout << "Nombre a eliminar: ";
    std::cin >> nombre;

    gestor.eliminarProducto(nombre);
}

void Menu::opcionListar(){
    gestor.listarTodos();
}

void Menu::opcionListarOrdenado(){
    gestor.listarOrdenado();
}

// ===== PENDIENTES =====

void Menu::opcionBuscarRango(){
    std::cout << "Funcion aun no implementada\n";
}

void Menu::opcionComparar(){
    std::cout << "Funcion aun no implementada\n";
}

void Menu::opcionCSV(){
    std::cout << "Funcion aun no implementada\n";
}

void Menu::opcionDOT(){
    std::cout << "Funcion aun no implementada\n";
}