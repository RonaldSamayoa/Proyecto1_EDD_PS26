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

        // separar por comas
        while(getline(ss, dato, ',')){
            campos.push_back(dato);
        }

        // validar que tenga todos los campos
        if(campos.size() != 7)
            continue;

        // crear producto
        Producto* p = new Producto{
            campos[0],                 // nombre
            campos[1],                 // codigo
            campos[2],                 // categoria
            campos[3],                 // fecha
            campos[4],                 // marca
            stod(campos[5]),           // precio
            stoi(campos[6])            // stock
        };

        productos.push_back(p);
    }

    archivo.close();
    return productos;
}