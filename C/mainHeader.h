#ifndef MAINHEADER_H
#define MAINHEADER_H

#include <stdlib.h>
#include <stdio.h>
#include <windows.h> //para sleep()

typedef struct 
{
    float verde;
    float amarillo;
    float rojo;

}Tiempo;

typedef struct
{
    short int verde;
    short int amarillo;
    short int rojo;
}Estado;


void cambiarSemaforo(Estado* estado, short int verde, short int amarillo, short int rojo);
void semaforoPrincipal(short int clock, Estado* estadoPrincipal, Estado* estadoAnteriorPrincipal, Estado* estadoSecundario, Tiempo tiempoPrincipal );
void semaforoSecundario(short int clock, Estado* estadoSecundario, Estado* estadoAnteriorSecundaria, Estado* estadoPrincipal, Tiempo tiempoSecundaria);

#endif