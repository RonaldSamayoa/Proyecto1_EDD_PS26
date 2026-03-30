//
// Created by ronald on 28/3/26.
//
#include "menu.h"
#include <iostream>
#include "include/utilidades/lector_csv.h"
#include "include/utilidades/generador_dot.h"

Menu::Menu(GestorCatalogo& g) : gestor(g) {}
// bucle principal
void Menu::iniciar(){
    int opcion;

    do{
        mostrarMenu();
        std::cin >> opcion;

        switch(opcion){
            case 1:
                opcionInsertar();
                break;
            case 2:
                opcionBuscarNombre();
                break;
            case 3:
                opcionBuscarCodigo();
                break;
            case 4:
                opcionBuscarCategoria();
                break;
            case 5:
                opcionBuscarRangoFecha();
                break;
            case 6:
                opcionEliminar();
                break;
            case 7:
                opcionListar();
                break;
            case 8:
                opcionListarOrdenado();
                break;
            case 9:
                opcionComparar();
                break;
            case 10:
                cargarDesdeCSV(gestor);
                break;
            case 11:
                opcionDOT();
                break;
            case 0:
                std::cout << "Saliendo...\n";
                break;
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
    std::cout << "9. Comparar busquedas (Lista vs AVL)\n";
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

//buscar por fechas de caducidad
void Menu::opcionBuscarRangoFecha(){
    std::string inicio, fin;

    std::cout << "Fecha inicio (YYYY-MM-DD): ";
    std::cin >> inicio;

    std::cout << "Fecha fin (YYYY-MM-DD): ";
    std::cin >> fin;

    auto resultado = gestor.buscarPorRango(inicio, fin);

    if(resultado.estaVacia()){
        std::cout << "No se encontraron productos en ese rango\n";
        return;
    }

    resultado.recorrer([](Producto* p){
        std::cout << " - " << p->nombre
                  << " (" << p->fecha_caducidad << ")\n";
    });
}

void Menu::opcionComparar(){
    std::string nombre;
    std::cout << "Nombre a buscar: ";
    std::cin >> nombre;

    gestor.compararBusqueda(nombre);
}

void Menu::opcionDOT(){
    // ===== AVL =====
    std::string rutaAVL = "../output/avl.dot";
    GeneradorDOT::generarAVL(gestor.obtenerAVL(), rutaAVL);

    std::cout << "AVL generado en: " << rutaAVL << std::endl;
    system("dot -Tpng ../output/avl.dot -o ../output/avl.png");

    // ===== ARBOL B =====
    std::string rutaB = "../output/arbol_b.dot";

    GeneradorDOT::generarB(gestor.obtenerArbolB(), rutaB);
    std::cout << "Arbol B generado en: " << rutaB << std::endl;

    system("dot -Tpng ../output/arbol_b.dot -o ../output/arbol_b.png");
    std::cout << "\nImagenes generadas en carpeta /output\n";
}

void Menu::cargarDesdeCSV(GestorCatalogo& gestor){
    std::string ruta = "../datos/productos.csv";

    std::vector<Producto*> productos = LectorCSV::leerArchivo(ruta);

    if(productos.empty()){
        std::cout << "No se cargaron productos\n";
        return;
    }

    int insertados = 0;

    for(auto p : productos){
        //validar duplicados por codigo
        if(gestor.buscarPorCodigo(p->codigo_barra) != nullptr){
            std::cout << "Codigo duplicado ignorado: " << p->codigo_barra << "\n";
            continue;
        }

        gestor.insertarProducto(p);
        insertados++;
    }

    std::cout << "Productos insertados: " << insertados << std::endl;
}