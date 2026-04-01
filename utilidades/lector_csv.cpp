//
// Created by ronald on 11/3/26.
//
#include "../include/utilidades/lector_csv.h"
#include <fstream>
#include <sstream>
#include <iostream>

// lee archivo CSV y devuelve lista de productos
std::vector<Producto*> LectorCSV::leerArchivo(std::string ruta){

    std::vector<Producto*> productos;

    std::ifstream archivo(ruta);

    // si no se puede abrir
    if(!archivo.is_open()){
        std::cout << "Error al abrir archivo\n";
        return productos;
    }

    std::string linea;

    // saltar encabezado
    getline(archivo, linea);

    // leer linea por linea
    while(getline(archivo, linea)){

        std::stringstream ss(linea);
        std::string dato;

        std::vector<std::string> campos;

        while(getline(ss, dato, ',')){
            campos.push_back(dato);
        }

        // validar cantidad de campos
        if(campos.size() != 7){
            std::cout << "[ERROR CSV] Linea ignorada (columnas incorrectas): "
                      << linea << std::endl;
            continue;
        }

        try{
            // convertir valores numericos SEGURO
            double precio = std::stod(campos[5]);
            int stock = std::stoi(campos[6]);

            Producto* p = new Producto{
                campos[0],
                campos[1],
                campos[2],
                campos[3],
                campos[4],
                precio,
                stock
            };

            productos.push_back(p);

        }catch(const std::exception& e){
            std::cout << "[ERROR CSV] Linea ignorada (conversion invalida): "
                      << linea << std::endl;
            continue; // no truena el programa
        }
    }

    archivo.close();
    return productos;
}