#ifndef MAINHEADER_H
#define MAINHEADER_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <windows.h> // para Sleep()

typedef struct 
{
    float verde;
    float amarillo;
    float rojo;
} Tiempo;

typedef struct
{
    bool verde;
    bool amarillo;
    bool rojo;
} Estado;

typedef enum
{
    VERDE,
    AMARILLO,
    ROJO
} Color;

void cambiarSemaforo(Estado* estado, bool verde, bool amarillo, bool rojo);
void semaforoPrincipal(Estado* estadoPrincipal, Estado* estadoAnteriorPrincipal, Estado* estadoSecundario, Tiempo tiempoPrincipal);
void semaforoSecundario(Estado* estadoSecundario, Estado* estadoAnteriorSecundaria, Estado* estadoPrincipal, Tiempo tiempoSecundaria);
DWORD WINAPI hiloSemaforoPrincipal(LPVOID lpParam);
DWORD WINAPI hiloSemaforoSecundario(LPVOID lpParam);
//extern HANDLE semaforoSecundarioHandle; 
extern HANDLE hiloSecundarioHandle;
//extern HANDLE hiloPrincipalHandle;



#endif
