#include "mainHeader.h"

long int timerPrincipal = 1;
long int timerSecundaria = 1;
short int sensor = 0;

void cambiarSemaforo(Estado* estado, short int verde, short int amarillo, short int rojo)
{
    (*estado).verde=verde;
    (*estado).amarillo=amarillo;
    (*estado).rojo=rojo;
}

void semaforoPrincipal(short int clock, Estado* estadoPrincipal, Estado* estadoAnteriorPrincipal, Estado* estadoSecundario, Tiempo tiempoPrincipal)
{
    
    if (clock == 1)
        timerPrincipal++;   //cuenta cada un segundo

    if((*estadoPrincipal).verde == 1) 
    {
        printf("Carretera principal en verde, timer: %i \n", timerPrincipal);

        if(timerPrincipal == (tiempoPrincipal.verde - 5) && clock == 1)
        {    
            printf("Hay autos en la carretera secundaria? (1: Sí, 0: No):");    //pregunta solo una vez
            scanf("%d", &sensor);
        }
        // Extender el tiempo en verde si no hay vehículos en la carretera secundaria
        float tiempoVerde = sensor ? tiempoPrincipal.verde : tiempoPrincipal.verde + 15;    //habria que crear una constante para 15

        if(timerPrincipal+1>tiempoVerde)
        {
            timerPrincipal = 1; //si tiene que cambiar reinicia el contador
            *estadoAnteriorPrincipal = *estadoPrincipal;
            cambiarSemaforo(estadoPrincipal, 0, 1, 0);
        
        }
    }
    else if((*estadoPrincipal).amarillo==1)
    {   
        printf("Carretera principal en amarillo, timer: %i \n", timerPrincipal);
        if(timerPrincipal+1>tiempoPrincipal.amarillo)
        {
            timerPrincipal = 1;
            if((*estadoAnteriorPrincipal).verde == 1)
                cambiarSemaforo(estadoPrincipal, 0, 0, 1);
            if((*estadoAnteriorPrincipal).rojo == 1)
                cambiarSemaforo(estadoPrincipal, 1, 0, 0);
        }
    }
    else if((*estadoPrincipal).rojo == 1)
    {
        if((*estadoSecundario).rojo == 1)   //en este caso la condicion de cambio es que el ciclo del otro semaforo haya terminado, no un tiempo fijo.
        {            
            timerPrincipal = 1;
            *estadoAnteriorPrincipal = *estadoPrincipal;
            cambiarSemaforo(estadoPrincipal, 0, 1, 0);
            printf("Carretera principal en amarillo, timer: %i \n", timerPrincipal);
        }
        else
            printf("Carretera principal en rojo, timer: %i \n", timerPrincipal);
    }
}

void semaforoSecundario(short int clock, Estado* estadoSecundaria, Estado* estadoAnteriorSecundaria, Estado* estadoPrincipal, Tiempo tiempoSecundaria)
{
    if (clock == 1)
        timerSecundaria++;

    if((*estadoSecundaria).verde == 1) 
    {
        printf("Carretera secundaria en verde, timer: %i \n", timerSecundaria);
        if(timerSecundaria+1>tiempoSecundaria.verde)
        {
            timerSecundaria = 1;
            *estadoAnteriorSecundaria = *estadoSecundaria;
            cambiarSemaforo(estadoSecundaria, 0, 1, 0);
        
        }
    }
    else if((*estadoSecundaria).amarillo==1)
    {   
        printf("Carretera secundaria en amarillo, timer: %i \n", timerSecundaria);
        if(timerSecundaria+1>tiempoSecundaria.amarillo)
        {
            timerSecundaria = 1;
            if((*estadoAnteriorSecundaria).verde == 1)
                cambiarSemaforo(estadoSecundaria, 0, 0, 1);
            if((*estadoAnteriorSecundaria).rojo == 1)
                cambiarSemaforo(estadoSecundaria, 1, 0, 0);
        }
    }
    else if((*estadoSecundaria).rojo == 1)
    {
        printf("Carretera secundaria en rojo, timer: %i \n", timerSecundaria);

        if((*estadoPrincipal).rojo == 1)
        { 
            timerSecundaria = 1;
            *estadoAnteriorSecundaria = *estadoSecundaria;
            cambiarSemaforo(estadoSecundaria, 0, 1, 0);
        }
    }
}