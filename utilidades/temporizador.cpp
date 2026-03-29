//
// Created by ronald on 11/3/26.
//
#include "../include/utilidades/temporizador.h"

// iniciar medicion
void Temporizador::iniciar(){
    inicio = std::chrono::high_resolution_clock::now();
}

// detener medicion
void Temporizador::detener(){
    fin = std::chrono::high_resolution_clock::now();
}

// calcular tiempo en milisegundos
double Temporizador::obtenerMilisegundos(){
    return std::chrono::duration<double, std::milli>(fin - inicio).count();
}