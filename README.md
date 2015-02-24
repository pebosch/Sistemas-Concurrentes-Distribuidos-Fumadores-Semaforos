# scd-fumadores-semaforos
Solución al problema de los fumadores basada en semáforos.

### Descripción del problema
En esta solución se intenta resolver un problema complejo usando hebras y semáforos POSIX.

Considerar un estanco en el que hay tres fumadores y un estanquero.
1.1. Cada fumador representa una hebra que realiza una actividad (fumar), invocando a una función fumar(), en un bucle infinito.
1.2. Cada fumador debe esperar antes de fumar a que se den ciertas condiciones (tener suministros para fumar), que dependen de la actividad del proceso que representa al estanquero.
1.3. El estanquero produce suministros para que los fumadores puedan fumar, también en un bucle infinito.
1.4. Para asegurar concurrencia real, es importante tener en cuenta que la solución diseñada debe permitir que varios fumadores fumen simultáneamente.

### Descripción de los requisitos
A continuación se describen los requisitos para que los fumadores puedan fumar y el funcionamiento del proceso estanquero:

2.1. Antes de fumar es necesario liar un cigarro, para ello el fumador necesita tres ingredientes: tabaco, papel y cerillas.
2.2. Uno de los fumadores tiene solamente papel, otro tiene solamente tabaco, y el otro tiene solamente cerillas.
2.3. El estanquero coloca aleatoriamente dos ingredientes diferentes de los tres que se necesitan para hacer un cigarro, desbloquea al fumador que tiene el tercer ingrediente y después se bloquea.
2.4. El fumador desbloqueado toma los dos ingredientes del mostrador, desbloquea al estanquero para que pueda seguir sirviendo ingredientes y fuma durante un tiempo después de liarse el cigarro.
2.5. El estanquero, cuando se desbloquea, vuelve a poner dos ingredientes aleatorios en el mostrador, y se repite el ciclo.

### Objetivos
Diseñar e implementar una solución al problema en C/C++ usando cuatro hebras y los semáforos necesarios. La solución debe cumplir los requisitos incluidos en la descripción, y además debe:
- Evitar interbloqueos entre las distintas hebras.
- Producir mensajes en la salida estándar que permitan hacer un seguimiento de la actividad de las hebras:
-- El estanquero debe indicar cuándo produce suministros y que suministros produce. Para establecer los ingredientes concretos (o directamente el fumador que podr´ıa usarlos), se debe usar también la funci´on rand().
-- Cada fumador debe indicar cuándo espera, que producto o productos espera, y cuándo comienza y finaliza de fumar.
