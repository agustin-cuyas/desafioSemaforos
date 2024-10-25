#include "mainHeader.hpp"

void Semaforo::cambiarEstado(Semaforo* otroSemaforo) {
    Estado* nuevoEstado = estadoActual->siguienteEstado(estadoAnterior, otroSemaforo->getEstadoActual(), duracionVerde, duracionAmarillo);

   if (dynamic_cast<EstadoRojo*>(nuevoEstado) && dynamic_cast<EstadoRojo*>(otroSemaforo->getEstadoActual())) {  //sin esta logica habia un momento que ambos estaban en rojo.
        if (!dynamic_cast<EstadoAmarillo*>(otroSemaforo->getEstadoActual())) {
            otroSemaforo->estadoAnterior = otroSemaforo->estadoActual;
            otroSemaforo->estadoActual = new EstadoAmarillo(duracionAmarillo);
        }
    }

    if(nuevoEstado != estadoActual) {
        delete estadoAnterior;
        estadoAnterior = estadoActual;
        estadoActual = nuevoEstado;
    }
}

SemaforoPrincipal::SemaforoPrincipal(Estado *estadoInicial): Semaforo(estadoInicial) {
    estadoActual = estadoInicial;
}

void SemaforoPrincipal::ingresarDuracion()
{
    cout << "Semaforo calle principal" << endl;
    do{
    cout << "Ingrese tiempo del verde (minimo 5s): ";
    cin >> duracionVerde;
    }while(duracionVerde<5);
    do{
    cout << "Ingrese tiempo del amarillo (minimo 1s): ";
    cin >> duracionAmarillo;
    }while(duracionAmarillo<1);
    cout << "Permanecera en rojo hasta que el otro termine su ciclo.\n\n";
}

void SemaforoPrincipal::ejecutarEstado() {
    cout << "Carretera principal en ";
    estadoActual->ejecutar();
}

SemaforoSecundaria::SemaforoSecundaria(Estado* estadoInicial) : Semaforo(estadoInicial) {
    estadoActual = estadoInicial;
}

void SemaforoSecundaria::ingresarDuracion()
{
    cout << "Semaforo calle secundaria" << endl;
    do{
    cout << "Ingrese tiempo del verde (minimo 3s): ";
    cin >> duracionVerde;
    }while(duracionVerde<3);
    do{
    cout << "Ingrese tiempo del amarillo (minimo 1s): ";
    cin >> duracionAmarillo;
    }while(duracionAmarillo<1);
    cout << "Permanecera en rojo hasta que el otro termine su ciclo.\n";
}

void SemaforoSecundaria::ejecutarEstado()
{
    cout << "Carretera secundaria en ";
    estadoActual->ejecutar();
}