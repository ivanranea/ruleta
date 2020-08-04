

**Proyecto Ruleta Europea**
**Asignatura: Taller de Programación I**
**Profesores: Bottallo, Diego A. - Diamand, Luciano - Villar, Fernando.**
**Alumnos: Ranea, Iván - Vivas, Lorena V.**


**Documentación Ruleta Europea.**

**Introduccion.**

El proyecto consiste en realizar una simulacion de una ruleta europea, un juego al azar formado por una ruleta y un tapiz. La ruleta que cuenta con 37 casillas numeradas de 0 a 36 (treita y seis)según las reglas de la misma. Las casillas son rojas y negras, los colores estan  dispuestos en forma desordenada, salvo el 0 que es de color verde.

El tapiz permite a los jugadores colocar sus apuestas sobre un número o conjunto deseado. Los conjuntos son predefinidos (pleno, docenas, color, paridad, columna, falta y pasa) Una vez realizadas las apuestas el jugador se hace girar la ruleta, según las reglas.

**Requerimientos.**

El programa solicitado debe permitir la realizacion de apuestas en una ruleta europea.
Al finalizar la ronda de apuestas debe brindarse una serie de estadísticas que se especifican y mencionan si la mesa resulta ganadora o perdedora y el monto específico.

Mesa o paño de la Ruleta Europea:


![ananannaa.jpeg](../_resources/a1978ee191a545d19a85c6de520a0dcc.jpeg)

La mesa posee 37 números del 0 al 36, donde todos, excepto el 0, son de color negro o rojo.
Para los fines del programa se consideran las siguientes apuestas:


-  Números: solo plenos (eleccion de un numero individual a apostar)
-  Docenas: hay tres de ellas, indicadas por “Primeros 12”, “Segundos 12” y “Terceros 12”
-  Falta: apuestas que van del 1 al 18
-  Pasa: apuestas que van del 19 al 36
-  Color: aquellos cuadrados de color ROJO y NEGRO
-  PARES e IMPARES
-  Columna: aquellos que figuran con enucniado 2 a 1, pueden ser diferenciados entre sí como “Columna del 1”, “Columna del 2” y “Columna del 3”

**Conceptos relevantes.**

Ronda: Consiste en una cantidad de apuestas y, posteriormente, el lanzamiento de la bola.
Al detenerse la bola en un número se debe contabilizar las ganancias o pérdidas generadas por la funcion ```resolucionApuestas```.
Una vez desarrolladas todas las rondas indicadas al inicio y dada la presentacion de la estadisticas, el programa finaliza.
El número máximo de rondas es 20.

Apuesta: Consiste en señalar en que casillas se colocan fichas y de que valor es cada una. No hay limite para la cantidad de fichas que se pueden apostar en una misma apuesta, siempre y cuando no exceda el dinero disponble del jugador.
Existe un máximo de 10 apuestas por ronda, se señaliza en la penultima apuesta que las mismas estan por finalizar.
La pérdida para la mesa consiste en la suma de los premios que debe pagar al jugador.
La ganancia para la mesa representa la suma de las fichas del jugador que no se ubicaron en posiciones favorecidas en cada lanzamiento de bola.
Como restricción, un mismo jugador no puede apostar la misma cantidad de dinero a apuestas que
pagan doble.
Se suponen los siguientes valores para las fichas: 1, 2, 5, 10, 50, 100.

Premios: Debe considerarse el pago de premios de acuerdo a las siguientes apuestas:

| Apuesta       | Paga          | 
| ------------- |:-------------:| 
| Pleno         |   35 a 1      | 
| Docena        |   3 a 1       |
| Falta			| 2 a 1         |


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



**Estadisticas**

Debe mostrarse estadísticas que los siguientes ítems:
1. El promedio de cantidad de apuestas por ronda.
2. Comparativa porcentual de apuestas ROJO vs NEGRO.
3. Si en más de 5 rondas seguidas la bola cayó en números de igual color.
4. Apuesta de mayor valor monetario, es decir el dinero que suman todas las fichas de una misma
apuesta. 
5. Mostrar cuántas veces la bola cayó en un número primo.
6. Informar si nunca salió en las rondas el 0 o números múltiplos de 10.

Al finalizar con la totalidad de las rondas, se tienen que indicar las pérdidas y ganancias totales, y en base a la diferencia entre ellas indicar:


- "Mesa Ganadora!!!" Si hay más ganacias que pérdidas.
- "Mesa No Conforme" Si las ganancias y las pérdidas son equivalentes.
- "Mesa En Problemas ;)" Si hay mas pérdidas que ganancias.

**Disenio**

El programa se divide a grandes rasgos en dos etapas, la primera de recoleccion datos y la segunda, el proceso de los mismo y la muestra de las estadisticas.

El programa comienza preguntado al jugador la cantidad de rondas que desea, seguido de la cantidad de apuestas para la ronda en curso. En amobos casos si se ingresa un numero no valido se le pide al jugador que ingrese otro.
Luego de ello el programa le presenta al jugador los distitnos tipos de apuesta que puede realizar. 
Una vez el jugador haya elegido el tipo de apuesta que desea se ejecuta el codigo correspondente para registrarla.
El registro lo que hace es guardar el tipo de apuesta (ej: numero, paridad, color, fila, etc), el valor (ej: 34, rojo, par, fila 2) y las fichas registradas (el valor monetario de las fichas).
Al momento del registro de las fichas se le va a presentar al jugador las opciones disponibles ($1,$2, $5, $10, $50, $100). No hay un limite de cantidad de fichas que se puede ingresar en una misma apuesta.
Una vez realizada las apuestas se procede al giro de la ruleta, que va a representar un valor numerico entre el 0 y 36.

El metodo para la resolucion de las ganancias es similar al de regsitro de apuestas, se utilizan los datos obtenidos con anterioridad (tipo, valor, fichas).
Se registra una ganancia o perdida segun haya salido favorecida o no la apuesta realizada por el jugador con respecto al giro de la ruleta.

Elementos mas importantes del programa:

- Arrays

```arraynApuestas[]```: contiene todos los ```nApuestas``` que se regitraron en las rondas.
```apuestas[]```: array de tipo ```Apuesta``` que contiene los datos, ```.tipo```, ```.valor```, ```.ficha```.
```arrayGiros[]```:  contiene todos los giros de la ruleta que se registraron en todas las rondas.
```registroGananciaPerdida[]```: en este array se guardan las ganancias o perdidas para cada una de las apuestas.
```conjuntoApuestas[][]```: es una matriz que contiene los arrays ```apuestas[]``` que se generaron en las rondas.
```arrayregistroGananciaPerdida[][]```: matriz en la que se almacenan los arrays ```registroGananciaPerdida[]``` de todas las rondas.


- Estructuras

```Apuesta```: tipo estructura que contiene los elementos ```.tipo```, ```.valor```, ```.ficha```.
```ganancia_perdida```: Estructura para registrar ```.ganancia``` y ```.pérdida``` de una apuesta.


- Funciones:

```preguntarApuestasAlUsuario```: Registra el tipo de una apuesta y llama a la funciones correspondientes para almacenar el valor y las fichas del mismo para asi tener todos los datos que conforman una apuesta.
```resolucionApuestas```: es la funcion que toma los registros de las apuestas y el giro de la ruleta. Calcula la resolucion de los premios segun hubo ganancia o perdida, los registra y muestra el resultado de cada apuesta.
```giroRuleta```: devuelve un numero al azar entre el 0 y 36.

- Macros:

```RONDAMAX```: indica la cantidad de rondas maximas (20).
```APUESTAMAX```: indica la cantidad de rondas maximas (10).
```A_PLENO```: Referencia al tipo de apuesta PLENO (1)
```A_DOCENAS```: Referencia al tipo de apuesta DOCENA (2)
```A_FALTA```: Referencia al tipo de apuesta FALTA (3)
```A_PASA```: Referencia al tipo de apuesta PASA (4)
```A_COLOR```: Referencia al tipo de apuesta COLOR (5)
```A_PARIDAD```: Referencia al tipo de apuesta PAR o IMPAR (6)
```A_COLUMNA```: Referencia al tipo de apuesta COLUMNA (7)


- Variables 

```nRondas```: cantidad de rondas seleccionadas por el jugador.
```nApuestas```: cantidad de apuestas seleccionadas por el jugador en cada ronda.
```giro```: sirve para guardar el retorno de la funcion ```giroRuleta```.


Estadisticas


1. El promedio de cantidad de apuestas por ronda.

Parametros de la funcion: ```arraynApuestas[]``` y ```nRondas```.
Con esta informacion la funcion calcula el promedio de apuestas por ronda y lo muestra por pantalla.

2. Comparativa porcentual de apuestas ROJO vs NEGRO.

Parametros de la funcion:  ```conjuntoApuestas[][]```, ```arraynApuestas[]``` y ```nRondas```.
Cuenta la cantidad de veces que se aposto al rojo y/o negro, calcula el procentaje y lo muestra por pantalla.

3. Si en más de 5 rondas seguidas la bola cayó en números de igual color.

Parametros de la funcion:```arrayGiros[]``` y ```nRondas```.
Comprueba si en el giro de la ruleta salieron numeros de igual color en cinco rondas seguidas e imprime el resultado.

4. Apuesta de mayor valor monetario, es decir el dinero que suman todas las fichas de una misma
apuesta.

Parametros de la funcion:  ```conjuntoApuestas[][]```, ```arraynApuestas[]``` y ```nRondas```.
Suma las fichas de un mismo tipo de apuesta para una ronda, las compara y determina cual es la mayor. Luego, toma la mayor apuesta de cada ronda, las compara entre ellas, determina cual es la mas grande y en que ronda fue e imprime el resultado.

5. Mostrar cuántas veces la bola cayó en un número primo.

Parametros de la funcion:```arrayGiros[]``` y ```nRondas```.
Toma todos los numeros del giro de la ruleta, afirma si son primos y cuenta cuantos son, para luego mostrarlo por pantalla.

6. Informar si nunca salió en las rondas el 0 o números múltiplos de 10.

Parametros de la funcion:```arrayGiros[]``` y ```nRondas```.
Toma todos los numeros del giro de la ruleta, analiza si son multiplos de 10 o el numero es 0. Luego imprime por pantalla informando si hay o no multiplos de 10 o 0.


**Metodologia de trabajo:**









