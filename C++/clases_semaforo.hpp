#ifndef CLASES_SEMAFORO
#define CLASES_SEMAFORO

class Semaforo {
    public:
        Semaforo(Estado* estadoInicial) : estadoActual(estadoInicial), estadoAnterior(nullptr) {}
        void cambiarEstado(Semaforo* otroSemaforo);
        virtual void ingresarDuracion() = 0;
        virtual void ejecutarEstado() = 0;
        Estado* getEstadoActual() { return estadoActual; }  //para conocer estado del otro semaforo

    protected:
        Estado* estadoActual;
        Estado* estadoAnterior;
        int duracionVerde;
        int duracionAmarillo;
};

class SemaforoPrincipal : public Semaforo {
    public:
        SemaforoPrincipal(Estado* estadoInicial);
        void ingresarDuracion() override;
        void ejecutarEstado() override;
};

class SemaforoSecundaria : public Semaforo {
    public:
        SemaforoSecundaria(Estado* estadoInicial);
        void ingresarDuracion() override;
        void ejecutarEstado() override;
};

#endif