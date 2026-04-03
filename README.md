# Proyecto1_EDD_PS26

## Sistema de Gestión de Productos

Sistema desarrollado en C++ que permite gestionar productos utilizando múltiples estructuras de datos implementadas desde cero.

## Características

* Registro manual de productos
* Carga masiva desde archivo CSV
* Búsquedas por:

    * Nombre (Árbol AVL)
    * Código de barras (Tabla Hash)
    * Categoría (Árbol B+)
    * Rango de fechas (Árbol B)
* Eliminación de productos
* Comparación de rendimiento (Lista vs AVL)
* Generación automática de visualizaciones (.dot → .png)

## Estructuras implementadas

* Lista Enlazada
* Lista Enlazada Ordenada
* Árbol AVL
* Tabla Hash
* Árbol B
* Árbol B+

## Requisitos

* Sistema Linux (Ubuntu recomendado)
* g++
* CMake 3.16 o superior
* Graphviz (para visualización de árboles)

Verificar instalación:
g++ --version
cmake --version
dot -V

Si Graphviz no está instalado:
sudo apt install graphviz

## Compilación y ejecución

Abrir una terminal y ubicarse en la carpeta raíz del proyecto (donde se encuentra CMakeLists.txt):
cd /ruta/del/proyecto

Crear carpeta de compilación:
mkdir build
cd build

Generar archivos de compilación:
cmake ..

Compilar:
make

Ejecutar el programa:
./Proyecto

Nota: El nombre del ejecutable puede variar según lo definido en CMakeLists.txt.

## Carga de datos

Ubicar el archivo CSV en:
datos/productos.csv

Luego, dentro del programa seleccionar:
10. Cargar desde CSV

## Generación de árboles (.dot → .png)

Seleccionar en el menú:
11. Visualizar arboles (.dot)

El sistema ejecuta automáticamente:
dot -Tpng ../output/avl.dot -o ../output/avl.png
dot -Tpng ../output/arbol_b.dot -o ../output/arbol_b.png
dot -Tpng ../output/arbol_bplus.dot -o ../output/arbol_bplus.png

## Consideraciones importantes

Al trabajar con grandes volúmenes de datos (más de 1000 productos), Graphviz puede mostrar advertencias como:
graph is too large for cairo-renderer bitmaps

Este mensaje no representa un error; las imágenes se generan correctamente.

Para mejor calidad, se recomienda usar formato SVG:
dot -Tsvg archivo.dot -o archivo.svg

## Estructura del proyecto

Proyecto/
│
├── src/
├── include/
├── datos/
│   └── productos.csv
├── output/
│   ├── avl.dot / avl.png
│   ├── arbol_b.dot / arbol_b.png
│   └── arbol_bplus.dot / arbol_bplus.png
├── CMakeLists.txt
└── main.cpp

## Observaciones

Este proyecto fue desarrollado sin el uso de estructuras estándar de C++ (STL), con el objetivo de reforzar el manejo de memoria dinámica, la implementación de Tipos Abstractos de Datos y el diseño de estructuras complejas.
