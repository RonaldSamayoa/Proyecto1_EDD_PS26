//
// Created by ronald on 11/3/26.
//

#ifndef PROYECTO1_LECTOR_CSV_H
#define PROYECTO1_LECTOR_CSV_H
#include <string>
#include <vector>
#include "../producto.h"

class LectorCSV {

public:
    static std::vector<Producto*> leerArchivo(std::string ruta);
};
#endif //PROYECTO1_LECTOR_CSV_H