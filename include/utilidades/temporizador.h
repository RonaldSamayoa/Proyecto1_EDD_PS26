//
// Created by ronald on 11/3/26.
//

#ifndef PROYECTO1_TEMPORIZADOR_H
#define PROYECTO1_TEMPORIZADOR_H
#include <chrono>

// clase utilitaria para medir tiempos
class Temporizador {

private:
    std::chrono::high_resolution_clock::time_point inicio;
    std::chrono::high_resolution_clock::time_point fin;

public:

    // inicia la medicion
    void iniciar();

    // termina la medicion
    void detener();

    // retorna tiempo en milisegundos
    double obtenerMilisegundos();
};

#endif //PROYECTO1_TEMPORIZADOR_H