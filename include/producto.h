//
// Created by ronald on 11/3/26.
//

#ifndef PROYECTO1_PRODUCTO_H
#define PROYECTO1_PRODUCTO_H
#include <string>

class Producto {
public:
    std::string nombre;
    std::string codigo_barra;
    std::string categoria;
    std::string fecha_caducidad;
    std::string marca;

    double precio;
    int stock;

    Producto();

    Producto(
        std::string nombre,
        std::string codigo_barra,
        std::string categoria,
        std::string fecha_caducidad,
        std::string marca,
        double precio,
        int stock
    );
};

// compara si dos productos tienen el mismo codigo de barras
bool compararCodigo(Producto* a, Producto* b);

// compara si dos productos tienen el mismo nombre
bool compararNombre(Producto* a, Producto* b);

// compara categorias
bool compararCategoria(Producto* a, Producto* b);

// compara fecha de caducidad
bool compararFecha(Producto* a, Producto* b);

bool menorPorPrecio(Producto* a, Producto* b);

bool menorPorNombre(Producto* a, Producto* b);

#endif //PROYECTO1_PRODUCTO_H