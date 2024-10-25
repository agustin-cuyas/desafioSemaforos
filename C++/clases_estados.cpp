#include "mainHeader.hpp"
#include "clases_estados.hpp"

void EstadoVerde::ejecutar(){
    cout << "Verde, timer: " << timer << " segundos." << endl;

    if (timer == (duracionVerde - 2)) {
        char opcion;
        do{
            cout << "Hay autos en la carretera secundaria? (s/n): ";        
            cin >> opcion;
            opcion = tolower(opcion);
        }while(opcion != 's' && opcion != 'n');
        
        sensor = (opcion == 's') ? 1 : 0;
    }
    
    timer++;
}

Estado* EstadoVerde::siguienteEstado(Estado* estadoAnterior, Estado* estadoOtroSemaforo, int duracionVerde, int duracionAmarillo) {
    int tiempoVerde = sensor ? duracionVerde : duracionVerde + 15;
    if (timer > tiempoVerde) {
        return new EstadoAmarillo(duracionAmarillo);
    }
    return this;
}


void EstadoAmarillo::ejecutar() {
    cout << "Amarillo, timer: " << timer << " segundos." << endl;
    timer++;
}

Estado* EstadoAmarillo::siguienteEstado(Estado* estadoAnterior, Estado* estadoOtroSemaforo, int duracionVerde, int duracionAmarillo) {
    if (timer > duracionAmarillo) {
        if (dynamic_cast<EstadoRojo*>(estadoAnterior))
            return new EstadoVerde(duracionVerde);
        else
            return new EstadoRojo(); 
    }
    return this;
}


void EstadoRojo::ejecutar() {
    cout << "Rojo, timer: " << timer << " segundos." << endl;
    timer++;
}

Estado* EstadoRojo::siguienteEstado(Estado* estadoAnterior, Estado* estadoOtroSemaforo, int duracionVerde, int duracionAmarillo) {
    if (dynamic_cast<EstadoRojo*>(estadoOtroSemaforo)) 
        return new EstadoAmarillo(duracionAmarillo);

    return this;
}