#include "mainHeader.h"

int main()
{
    //unsigned long int timer=1;
    short int clock;
    Tiempo tiempoPrincipal;
    Tiempo tiempoSecundaria;

    Estado estadoActualPrincipal;
    Estado estadoActualSecundaria;

    Estado estadoAnteriorPrincipal;
    Estado estadoAnteriorSecundaria;


    tiempoPrincipal.verde = 35; //35
    tiempoPrincipal.amarillo = 5; //5
    
    tiempoSecundaria.verde = 15; //15
    tiempoSecundaria.amarillo = 5; //5

    cambiarSemaforo(&estadoAnteriorPrincipal, 1, 0, 0); //verde
    cambiarSemaforo(&estadoAnteriorSecundaria, 0, 0, 1); //rojo

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

    getchar();
    return 0;
}