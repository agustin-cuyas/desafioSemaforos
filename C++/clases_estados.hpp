#ifndef CLASES_ESTADO
#define CLASES_ESTADO

class Estado {
    public:
        virtual void ejecutar() = 0;
        virtual Estado* siguienteEstado(Estado* estadoAnterior, Estado* estadoOtroSemaforo, int duracionVerde, int duracionAmarillo) = 0;
};

class EstadoVerde : public Estado {
    public:
        EstadoVerde(int duracion) : duracionVerde(duracion), timer(1), sensor(0) {} //este estado tiene un parametro extra para verificar el sensor
        void ejecutar() override;
        Estado* siguienteEstado(Estado* estadoAnterior, Estado* estadoOtroSemaforoo, int duracionVerde, int duracionAmarillo) override;
        
    protected:
        int timer;
        int duracionVerde;
        bool sensor;    
};

class EstadoAmarillo : public Estado {
public:
    EstadoAmarillo(int duracion) : duracionAmarillo(duracion), timer(1) {}
    void ejecutar() override;
    Estado* siguienteEstado(Estado* estadoAnterior, Estado* estadoOtroSemaforoo, int duracionVerde, int duracionAmarillo) override;
    
protected:
    int timer;
    int duracionAmarillo;
};

class EstadoRojo : public Estado {
public:
    void ejecutar() override;
    Estado* siguienteEstado(Estado* estadoAnterior, Estado* estadoOtroSemaforo, int duracionVerde, int duracionAmarillo) override;

    protected:
        int timer = 1;
};

#endif