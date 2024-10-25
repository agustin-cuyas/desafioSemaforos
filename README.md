# Segundo desafío C/C++
## Sistema de Control de Tráfico

Para desarrollar el desafío, lo primero que hice fue repasar máquinas de estado y averiguar cómo podían implementarse en C y C++. Luego idnetifiqué la cantidad de estados que necesitaba y cómo iban a cambiar en base a las entradas.

### - Desarrollo en C:
   Utilicé 3 funciones principales. cambiarSemaforo que era llamada por semaforoPrincipal y semaforoSecundaria.
   Para contar el tiempo implementé un clock en el main que hace incrementar el tiempo en cada estado.
   En un principio las duraciones de los estados estaban hardcodeadas, lo que hacia que llegado un punto los semaforos se desfasaban y no    cumplian las condiciones. Esto era porque la duracion en rojo debía ser función del otro semaforo. Para esto se manda el estado del 
   otro semaforo a cada uno. 
   Además se debe tener en cuenta el estado anterior, ya que de amarillo puede ir a rojo o verde, y esto lo decide en función del estado 
   del que viene.
   Luego de solucionar los errores, lo último fue agregar el sensor unos segundo antes que se termine el timepo en verde y solicitar las     duraciones al principio del programa.

### - Desarrollo en C++:
   En este caso, aproveché las clases para hacer los cambios de estado.
   Hay dos clases principales: Estado y Semaforo. La primera es heredada por EstadoVerde, EstadoAmarillo y EstadoRojo. SemaforoPrincipal y      SemaforoSecundaria son subclases de Semaforo.
   - En Estado tenemos los metodos ejecutar y siguienteEstado. Entre los atributos se tiene timer, duracionVerde, duracionAmarillo y sensor.      Las duraciones son incializadas por cada semaforo. No existe duracionRojo ya que esta depende del ciclo del otro semaforo.
     Sensor solo existe para EstadoVerde ya que es en este estado que se tiene en cuenta si hay autos en la otra carretera.
   - En Semaforo los metodos principales son cambiarEstado, ejecutarEstado, ingresarDuracion y getEestadoActual.
     Como se mencionó, las duraciones dependen del semaforo, entonces al principio del programa se pide que se ingresen los valores y   
     luego son pasados a los estados.
     Como había pasado en el código en C, había un momento en que ambos semáforos estaban simultaneamente en rojo, fue lo que más me     
     costó solucionar. La solución está resaltada en clases_semaforo.cpp:
     
               if (dynamic_cast<EstadoRojo*>(nuevoEstado) && dynamic_cast<EstadoRojo*>(otroSemaforo->getEstadoActual())) {
                  if (!dynamic_cast<EstadoAmarillo*>(otroSemaforo->getEstadoActual())) {
                      otroSemaforo->estadoAnterior = otroSemaforo->estadoActual;
                      otroSemaforo->estadoActual = new EstadoAmarillo(duracionAmarillo);
                   }
               }
