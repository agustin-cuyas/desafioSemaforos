#include "mainHeader.h"

long int timerPrincipal = 0;
long int timerSecundaria = 0;
bool sensor = false;
char opcion;   

void cambiarSemaforo(Estado* estado, bool verde, bool amarillo, bool rojo)
{
    estado->verde = verde;
    estado->amarillo = amarillo;
    estado->rojo = rojo;
}

void semaforoPrincipal(Estado* estadoPrincipal, Estado* estadoAnteriorPrincipal, Estado* estadoSecundario, Tiempo tiempoPrincipal)
{
    timerPrincipal++;

    Color color = estadoPrincipal->verde ? VERDE : (estadoPrincipal->amarillo ? AMARILLO : ROJO);
    
    switch (color) {
        case VERDE:
            printf("Carretera principal en verde, timer: %ld \n", timerPrincipal);

            if (timerPrincipal == (tiempoPrincipal.verde - 3)) {
                do {
                    printf("Hay autos en la carretera secundaria? (s/n): ");
                    opcion = getchar();
                } while (opcion != 's' && opcion != 'n');
                
                sensor = opcion == 's' ? 1 : 0;
                while (getchar() != '\n'); // limpiar el buffer
                SetEvent(semaforoSecundarioHandle); //permite continuar al otro hilo
            }
            
            float tiempoVerde = sensor ? tiempoPrincipal.verde : tiempoPrincipal.verde + 15;

            if (timerPrincipal >= tiempoVerde) {
                timerPrincipal = 1; //si tiene que cambiar reinicia el contador
                *estadoAnteriorPrincipal = *estadoPrincipal;
                cambiarSemaforo(estadoPrincipal, 0, 1, 0);    
            }
            break;

        case AMARILLO:
            printf("Carretera principal en amarillo, timer: %ld \n", timerPrincipal);
            if (timerPrincipal+1 >= tiempoPrincipal.amarillo) {
                timerPrincipal = 1;
                if((*estadoAnteriorPrincipal).verde == 1)
                    cambiarSemaforo(estadoPrincipal, 0, 0, 1);
                if((*estadoAnteriorPrincipal).rojo == 1)
                    cambiarSemaforo(estadoPrincipal, 1, 0, 0);
                SetEvent(semaforoSecundarioHandle);
            }
            break;

        case ROJO:
            if((*estadoSecundario).rojo == 1)   //en este caso la condicion de cambio es que el ciclo del otro semaforo haya terminado, no un tiempo fijo.
            {            
                timerPrincipal = 1;
                *estadoAnteriorPrincipal = *estadoPrincipal;
                cambiarSemaforo(estadoPrincipal, 0, 1, 0);
                printf("Carretera principal en amarillo, timer: %i \n", timerPrincipal);
            }
            else
                printf("Carretera principal en rojo, timer: %i \n", timerPrincipal);
            break;       
    }
}

void semaforoSecundario(Estado* estadoSecundaria, Estado* estadoAnteriorSecundaria, Estado* estadoPrincipal, Tiempo tiempoSecundaria)
{
    WaitForSingleObject(semaforoSecundarioHandle, INFINITE);
    timerSecundaria++;

    Color color = (*estadoSecundaria).verde ? VERDE : ((*estadoSecundaria).amarillo ? AMARILLO : ROJO);

    switch (color) {
        case VERDE:
            printf("Carretera secundaria en verde, timer: %ld \n", timerSecundaria);
            if (timerSecundaria +1 >= tiempoSecundaria.verde) {
                timerSecundaria = 1;
                *estadoAnteriorSecundaria = *estadoSecundaria;
                cambiarSemaforo(estadoSecundaria, 0, 1, 0);
            }
            break;

        case AMARILLO:
            printf("Carretera secundaria en amarillo, timer: %ld \n", timerSecundaria);
            if(timerSecundaria+1>tiempoSecundaria.amarillo)
            {
                timerSecundaria = 1;
                if((*estadoAnteriorSecundaria).verde == 1)
                    cambiarSemaforo(estadoSecundaria, 0, 0, 1);
                if((*estadoAnteriorSecundaria).rojo == 1)
                    cambiarSemaforo(estadoSecundaria, 1, 0, 0);
            }
            break;

        case ROJO:
            printf("Carretera secundaria en rojo, timer: %i \n", timerSecundaria);

            if((*estadoPrincipal).rojo == 1)
            { 
                timerSecundaria = 1;
                *estadoAnteriorSecundaria = *estadoSecundaria;
                cambiarSemaforo(estadoSecundaria, 0, 1, 0);
            }
            break;
    }
    ResetEvent(semaforoSecundarioHandle);
}