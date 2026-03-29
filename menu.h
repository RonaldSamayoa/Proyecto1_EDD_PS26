//
// Created by ronald on 28/3/26.
//

#ifndef PROYECTO1_MENU_H
#define PROYECTO1_MENU_H
#include "include/gestor_catalogo.h"

class Menu {

private:
    GestorCatalogo& gestor;

public:
    // constructor
    Menu(GestorCatalogo& g);

    // inicia el menu
    void iniciar();

private:
    void mostrarMenu();

    // operaciones principales
    void opcionInsertar();
    void opcionBuscarNombre();
    void opcionBuscarCodigo();
    void opcionBuscarCategoria();
    void opcionBuscarRangoFecha();

    void opcionEliminar();

    void opcionListar();
    void opcionListarOrdenado();

    void opcionComparar(); // pendiente
    void cargarDesdeCSV(GestorCatalogo& gestor);
    void opcionDOT();      // pendiente
};

#endif //PROYECTO1_MENU_H
