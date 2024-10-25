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

    
    cambiarSemaforo(&estadoActualPrincipal, 1, 0, 0); //verde
    cambiarSemaforo(&estadoActualSecundaria, 0, 0, 1); //rojo

    printf("Semaforo calle principal\n"); 
    do{
    printf("Ingrese tiempo del verde (minimo 5s): ");
    scanf("%f",&tiempoPrincipal.verde); //min5
    } while(tiempoPrincipal.verde<5);  
    do{
    printf("Ingrese tiempo del amarillo (minimo 1s): ");
    scanf("%f",&tiempoPrincipal.amarillo);  //min1
    }while(tiempoPrincipal.amarillo<1);

    printf("Permanecera en rojo hasta que el otro termine su ciclo.\n");
    
    printf("Semaforo calle secundaria\n");
    do{
    printf("Ingrese tiempo del verde (minimo 3s): ");
    scanf("%f",&tiempoSecundaria.verde);    //min3
    }while(tiempoSecundaria.verde<3);
    do{
    printf("Ingrese tiempo del amarillo (minimo 1s): ");
    scanf("%f",&tiempoSecundaria.amarillo); //min1
    }while(tiempoSecundaria.amarillo<1);
    

    printf("Permanecera en rojo hasta que el otro termine su ciclo.\n");
    system("cls");

    while(getchar() != '\n');      //limpio el buffer

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