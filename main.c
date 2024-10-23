/*
incluir bool para clock y sensor
ver si sensor se puede pedir como char para que quede mas lindo
*/

#include "mainHeader.h"

int main()
{
    bool clock = 0;
    Tiempo tiempoPrincipal;
    Tiempo tiempoSecundaria;

    Estado estadoActualPrincipal;
    Estado estadoActualSecundaria;

    Estado estadoAnteriorPrincipal;
    Estado estadoAnteriorSecundaria;


    tiempoPrincipal.verde = 30; //30
    tiempoPrincipal.amarillo = 5; //5
    
    tiempoSecundaria.verde = 15; //15
    tiempoSecundaria.amarillo = 5; //5


    cambiarSemaforo(&estadoActualPrincipal, 1, 0, 0); //verde
    cambiarSemaforo(&estadoActualSecundaria, 0, 0, 1); //rojo

    while(1)
    {
        semaforoPrincipal(clock, &estadoActualPrincipal, &estadoAnteriorPrincipal, &estadoActualSecundaria, tiempoPrincipal);        
        semaforoSecundario(clock, &estadoActualSecundaria,&estadoAnteriorSecundaria, &estadoActualPrincipal, tiempoSecundaria);

        clock = clock == 1 ? 0 : 1;
        Sleep(500);
        system("cls");
    }

    return 0;
}