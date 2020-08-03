

Proyecto Ruleta Europea
Asignatura: Taller de Programación I
Profesores: Bottallo, Diego A. - Diamand, Luciano - Villar, Fernando.
Alumnos: Ranea, Iván - Vivas, Lorena V.


Documentación Ruleta Europea.

Introduccion.

El proyecto consiste en realizar una simulacion de una ruleta europea, un juego al azar formado por una ruleta y un tapiz. La ruleta que cuenta con 37 (treinta y siete) casillas numeradas de 0 (cero) a 36 (treita y seis)según las reglas de la misma. Las casillas son rojas y negras, los colores estan  dispuestos en forma desordenada, salvo el 0 que es de color verde.

El tapiz permite a los jugadores colocar sus apuestas sobre el número o el color deseado. Puede apostar por un número o serie de números. Una vez realizadas las apuestas el jugador se hace girar la ruleta, según las reglas.

Requerimientos

El programa solicitado debe permitir la realizacion de apuestas en una ruleta europea.
Al finalizar la ronda de apuestas debe brindarse una serie de estadísticas que se especifican y mencionan si la mesa resulta ganadora o perdedora y el monto específico.

Requerimientos.

Mesa o paño de la Ruleta Europea:


![ananannaa.jpeg](../_resources/a1978ee191a545d19a85c6de520a0dcc.jpeg)

La mesa posee 37 números del 0 (cero) al 36 (treinta y seis), donde todos, excepto el 0 (cero), son de color negro o rojo.
Para los fines del programa se consideran las siguientes apuestas:


-  Números: solo plenos (eleccion de un numero individual a apostar)
-  Docenas: hay tres de ellas, indicadas por “Primeros 12”, “Segundos 12” y “Terceros 12”
-  Falta: apuestas que van del 1 (uno) al 18 (dieciocho)
-  Pasa: apuestas que van del 19 (diecinueve) al 36 (treinta y seis)
-  Color: aquellos cuadrados de color ROJO y NEGRO
-  PARES e IMPARES
-  Columna: aquellos que figuran con enucniado 2 (dos) a 1 (uno), pueden ser diferenciados entre sí como “Columna del 1”, “Columna del 2” y “Columna del 3”

Conceptos relevantes:

Ronda: El programa solicita al inicio que se especifiquen cuantas rondas se jugará en esta mesa, cada ronda consiste en una cantidad de apuestas y, posteriormente, el lanzamiento de la bola.
Al detenerse la bola en un número se debe contabilizar las ganancias o pérdidas generadas.
Una vez desarrolladas todas las rondas indicadas al inicio y dada la presentacion de la estadisticas, el programa finaliza.
El número máximo de rondas es 20 (veinte).

Apuesta: Una apuesta consiste en señalar en que casillas se colocan fichas y de que valor es cada una. No hay limite para la cantidad de fichas que se pueden apostar en una misma apuesta, siempre y cuando no exceda el dinero disponble del jugador.
Existe un máximo de 10 apuestas por ronda, se señaliza en la penultima apuesta que las mismas estan por finalizar.
La pérdida para la mesa consiste en la suma de los premios que debe pagar al jugador.
La ganancia para la mesa representa la suma de las fichas del jugador que no se ubicaron en posiciones favorecidas en cada lanzamiento de bola.
Como restricción, un mismo jugador no puede apostar la misma cantidad de dinero a apuestas que
pagan doble.
Se suponen los siguientes valores para las fichas: 1 (uno), 2 (dos), 5 (cinco), 10 (diez), 50 (cincuenta), 100 (cien).

Premios: Debe considerarse el pago de premios de acuerdo a las siguientes apuestas:


- Pleno 
Paga: 35 a 1
- Docena  
Paga: 3 a 1
- Falta 
Paga: 2 a 1
- Pasa 
Paga: 2 a 1
- Color
Paga: 2 a 1
- Pares o Impares
Paga: 2 a 1
- Columna 
Paga: 3 a 1



Resultados:

Debe mostrarse estadísticas que los siguientes ítems:
1. El promedio de cantidad de apuestas por ronda.
2. Comparativa porcentual de apuestas ROJO vs NEGRO.
3. Si en más de 5 (cinco) rondas seguidas la bola cayó en números de igual color.
4. Apuesta de mayor valor monetario, es decir el dinero que suman todas las fichas de una misma
apuesta. Por pantalla se debe mostrar en que ronda sucedió.
5. Mostrar cuántas veces la bola cayó en un número primo.
6. Informar si nunca salió en las rondas el 0 (cero) o números múltiplos de 10 (diez).

Al finalizar con la totalidad de las rondas, se tienen que indicar las pérdidas y ganancias totales, y en base a la diferencia entre ellas indicar:


- "Mesa Ganadora!!!" Si hay más ganacias que pérdidas.
- "Mesa No Conforme" Si las ganancias y las pérdidas son equivalentes.
- "Mesa En Problemas ;)" Si hay mas pérdidas que ganancias.

Disenio.

Para el desarrollo del programa se definieron macros, constantes, estructuras y funciones.

Las macros mas importantes coumplen la funcion de indicar de que tipo de apuesta se esta refieriendo y su valor si asi lo tuviere.

Dentro de las funciones mas importantes se encuentran:

- las que registran una apuesta del jugador
- las que registran el monto de fichas
- la realiza la gestion o resolucion de premios una vez finalizadas las rondas 
- la funcion del giro de la ruleta


1. Funcion preguntarApuestasAlUsuario.

La funcion toma tres argumentos:


- Apuesta *apuestas: un array del tipo estructutura "Apuesta", en el cual se van a registrar todos los datos que conllevan una apuesta. El tipo de apuesta, el valor (si lo tuviere) y las fichas apostadas.
- int nApuestas: una variable entera que guarda el numero de apuestas ingresadas por el jugador.
- int *dineroTotalJUgador: un puntero de la variable que contiene el dinero total que dispone el juagdor.













