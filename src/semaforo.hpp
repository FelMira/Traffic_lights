#ifndef SEMAFORO_HPP
#define SEMAFORO_HPP
#include "mbed.h"

extern DigitalOut semaforo[];
extern InterruptIn botao;
void desligar_semaforo();
void mudar_led();
void piscar();
void ativar_timer();
void desativar_timer();

#endif