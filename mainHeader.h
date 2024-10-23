#ifndef MAINHEADER_H
#define MAINHEADER_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <windows.h> //para sleep()

typedef struct 
{
    float verde;
    float amarillo;
    float rojo;

}Tiempo;

typedef struct
{
    bool verde;
    bool amarillo;
    bool rojo;
}Estado;


void cambiarSemaforo(Estado* estado, bool verde, bool amarillo, bool rojo);
void semaforoPrincipal(bool clock, Estado* estadoPrincipal, Estado* estadoAnteriorPrincipal, Estado* estadoSecundario, Tiempo tiempoPrincipal);
void semaforoSecundario(bool clock, Estado* estadoSecundario, Estado* estadoAnteriorSecundaria, Estado* estadoPrincipal, Tiempo tiempoSecundaria);

#endif