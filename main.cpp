#include "menu.h"

int main(){

    GestorCatalogo gestor(10, 3);
    Menu menu(gestor);

    menu.iniciar();

    return 0;
}