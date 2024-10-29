#include "mainHeader.h"

Tiempo tiempoPrincipal;
Tiempo tiempoSecundaria;

Estado estadoActualPrincipal;
Estado estadoActualSecundaria;

Estado estadoAnteriorPrincipal;
Estado estadoAnteriorSecundaria;

bool clk = 0;

DWORD WINAPI hiloPrincipal(LPVOID lpParam) {    
    while (1) {
        semaforoPrincipal(clk, &estadoActualPrincipal, &estadoAnteriorPrincipal, &estadoActualSecundaria, tiempoPrincipal);
        semaforoSecundario(clk, &estadoActualSecundaria,&estadoAnteriorSecundaria, &estadoActualPrincipal, tiempoSecundaria);
        clk = !clk;
        Sleep(500);
        system("cls");
    }
}

int main() {
    HANDLE hilo;   //pthread_t hiloPrincipal
    
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

    printf("Permanecera en rojo hasta que el otro termine su ciclo.\n\n");
    
    
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

    //crear hilo
    hilo = CreateThread(NULL, 0, hiloPrincipal, NULL, 0, NULL);    //pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);

    WaitForSingleObject(hilo, INFINITE);

    //limpia los hilos
    CloseHandle(hilo);

    return 0;
}