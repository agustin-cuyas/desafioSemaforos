#include "mainHeader.hpp"

int main() {
    Estado* estadoInicialPrincipal = new EstadoVerde(5);
    Estado* estadoInicialSecundaria = new EstadoRojo();
    
    SemaforoPrincipal semaforoPrincipal(estadoInicialPrincipal);
    SemaforoSecundaria semaforoSecundaria(estadoInicialSecundaria);

    semaforoPrincipal.ingresarDuracion();
    semaforoSecundaria.ingresarDuracion();

    cin.ignore();   //limpio el buffer 
    system("cls");

    while (true) {

        semaforoPrincipal.ejecutarEstado();
        semaforoSecundaria.ejecutarEstado();

        semaforoPrincipal.cambiarEstado(&semaforoSecundaria);
        semaforoSecundaria.cambiarEstado(&semaforoPrincipal);

        this_thread::sleep_for(chrono::seconds(1));
        system("cls");
    }

    return 0;
}
