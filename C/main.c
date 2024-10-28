#include "mainHeader.h"

Tiempo tiempoPrincipal;
Tiempo tiempoSecundaria;

Estado estadoActualPrincipal;
Estado estadoActualSecundaria;

Estado estadoAnteriorPrincipal;
Estado estadoAnteriorSecundaria;

HANDLE semaforoSecundarioHandle;

DWORD WINAPI hiloSemaforoPrincipal(LPVOID lpParam) {    
    while (1) {
        semaforoPrincipal(&estadoActualPrincipal, &estadoAnteriorPrincipal, &estadoActualSecundaria, tiempoPrincipal);
        Sleep(1000);
        system("cls");
    }
}

DWORD WINAPI hiloSemaforoSecundario(LPVOID lpParam) {
    while (1) {
        semaforoSecundario(&estadoActualSecundaria,&estadoAnteriorSecundaria, &estadoActualPrincipal, tiempoSecundaria);
        Sleep(1000);
        system("cls");
    }
}

int main() {
    HANDLE hiloPrincipal, hiloSecundario;

    semaforoSecundarioHandle = CreateEvent(NULL, TRUE, FALSE, NULL);
    
    cambiarSemaforo(&estadoActualPrincipal, 1, 0, 0);
    cambiarSemaforo(&estadoActualSecundaria, 0, 0, 1);

    
    printf("Semaforo calle principal\n"); 
    do {
        printf("Ingrese tiempo del verde (minimo 5s): ");
        scanf("%f", &tiempoPrincipal.verde);
    } while (tiempoPrincipal.verde < 5);  
    do {
        printf("Ingrese tiempo del amarillo (minimo 1s): ");
        scanf("%f", &tiempoPrincipal.amarillo);
    } while (tiempoPrincipal.amarillo < 1);

    printf("Permanecera en rojo hasta que el otro termine su ciclo.\n");
    
    
    printf("Semaforo calle secundaria\n");
    do {
        printf("Ingrese tiempo del verde (minimo 3s): ");
        scanf("%f", &tiempoSecundaria.verde);
    } while (tiempoSecundaria.verde < 3);
    do {
        printf("Ingrese tiempo del amarillo (minimo 1s): ");
        scanf("%f", &tiempoSecundaria.amarillo);
    } while (tiempoSecundaria.amarillo < 1);
    
    printf("Permanecera en rojo hasta que el otro termine su ciclo.\n");
    system("cls");
    while(getchar() != '\n');      //limpio el buffer

    //crear hilos
    hiloPrincipal = CreateThread(NULL, 0, hiloSemaforoPrincipal, NULL, 0, NULL);
    hiloSecundario = CreateThread(NULL, 0, hiloSemaforoSecundario, NULL, 0, NULL);

    WaitForSingleObject(hiloPrincipal, INFINITE);
    WaitForSingleObject(hiloSecundario, INFINITE);

    //limpia los hilos
    CloseHandle(hiloPrincipal);
    CloseHandle(hiloSecundario);
    CloseHandle(semaforoSecundarioHandle);

    return 0;
}