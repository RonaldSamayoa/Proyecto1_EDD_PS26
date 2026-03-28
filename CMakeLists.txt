cmake_minimum_required(VERSION 4.1)
project(Proyecto1)

set(CMAKE_CXX_STANDARD 20)

add_executable(Proyecto1 main.cpp
        gestor_catalogo.cpp
        estructuras/lista_enlazada.cpp
        estructuras/lista_ordenada.cpp
        estructuras/arbol_avl.cpp
        estructuras/tabla_hash.cpp
        estructuras/arbol_b.cpp
        estructuras/arbol_bplus.cpp
        utilidades/lector_csv.cpp
        utilidades/temporizador.cpp
        utilidades/generador_dot.cpp
        utilidades/logger.cpp
        include/producto.h
        include/gestor_catalogo.h
        include/estructuras/lista_enlazada.h
        include/estructuras/lista_ordenada.h
        include/estructuras/arbol_avl.h
        include/estructuras/tabla_hash.h
        include/estructuras/arbol_b.h
        include/estructuras/arbol_bplus.h
        include/utilidades/lector_csv.h
        include/utilidades/temporizador.h
        include/utilidades/generador_dot.h
        include/utilidades/logger.h
        producto.cpp
        menu.cpp
        menu.h)
