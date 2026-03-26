//
// Created by ronald on 11/3/26.
//
#include "include/producto.h"

Producto::Producto() {}

Producto::Producto(
        std::string nombre,
        std::string codigo_barra,
        std::string categoria,
        std::string fecha_caducidad,
        std::string marca,
        double precio,
        int stock
) {
    this->nombre = nombre;
    this->codigo_barra = codigo_barra;
    this->categoria = categoria;
    this->fecha_caducidad = fecha_caducidad;
    this->marca = marca;
    this->precio = precio;
    this->stock = stock;
}

// compara codigo de barras
bool compararCodigo(Producto* a, Producto* b){
    return a->codigo_barra == b->codigo_barra;
}

// compara nombre
bool compararNombre(Producto* a, Producto* b){
    return a->nombre == b->nombre;
}

bool compararNombreOrden(Producto* a, Producto* b){
    return a->nombre < b->nombre;
}

// compara categoria
bool compararCategoria(Producto* a, Producto* b){
    return a->categoria == b->categoria;
}

// compara fecha de caducidad
bool compararFecha(Producto* a, Producto* b) {
    return a->fecha_caducidad == b->fecha_caducidad;
}

bool menorPorPrecio(Producto* a, Producto* b){
    return a->precio < b->precio;
}

bool menorPorNombre(Producto* a, Producto* b) {
    return a->nombre < b->nombre;
}