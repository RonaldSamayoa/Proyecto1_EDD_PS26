//
// Created by ronald on 11/3/26.
//

#ifndef PROYECTO1_GENERADOR_DOT_H
#define PROYECTO1_GENERADOR_DOT_H
#include <string>
#include "../estructuras/arbol_avl.h"
#include "../estructuras/arbol_b.h"
#include "../estructuras/arbol_bplus.h"

class GeneradorDOT {

public:
    // genera el archivo .dot del arbol AVL
    static void generarAVL(ArbolAVL& arbol, std::string nombreArchivo);

    //genera .dot para arbol B
    static void generarB(ArbolB& arbol, std::string nombreArchivo);

    // genera el archivo .dot del arbol B+
    static void generarBPlus(ArbolBPlus& arbol, std::string nombreArchivo);
};
#endif //PROYECTO1_GENERADOR_DOT_H