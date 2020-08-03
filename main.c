#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define CANTCOLOR 18 //Cantidad de números de la categoría ROJOS y NEGROS (cada uno tiene 18)
#define NROSPORCOLUMNA 12
#define RONDAMAX 20 //Cantidad máxima de rondas que el jugador puede jugar
#define APUESTAMAX 10 //Cantidad máxima de apuestas que el jugador puede realizar en una ronda
#define TRUE 1
#define FALSE 0

#define A_PLENO 1 //Referencia al tipo de apuesta PLENO

#define A_DOCENAS 2 //Referencia al tipo de apuesta DOCENA
#define A_PRIMER_DOCENA 1 //Referencia al valor de tipo DOCENA
#define A_SEGUNDA_DOCENA 2 //Referencia al valor de tipo DOCENA
#define A_TERCERA_DOCENA 3 //Referencia al valor de tipo DOCENA

#define A_FALTA 3 //Referencia al tipo de apuesta FALTA

#define A_PASA 4 //Referencia al tipo de apuesta PASA

#define A_COLOR 5 //Referencia al tipo de apuesta COLOR
#define A_COLOR_ROJO 1 //Referencia al valor de tipo COLOR
#define A_COLOR_NEGRO 2 //Referencia al valor de tipo COLOR

#define A_PARIDAD 6
#define A_PARIDAD_PAR 1 //Referencia al valor de tipo PARIDAD
#define A_PARIDAD_IMPAR 2 //Referencia al valor de tipo PARIDAD

#define A_COLUMNA 7 //Referencia al tipo de apuesta COLUMNA
#define A_PRIMER_COLUMNA 1 //Referencia al valor de tipo COLUMNA
#define A_SEGUNDA_COLUMNA 2 //Referencia al valor de tipo COLUMNA
#define A_TERCERA_COLUMNA 3 //Referencia al valor de tipo COLUMNA

#define FICHATEMP_FALTA fichaTemp.falta==fichaTemp.pasa || fichaTemp.falta==fichaTemp.color || fichaTemp.falta==fichaTemp.paridad //Macro utilizada para, junto con un If, comprobar si se cumplen las condiciones para llamar a la función restricción en la apuesta FALTA
#define FICHATEMP_PASA fichaTemp.pasa==fichaTemp.falta || fichaTemp.pasa==fichaTemp.color || fichaTemp.pasa==fichaTemp.paridad //Macro utilizada para, junto con un If, comprobar si se cumplen las condiciones para llamar a la función restricción en la apuesta PASA
#define FICHATEMP_COLOR fichaTemp.color==fichaTemp.falta || fichaTemp.color==fichaTemp.pasa || fichaTemp.color==fichaTemp.paridad //Macro utilizada para, junto con un If, comprobar si se cumplen las condiciones para llamar a la función restricción en la apuesta COLOR
#define FICHATEMP_PARIDAD fichaTemp.paridad==fichaTemp.falta || fichaTemp.paridad==fichaTemp.pasa || fichaTemp.paridad==fichaTemp.color //Macro utilizada para, junto con un If, comprobar si se cumplen las condiciones para llamar a la función restricción en la apuesta PARIDAD

#define ROJO_3 tercer_columna==3 || tercer_columna==9 || tercer_columna==12 || tercer_columna==18 || tercer_columna==21 || tercer_columna==27 || tercer_columna==30 || tercer_columna==36
#define NEGRO_3 tercer_columna==6 || tercer_columna==15 || tercer_columna==24 || tercer_columna==33
#define ROJO_2 segunda_columna==5 || segunda_columna==14 || segunda_columna==23 || segunda_columna==32 || segunda_columna==21 || segunda_columna==27 || segunda_columna==30 || segunda_columna==36
#define NEGRO_2 segunda_columna==2 || segunda_columna==8 || segunda_columna==11 || segunda_columna==17 || segunda_columna==20 || segunda_columna==26 || segunda_columna==29 || segunda_columna==35
#define ROJO_1 primer_columna==1 || primer_columna==7 || primer_columna==16 || primer_columna==19 || primer_columna==25 || primer_columna==34
#define NEGRO_1 primer_columna==4 || primer_columna==10 || primer_columna==13 || primer_columna==22 || primer_columna==28 || primer_columna==31

const int numerosRojos[] = {1,3,5,7,9,12,14,16,18,19,21,23,25,27,30,32,34,36};
const int numerosNegros[] = {2,4,6,8,10,11,13,15,17,20,22,24,26,28,29,31,33,35};
const int columna1[] = {1,4,7,10,13,16,19,22,25,28,31,34};
const int columna2[] = {2,5,8,11,14,17,20,23,26,29,32,35};
const int columna3[] = {3,6,9,12,15,18,21,24,27,30,33,36};

typedef struct {
    int tipo; // Numero, paridad, color, fila, etc
    int valor; // 34, rojo, par, fila 2
    int fichas; // cantidad de fichas apostadas
} Apuesta; // Ejemplo: Para apostar 5 fichas al rojo - Apuesta(tipo: 5, valor: 1, fichas: 5)


typedef struct { //Estructura para registrar ganancias y pérdidas de una apuesta
    int ganancia;
    int perdida;

} ganancia_perdida;

typedef struct{ //Estructura que registra las fichas apostadas en las apuestas que pagan doble y que son utilizadas en la función restricción
    int falta;
    int pasa;
    int color;
    int paridad;

} ficha_temp;

void restriccion(Apuesta *apuestas, int i, int *dineroTotalJugador, ficha_temp *fichaTemp); //Funcion de restriccion para que el jugador no pueda apostar la misma cantidad de fichas a apuestas que pagan doble

ganancia_perdida registrarGananciaPleno(Apuesta apuesta, int giro); //Resuelve los premios de lo apostado en PLENO y devuelve una estructura que contiene la ganancia y pérdida de la misma

ganancia_perdida registrarGananciaDocenas(Apuesta apuesta, int giro); //Resuelve los premios de lo apostado en DOCENAS y devuelve una estructura que contiene la ganancia y pérdida de la misma

ganancia_perdida registrarGananciaFalta(Apuesta apuesta, int giro); //Resuelve los premios de lo apostado en FALTA y devuelve una estructura que contiene la ganancia y pérdida de la misma

ganancia_perdida registrarGananciaPasa(Apuesta apuesta, int giro); //Resuelve los premios de lo apostado en PASA y devuelve una estructura que contiene la ganancia y pérdida de la misma

ganancia_perdida registrarGananciaColor(Apuesta apuesta, int giro); //Resuelve los premios de lo apostado en COLOR y devuelve una estructura que contiene la ganancia y pérdida de la misma

ganancia_perdida registrarGananciaParidad(Apuesta apuesta, int giro); //Resuelve los premios de lo apostado en PARIDAD y devuelve una estructura que contiene la ganancia y pérdida de la misma

ganancia_perdida registrarGananciaColumna(Apuesta apuesta, int giro); //Resuelve los premios de lo apostado en COLUMNA y devuelve una estructura que contiene la ganancia y pérdida de la misma

void resolucionApuestas(Apuesta *apuestas, ganancia_perdida *registroGananciaPerdida, int nApuestas, int giro); //Registra e imprime las ganancias y las pérdidas en una ronda de apuestas

int registrarMontoFichas(int *dineroTotalJugador); //Se encarga de mostrar las opciones  de fichas disponibles para apostar, dinero total del jugador, y hace un registro de las fichas ingresadas por el usuario

Apuesta registrarApuestaPlenos(int *dineroTotalJugador); //Registra una apuesta a Pleno

Apuesta registrarApuestaDocenas(int *dineroTotalJugador); //Registra una apuesta a Docenas

Apuesta registrarApuestaFalta(int *dineroTotalJugador); //Registra una apuesta a Falta

Apuesta registrarApuestaPasa(int *dineroTotalJugador); //Registra una apuesta a Pasa

Apuesta registrarApuestaColor(int *dineroTotalJugador); //Registra una apuesta a Color

Apuesta registrarApuestaParidad(int *dineroTotalJugador); //Registra una apuesta a Paridad

Apuesta registrarApuestaColumna(int *dineroTotalJugador); //Registra una apuesta a Columna

void preguntarApuestasAlUsuario(Apuesta *apuestas, int nApuestas, int *dineroTotalJugador); //Muestra el paño y las opciones de apuesta, permite ingresar una cantidad de apuestas y llama según corresponda a las funciones para registrar apuestas

void balanceFinal(ganancia_perdida arrayregistroGananciaPerdida[RONDAMAX][APUESTAMAX], int *arraynApuestas, int nRondas); //Muestra los resultados finales de ganancias y périddas

void porcentajeColor(Apuesta conjuntoApuestas[RONDAMAX][APUESTAMAX], int *arraynApuestas, int nRondas); //Compara los porcentajes de las apuestas realizadas a ROJO y NEGRO

void apuestaMayorValor(Apuesta conjuntoApuestas[RONDAMAX][APUESTAMAX], int *arraynApuestas, int nRondas); //Muestra cuál fue la mayor cantidad de fichas apostadas y en qué ronda sucedió

void mostrarMesa(); //Funcion para mostrar el paño de la ruleta europea

void giroIgualColor(int *arrayGiros, int nRondas);  //Muestra si en más de cinco rondas seguidas la bola cayó en números de igual color

void promedioApuestasPorRonda(int *arraynApuestas, int nRondas); //Calcula y muestra el promedio de apuestas por ronda

void ceroOmultiplosdeDiez(int *arrayGiros, int nRondas); //Muestra si la bola cayó en el número 0 o algún multiplo de 10

void numeroPrimo(int *arrayGiros, int nRondas); //Calcula y muestra cuántas veces la bola cayó en un número primo

int giroRuleta(); //Genera aleatoreamente un número entre 0 y 36

/// INICIO MAIN
int main()
{
    int i, j;
    int nRondas = 0;
    int nApuestas = 0;
    int dineroTotalJugador = 300;
    int arraynApuestas[RONDAMAX];
    Apuesta apuestas[APUESTAMAX];
    Apuesta conjuntoApuestas[RONDAMAX][APUESTAMAX];
    ganancia_perdida registroGananciaPerdida[APUESTAMAX];
    ganancia_perdida arrayregistroGananciaPerdida[RONDAMAX][APUESTAMAX];
    int giro = 0;
    int arrayGiros[RONDAMAX];

    for(i=0; i<RONDAMAX; i++)
    {
        for(j=0; j<APUESTAMAX; j++)
        {
            apuestas[j].tipo = 0;
            apuestas[j].valor = 0;
            apuestas[j].fichas = 0;
            conjuntoApuestas[i][j] = apuestas[j];
            registroGananciaPerdida[j].ganancia = 0;
            registroGananciaPerdida[j].perdida = 0;
            arrayregistroGananciaPerdida[i][j] = registroGananciaPerdida[j];
            arraynApuestas[j] = 0;
        }
        arrayGiros[i] = 0;
    }

    printf("Bienvenido al programa de Ruleta Europea.\n\n");
    printf("Ingrese la cantidad de rondas desea jugar: ");
    scanf("%d", &nRondas);

    while(nRondas>20)
    {
        printf("La cantidad máxima de rondas es de 20, ingrese otro número.\n");
        printf("Rondas a jugar: ");
        scanf("%d", &nRondas);
    }

    printf("\n");

    for(i=0; i<nRondas; i++)
    {
        if(dineroTotalJugador>0)
        {
            printf("Ronda número %d.\n", i+1);
            printf("Indique cuántas apuestas desea realizar: ");
            scanf("%d", &nApuestas);

            while(nApuestas>10)
            {
                printf("La cantidad máxima de apuestas es de 10, ingrese otro número.\n");
                printf("Apuestas a jugar: ");
                scanf("%d", &nApuestas);
            }

            printf("\n");

            arraynApuestas[i]=nApuestas;

            preguntarApuestasAlUsuario(apuestas, nApuestas, &dineroTotalJugador);

            for(j=0; j<nApuestas; j++)
            {
                conjuntoApuestas[i][j] = apuestas[j];
            }
            giro = giroRuleta();
            arrayGiros[i] = giro;
            printf("\nEl resultado del giro de la ruleta fue %d\n", giro);

            resolucionApuestas(apuestas, registroGananciaPerdida, nApuestas, giro);

            for(j=0; j<nApuestas; j++)
            {
                arrayregistroGananciaPerdida[i][j]=registroGananciaPerdida[j];
            }
        }else
        {

            break;
        }
    }

        promedioApuestasPorRonda(arraynApuestas, nRondas);
        porcentajeColor(conjuntoApuestas, arraynApuestas, nRondas);
        giroIgualColor(arrayGiros, nRondas);
        apuestaMayorValor(conjuntoApuestas, arraynApuestas, nRondas);
        numeroPrimo(arrayGiros, nRondas);
        balanceFinal(arrayregistroGananciaPerdida, arraynApuestas, nRondas);



    return 0;
}

///FIN MAIN

ganancia_perdida registrarGananciaPleno(Apuesta apuesta, int giro){
    ganancia_perdida g;
    g.ganancia=0;
    g.perdida=0;

    if(giro==apuesta.valor)
    {
        g.ganancia = 35*apuesta.fichas;
    }else
    {
        g.perdida = apuesta.fichas;
    }
    return g;
}

ganancia_perdida registrarGananciaDocenas(Apuesta apuesta, int giro){
    ganancia_perdida g;
    g.ganancia=0;
    g.perdida=0;

    switch(apuesta.valor)
    {
        case A_PRIMER_DOCENA: //Primera docena
            if(giro>0 && giro<=12)
            {
                g.ganancia = 3*apuesta.fichas;

            }else
            {
                g.perdida = apuesta.fichas;
            }
            break;

        case A_SEGUNDA_DOCENA: //Segunda docena

            if(giro>12 && giro<=24)
            {
                g.ganancia = 3*apuesta.fichas;

            }else
            {
                g.perdida = apuesta.fichas;
            }
            break;

        case A_TERCERA_DOCENA: //Tercera docena

            if(giro>24 && giro <= 36)
            {
                g.ganancia = 3*apuesta.fichas;
            }else
            {
                g.perdida = apuesta.fichas;
            }
        default:break;
    }
    return g;
}

ganancia_perdida registrarGananciaFalta(Apuesta apuesta, int giro){
    ganancia_perdida g;
    g.ganancia=0;
    g.perdida=0;

    if(giro>0 && giro<=18)
    {
        g.ganancia = 2*apuesta.fichas;
    }else
    {
        g.perdida = apuesta.fichas;
    }
    return g;
}

ganancia_perdida registrarGananciaColor(Apuesta apuesta, int giro){
    ganancia_perdida g;
    g.ganancia=0;
    g.perdida=0;

    int i;
    int apuestaGanada = FALSE;

    switch(apuesta.valor)
    {
        case A_COLOR_ROJO: //Rojo

            for(i=0; i<CANTCOLOR; i++)
            {
                if(giro==numerosRojos[i])
                {
                    g.ganancia = 2*apuesta.fichas;
                    apuestaGanada = TRUE;
                    break;
                }
            }
            if(apuestaGanada==FALSE)
            {
                g.perdida = apuesta.fichas;
            }
            break;

        case A_COLOR_NEGRO: //Negro

            for(i=0; i<CANTCOLOR; i++)
            {
                if(giro==numerosNegros[i])
                {
                    g.ganancia = 2*apuesta.fichas;
                    apuestaGanada = TRUE;
                    break;
                }
            }
            if(apuestaGanada==FALSE)
            {
                g.perdida = apuesta.fichas;
            }
            break;
        default:break;
    }
    return g;

}

ganancia_perdida registrarGananciaPasa(Apuesta apuesta, int giro){
    ganancia_perdida g;
    g.ganancia=0;
    g.perdida=0;

    if(giro>=19 && giro<=36)
    {
        g.ganancia = 2*apuesta.fichas;

    }else
    {
        g.perdida = apuesta.fichas;
    }
    return g;

}

ganancia_perdida registrarGananciaParidad(Apuesta apuesta, int giro){
    ganancia_perdida g;
    g.ganancia=0;
    g.perdida=0;

    switch(apuesta.valor)
    {
        case A_PARIDAD_PAR: //Par
            if(giro%2==0)
            {
                g.ganancia = 2*apuesta.fichas;

            }else
            {
                g.perdida = apuesta.fichas;
            }

            break;

        case A_PARIDAD_IMPAR: //Impar
            if(giro%2!=0)
            {
                g.ganancia = 2*apuesta.fichas;

            }else
            {
                g.perdida = apuesta.fichas;
            }

            break;

        default:break;
    }
    return g;
}

ganancia_perdida registrarGananciaColumna(Apuesta apuesta, int giro){
    int apuestaGanada = FALSE;
    int i;
    ganancia_perdida g;
    g.ganancia=0;
    g.perdida=0;

    switch(apuesta.valor)
    {
        case A_PRIMER_COLUMNA: //Columna del 1
            for(i=0; i<NROSPORCOLUMNA; i++)
            {
                if(giro==columna1[i])
                {
                    g.ganancia = 3*apuesta.fichas;
                    apuestaGanada = TRUE;
                    break;
                }
            }
            if(apuestaGanada==FALSE)
            {
                g.perdida = apuesta.fichas;
            }
            break;

        case A_SEGUNDA_COLUMNA: //Columna del 2

            for(i=0; i<NROSPORCOLUMNA; i++)
            {
                if(giro==columna2[i])
                {
                    g.ganancia += 3*apuesta.fichas;
                    apuestaGanada = TRUE;
                    break;

                }
            }
            if(apuestaGanada==FALSE)
            {
                g.perdida = apuesta.fichas;
            }
            break;

        case A_TERCERA_COLUMNA: //Columna del 3

            for(i=0; i<NROSPORCOLUMNA; i++)
            {
                if(giro==columna3[i])
                {
                    g.ganancia = 3*apuesta.fichas;
                    apuestaGanada = TRUE;
                    break;
                }
            }
            if(apuestaGanada==FALSE)
            {
                g.perdida = apuesta.fichas;
            }
            break;
        default: break;
    } //Fin switch Columnas
    return g;
}

void resolucionApuestas(Apuesta *apuestas, ganancia_perdida *registroGananciaPerdida, int nApuestas, int giro){

    int i;


    for(i=0; i<nApuestas; i++) // Inicio for principal
    {
        Apuesta a = apuestas[i];
        switch(a.tipo)
        {
            case A_PLENO: //Numeros Plenos

                registroGananciaPerdida[i] = registrarGananciaPleno(a, giro);
                break;

            case A_DOCENAS: //Docenas

                registroGananciaPerdida[i] = registrarGananciaDocenas(a, giro);
                break;

            case A_FALTA: //Falta (1 al 18)

                registroGananciaPerdida[i] = registrarGananciaFalta(a, giro);
                break;

            case A_PASA: //Pasa (19 al 36)
                registroGananciaPerdida[i] = registrarGananciaPasa(a, giro);
                break;

            case A_COLOR: //Color

                registroGananciaPerdida[i] = registrarGananciaColor(a, giro);
                break;

            case A_PARIDAD: //Pares o Impares
                registroGananciaPerdida[i] = registrarGananciaParidad(a, giro);
                break;

            case A_COLUMNA: // Columnas

                registroGananciaPerdida[i] = registrarGananciaColumna(a, giro);
                break;

            default: break;

        }

        if(registroGananciaPerdida[i].ganancia>0){
            printf("\nResultado apuesta numero %d:\nPerdida de mesa (Ganancia de jugador): $%d\n", i+1, registroGananciaPerdida[i].ganancia);
        }else
        {
        printf("\nResultado apuesta numero %d:\nGanancia de mesa (Perdida de jugador): $%d\n", i+1, registroGananciaPerdida[i].perdida);
        }

    } //Fin for principal

    int ganancia = 0;
    int perdida = 0;

    for(i=0; i<nApuestas; i++){
        ganancia += registroGananciaPerdida[i].ganancia;
        perdida += registroGananciaPerdida[i].perdida;
    }


    if(ganancia==0)
    {
        printf("\nLa ganancia de la mesa fue: $%d.\nEl jugador no tuvo ganancias.\n\n", perdida);

    }else if(perdida==0)
    {
        printf("\nLa mesa no tuvo ganancias.\nLa ganancia del jugador fue: $%d.\n\n", ganancia);
    }else
    {
        printf("\nLa ganancia de la mesa fue: $%d.\nLa ganancia del jugador fue: $%d.\n\n", perdida, ganancia);
    }
}

int registrarMontoFichas(int *dineroTotalJugador)
{

    int fichasTemp = 0;
    int fichasApostadas = 0;

    while(TRUE) // Inicio ingreso de fichas para la apuesta
    {

        printf("\nFichas disponibles: $1, $2, $5, $10, $50, $100\nDinero disponible: %d\nCuando desee finalizar la apuesta ingrese 0\nIngrese la ficha que desea apostar: ", *dineroTotalJugador);
        scanf("%d", &fichasTemp);

        while(fichasTemp!=0 && fichasTemp!=1 && fichasTemp!=2 && fichasTemp!=5 && fichasTemp!=10 && fichasTemp!=50 && fichasTemp!=100)
        {
            printf("Ingreso incorrecto.\nIngrese un valor de ficha disponible ($1, $2, $5, $10, $50, $100): ");
            scanf("%d", &fichasTemp);
        }

        while(fichasTemp==0 && fichasApostadas==0)
        {
            printf("Debe ingresar al menos una ficha para su apuesta ($1, $2, $5, $10, $50, $100): ");
            scanf("%d", &fichasTemp);

            while(fichasTemp!=0 && fichasTemp!=1 && fichasTemp!=2 && fichasTemp!=5 && fichasTemp!=10 && fichasTemp!=50 && fichasTemp!=100)
            {
                printf("Ingreso incorrecto.\nIngrese un valor de ficha disponible ($1, $2, $5, $10, $50, $100): ");
                scanf("%d", &fichasTemp);
            }
        }

        if(fichasTemp==0)
        {
            break;
        }
        else
        {

            if(fichasTemp>(*dineroTotalJugador))
            {

                printf("\nEl valor de las fichas excede su dinero disponible ($%d),\nvuelva a ingresar las fichas.\n", *dineroTotalJugador);
                *dineroTotalJugador += fichasApostadas;
                fichasApostadas = 0;
                fichasTemp = 0;

            }
            else
            {
                *dineroTotalJugador -= fichasTemp;
                fichasApostadas += fichasTemp;
                printf("\nApuesta total: $%d\n", fichasApostadas);
            }
        }
    }
    return fichasApostadas; //retornar entero que representa fichas
}


Apuesta registrarApuestaPlenos(int *dineroTotalJugador)
{
    int valor;
    printf("Ingrese el número al cual desea apostar (0 al 36): ");
    scanf("%d", &valor);
    while(valor<0 || valor>36)
    {
        printf("Ingreso incorrecto, elija un número entre el 0 y el 36: ");
        scanf("%d", &valor);
    }
    Apuesta a;
    a.tipo = A_PLENO;
    a.valor = valor;
    a.fichas = registrarMontoFichas(dineroTotalJugador);
    return a;
}

Apuesta registrarApuestaDocenas(int *dineroTotalJugador)
{
    int valor;
    printf("Ingrese a qué docena desea apostar:\n%d.Primera docena\n%d.Segunda docena\n%d.Tercera docena\n",
           A_PRIMER_DOCENA, A_SEGUNDA_DOCENA, A_TERCERA_DOCENA);
    scanf("%d", &valor);
    while(valor<=0 || valor>3)
    {
        printf("Ingreso incorrecto, elija a qué docena desea apostar (1, 2 o 3): ");
        scanf("%d", &valor);
    }
    Apuesta a;
    a.tipo = A_DOCENAS;
    a.valor = valor;
    a.fichas = registrarMontoFichas(dineroTotalJugador);
    return a;
}

Apuesta registrarApuestaFalta(int *dineroTotalJugador)
{

    Apuesta a;
    a.tipo = A_FALTA;
    a.valor = 0;
    a.fichas = registrarMontoFichas(dineroTotalJugador);
    return a;
}

Apuesta registrarApuestaPasa(int *dineroTotalJugador)
{

    Apuesta a;
    a.tipo = A_PASA;
    a.valor = 0;
    a.fichas = registrarMontoFichas(dineroTotalJugador);
    return a;
}


Apuesta registrarApuestaColor(int *dineroTotalJugador)
{
    int valor;
    printf("Ingrese el color al desea apostar:\n1.Rojo\n2.Negro\n");
    scanf("%d", &valor);
    while(valor<=0 || valor>2)
    {
        printf("Ingreso incorrecto, elija a qué docena desea apostar (1 o 2): ");
        scanf("%d", &valor);
    }

    Apuesta a;
    a.tipo = A_COLOR;
    a.valor = valor;
    a.fichas = registrarMontoFichas(dineroTotalJugador);
    return a;
}

Apuesta registrarApuestaParidad(int *dineroTotalJugador)
{
    int valor;
    printf("Ingrese si desea apostar a los números pares o impares:\n1.Par\n2.Impar\n");
    scanf("%d", &valor);
    while(valor<=0 || valor>2)
    {
        printf("Ingreso incorrecto, elija si desea apostar a los números pares o impares (1 o 2): ");
        scanf("%d", &valor);
    }

    Apuesta a;
    a.tipo = A_PARIDAD;
    a.valor = valor;
    a.fichas = registrarMontoFichas(dineroTotalJugador);
    return a;
}

Apuesta registrarApuestaColumna(int *dineroTotalJugador)
{
    int valor;
    printf("Ingrese el tipo de columna a la que desea apostar:\n1.Columna del 1\n2.Columna del 2\n3.Columna del 3\n");
    scanf("%d", &valor);
    while(valor<=0 || valor>3)
    {
        printf("Ingreso incorrecto, elija a qué columna desea apostar (1, 2 o 3): ");
        scanf("%d", &valor);
    }


    Apuesta a;
    a.tipo = A_COLUMNA;
    a.valor = valor;
    a.fichas = registrarMontoFichas(dineroTotalJugador);
    return a;
}

void preguntarApuestasAlUsuario(Apuesta *apuestas, int nApuestas, int *dineroTotalJugador)
{
    int i;
    ficha_temp fichaTemp;
    fichaTemp.falta = 0;
    fichaTemp.pasa = 0;
    fichaTemp.color = 0;
    fichaTemp.paridad = 0;

    if(*dineroTotalJugador>0)
    {
        mostrarMesa();

        for(i=0; i<nApuestas; i++) // Comienzo for apuestas
        {
            if(*dineroTotalJugador==0)
            {
                printf("\nSe ha quedado sin fichas para jugar\n");
                break;
            }

            if(i==(nApuestas-2))
            {
                printf("\nEsta es su penúltima apuesta\n");
            }

            int tipoApuestas;
            printf("\n1.Pleno\n2.Docenas\n3.Falta (1 al 18)\n4.Pasa (19 al 36)\n5.Color\n6.Pares o Impares\n7.Columnas\n");
            printf("\nApuesta nro %d: ", i+1);
            scanf("%d", &tipoApuestas);

            while(tipoApuestas<=0 || tipoApuestas>7)
            {
                printf("Ingreso incorrecto, elija un tipo de apuesta (1 al 7): ");
                scanf("%d", &tipoApuestas);
            }

            switch(tipoApuestas) //Inicio Swith Tipo Apuestas
            {
            case A_PLENO: //Plenos
                if(*dineroTotalJugador==0)
                {
                    printf("\nSe ha quedado sin fichas para jugar\n");
                    break;
                }
                apuestas[i] = registrarApuestaPlenos(dineroTotalJugador);
                break;

            case A_DOCENAS: //Docenas
                if(*dineroTotalJugador==0)
                {
                    printf("\nSe ha quedado sin fichas para jugar\n");
                    break;
                }
                apuestas[i] = registrarApuestaDocenas(dineroTotalJugador);
                break;

            case A_FALTA:  // Falta
                if(*dineroTotalJugador==0)
                {
                    printf("\nSe ha quedado sin fichas para jugar\n");
                    break;
                }
                apuestas[i] = registrarApuestaFalta(dineroTotalJugador);
                fichaTemp.falta = apuestas[i].fichas;

                if(FICHATEMP_FALTA)
                {
                    restriccion(apuestas, i, dineroTotalJugador, &fichaTemp);
                }
                break;

            case A_PASA:  // Pasa
                if(*dineroTotalJugador==0)
                {
                    printf("\nSe ha quedado sin fichas para jugar\n");
                    break;
                }
                apuestas[i] = registrarApuestaPasa(dineroTotalJugador);
                fichaTemp.pasa = apuestas[i].fichas;
                if(FICHATEMP_PASA)
                {
                    restriccion(apuestas, i, dineroTotalJugador, &fichaTemp);
                }
                break;

            case A_COLOR: // Color
                if(*dineroTotalJugador==0)
                {
                    printf("\nSe ha quedado sin fichas para jugar\n");
                    break;
                }
                apuestas[i] = registrarApuestaColor(dineroTotalJugador);
                fichaTemp.color = apuestas[i].fichas;
                 if(FICHATEMP_COLOR)
                {
                    restriccion(apuestas, i, dineroTotalJugador, &fichaTemp);
                }

                break;

            case A_PARIDAD: // Par o Impar
                if(*dineroTotalJugador==0)
                {
                    printf("\nSe ha quedado sin fichas para jugar\n");
                    break;
                }
                apuestas[i] = registrarApuestaParidad(dineroTotalJugador);
                fichaTemp.paridad = apuestas[i].fichas;
                 if(FICHATEMP_PARIDAD)
                {
                    restriccion(apuestas, i, dineroTotalJugador, &fichaTemp);
                }

                break;

            case A_COLUMNA: // Columnas
                if(*dineroTotalJugador==0)
                {
                    printf("\nSe ha quedado sin fichas para jugar\n");
                    break;
                }
                apuestas[i] = registrarApuestaColumna(dineroTotalJugador);
                break;

            default: break;

            } // Fin Switch Tipo Apuestas
        } //Fin for Apuestas
    }else
    {
        printf("\nSe ha quedado sin fichas para jugar\n");
    }
}

void restriccion(Apuesta *apuestas, int i, int *dineroTotalJugador, ficha_temp *fichaTemp){ // Restricción para que el usuario no pueda apostar la misma cantidad de fichas en las apuestas de Falta, Pasa, Color y Par o Impar.

    if(apuestas[i].tipo==A_FALTA)
    {
        while((fichaTemp->falta)==(fichaTemp->pasa) || (fichaTemp->falta)==(fichaTemp->color) || (fichaTemp->falta)==(fichaTemp->paridad))
        {
            *dineroTotalJugador += fichaTemp->falta;
            printf("\nYa ingreso ese monto anteriormente en alguna de las otras apuestas que pagan\ndoble, ingrese otro monto.\n");
            printf("Tus apuestas anteriores fueron: Pasa: $%d, Color: $%d, Paridad: $%d\n", fichaTemp->pasa, fichaTemp->color, fichaTemp->paridad);
            apuestas[i] = registrarApuestaFalta(dineroTotalJugador);
            (fichaTemp->falta) = apuestas[i].fichas;
        }
    }else if(apuestas[i].tipo==A_PASA)
    {
        while(fichaTemp->pasa==fichaTemp->falta || fichaTemp->pasa==fichaTemp->color || fichaTemp->pasa==fichaTemp->paridad)
        {
            *dineroTotalJugador += fichaTemp->pasa;
            printf("\nYa ingreso ese monto anteriormente en alguna de las otras apuestas que pagan\ndoble, ingrese otro monto.\n");
            printf("Tus apuestas anteriores fueron: Falta: $%d, Color: $%d, Paridad: $%d\n", fichaTemp->falta, fichaTemp->color, fichaTemp->paridad);
            apuestas[i] = registrarApuestaPasa(dineroTotalJugador);
            fichaTemp->pasa = apuestas[i].fichas;
        }
    }else if(apuestas[i].tipo==A_COLOR)
    {
        while(fichaTemp->color==fichaTemp->falta || fichaTemp->color==fichaTemp->pasa || fichaTemp->color==fichaTemp->paridad)
        {
            *dineroTotalJugador += fichaTemp->color;
            printf("\nYa ingreso ese monto anteriormente en alguna de las otras apuestas que pagan\ndoble, ingrese otro monto.\n");
            printf("Tus apuestas anteriores fueron: Falta: $%d, Pasa: $%d, Paridad: $%d\n", fichaTemp->falta, fichaTemp->pasa, fichaTemp->paridad);
            apuestas[i] = registrarApuestaColor(dineroTotalJugador);
            fichaTemp->color = apuestas[i].fichas;
        }
    }else if(apuestas[i].tipo==A_PARIDAD)
    {
        while(fichaTemp->paridad==fichaTemp->falta || fichaTemp->paridad==fichaTemp->color || fichaTemp->paridad==fichaTemp->pasa)
        {
            *dineroTotalJugador += fichaTemp->paridad;
            printf("\nYa ingreso ese monto anteriormente en alguna de las otras apuestas que pagan\ndoble, ingrese otro monto.\n");
            printf("Tus apuestas anteriores fueron: Falta: $%d, Pasa: $%d, Color: $%d\n", fichaTemp->falta, fichaTemp->pasa, fichaTemp->color);
            apuestas[i] = registrarApuestaParidad(dineroTotalJugador);
            fichaTemp->paridad = apuestas[i].fichas;
        }
    }
}

void balanceFinal(ganancia_perdida arrayregistroGananciaPerdida[RONDAMAX][APUESTAMAX], int *arraynApuestas, int nRondas){

    int i, j;
    int ganancia = 0;
    int perdida = 0;

    for(i=0; i<nRondas; i++)
    {
        for(j=0; j<arraynApuestas[i]; j++)
        {
            ganancia += arrayregistroGananciaPerdida[i][j].ganancia; ///Se refiere a la ganancia del apostador
            perdida += arrayregistroGananciaPerdida[i][j].perdida;  ///Se refiere a la perdida del apostador
        }
    }

    printf("Ganancia total de mesa: $%d\nPerdida total de mesa: $%d\n", perdida, ganancia);

    if(perdida>ganancia)
    {
        printf("\x1b[32m Mesa Ganadora!!!\x1b[0m\n");

    }else if(perdida == ganancia)
    {
        printf("\x1b[33m Mesa No Conforme\x1b[0m\n");

    }else
    {
        printf("\x1b[31m Mesa En Problemas ;)\x1b[0m\n");
    }
}

void porcentajeColor(Apuesta conjuntoApuestas[RONDAMAX][APUESTAMAX], int *arraynApuestas, int nRondas)
{
    int i, j;
    float porcentajerojo= 0;
    float porcentajenegro = 0;
    float rojo = 0;
    float negro = 0;
    float contApuesta = 0;

    for(i=0; i<nRondas; i++)
    {
        for(j=0; j<arraynApuestas[i]; j++)
        {
           if(conjuntoApuestas[i][j].tipo==A_COLOR)
            {
                contApuesta ++;
                if(conjuntoApuestas[i][j].valor==A_COLOR_ROJO)
                {
                     rojo += 1;

                }else if(conjuntoApuestas[i][j].valor==A_COLOR_NEGRO)
                {
                    negro += 1;
                }
            }
        }
    }
    porcentajerojo = (rojo/contApuesta)*100;
    porcentajenegro = (negro/contApuesta)*100;

    if(contApuesta==0)
    {
        printf("No hubo apuestas en Color\n");
    }else
    {
        printf("El porcentaje de apuestas realizadas al color Rojo es %.2f%%.\nEl porcentaje de apuestas realizadas al color negro es %.2f%%.\n", porcentajerojo, porcentajenegro);
    }
}

void apuestaMayorValor(Apuesta conjuntoApuestas[RONDAMAX][APUESTAMAX], int *arraynApuestas, int nRondas){

    int h, i, j, k;

    int sumaTotales[7];
    int mayoresApuestasPorRonda[nRondas];
    int mayorApuestaFinal;
    int mayorRondaFinal;

    for(i=0; i<nRondas;i++)
    {
        for(j=0; j<7; j++)
        {
            sumaTotales[j] = 0;
        }

        for(j=0; j<arraynApuestas[i]; j++)
        {
            if(conjuntoApuestas[i][j].tipo == A_PLENO)
            {

                sumaTotales[0] += conjuntoApuestas[i][j].fichas;

            }else if(conjuntoApuestas[i][j].tipo == A_DOCENAS)
            {

                sumaTotales[1] += conjuntoApuestas[i][j].fichas;

            }else if(conjuntoApuestas[i][j].tipo == A_FALTA)
            {

                sumaTotales[2] += conjuntoApuestas[i][j].fichas;

            }else if(conjuntoApuestas[i][j].tipo == A_PASA)
            {

                sumaTotales[3] += conjuntoApuestas[i][j].fichas;

            }else if(conjuntoApuestas[i][j].tipo == A_COLOR)
            {

                sumaTotales[4] += conjuntoApuestas[i][j].fichas;

            }else if(conjuntoApuestas[i][j].tipo == A_PARIDAD)
            {

                sumaTotales[5] += conjuntoApuestas[i][j].fichas;

            }else if(conjuntoApuestas[i][j].tipo == A_COLUMNA)
            {

                sumaTotales[6] += conjuntoApuestas[i][j].fichas;
            }
        }

        mayoresApuestasPorRonda[i] = sumaTotales[0];

        for(k=1;k<7;k++)
        {
            if(sumaTotales[k]>mayoresApuestasPorRonda[i])
            {
               mayoresApuestasPorRonda[i] = sumaTotales[k];
            }
        }
    }

    mayorApuestaFinal = mayoresApuestasPorRonda[0];
    mayorRondaFinal = 1;

    for(h=1;h<nRondas;h++)
    {
        if(mayoresApuestasPorRonda[h]>mayorApuestaFinal)
        {
           mayorApuestaFinal = mayoresApuestasPorRonda[h];
           mayorRondaFinal = h + 1;
        }
    }
    printf("La mayor apuesta es %d, en la ronda %d\n", mayorApuestaFinal, mayorRondaFinal);
}

void mostrarMesa() ///Funcion para mostrar el paño de la ruleta europea
{
    int i;
    int tercer_columna = 3;
    int segunda_columna = 2;
    int primer_columna = 1;

    for(i=0; i<36; i++)
    {
        if(tercer_columna<=36)
        {
            if(tercer_columna==3)
            {
                printf("\x1b[47m  "); ///Espacio para que que la tercer fila quede alineada con la segunda fila
            }
            if(ROJO_3)
            {
                printf("\x1b[47m\x1b[31m%d   \x1b[0m", tercer_columna);
            }else if(NEGRO_3)
            {
                printf("\x1b[47m\x1b[30m%d   \x1b[0m", tercer_columna);
            }

            tercer_columna += 3;
            if(tercer_columna>36)
            {
                printf(" | 2 a 1 |\n");
            }
        }
        if(tercer_columna>36 && segunda_columna<=35)
        {
            if(segunda_columna==2)
            {
                printf("\x1b[47m\x1b[32m0 \x1b[0m");
            }
            if(ROJO_2)
            {
                printf("\x1b[47m\x1b[31m%d   \x1b[0m", segunda_columna);
            }else if(NEGRO_2)
            {
                printf("\x1b[47m\x1b[30m%d   \x1b[0m", segunda_columna);
            }

            segunda_columna += 3;
            if(segunda_columna>35)
            {
                printf(" | 2 a 1 |\n");
            }
        }
        if(tercer_columna>36 && segunda_columna>35 && primer_columna<=34)
        {
            if(primer_columna==1)
            {
                printf("\x1b[47m  "); ///Espacio para que que la primer fila quede alineada con la segunda fila
            }
            if(ROJO_1)
            {
                printf("\x1b[47m\x1b[31m%d   \x1b[0m", primer_columna);
            }else if(NEGRO_1)
            {
                printf("\x1b[47m\x1b[30m%d   \x1b[0m", primer_columna);
            }

            primer_columna += 3;
            if(primer_columna>34)
            {
                printf(" | 2 a 1 |\n");
            }
        }
    }
    printf("  Primeros 12    |    Segundos 12    |    Terceros 12       | \n");
    printf("  1 - 18 | PARES |\x1b[47m\x1b[31m  ROJO  \x1b[0m|\x1b[47m\x1b[30m  NEGRO  \x1b[0m |  IMPAR  |  19 - 36   | ");
}

void giroIgualColor(int *arrayGiros, int nRondas)
{
    int i, j;
    int contIgualColorRojo = 0;
    int contIgualColorNegro = 0;
    int seguidoRojo = FALSE;
    int seguidoNegro = FALSE;

    for(i=0; i<nRondas; i++)
    {
        for(j=0; j<CANTCOLOR; j++)
        {
            if(arrayGiros[i]==numerosRojos[j])
            {
                contIgualColorRojo ++;

                if(contIgualColorNegro>0)
                {
                    contIgualColorNegro = 0;
                }
                if(contIgualColorRojo>=5)
                {
                    seguidoRojo = TRUE;
                }

            }else if(arrayGiros[i]==numerosNegros[j])
            {
                contIgualColorNegro ++;

                 if(contIgualColorRojo>0)
                {
                    contIgualColorRojo = 0;
                }
                if(contIgualColorNegro>=5)
                {
                    seguidoNegro = TRUE;
                }
            }
        }
    }

    if(seguidoRojo==TRUE && seguidoNegro==FALSE)
    {
        printf("La bola cayó en números rojos 5 veces seguidas.\n");

    }else if(seguidoNegro==TRUE && seguidoRojo==FALSE)
    {
        printf("La bola cayó en números negros 5 veces seguidas.\n");
    }else if(seguidoRojo==TRUE && seguidoNegro==TRUE)
    {
        printf("La bola cayó 5 veces seguidas tanto en números rojos como negros.\n");
    }else
    {
        printf("La bola no cayó 5 veces seguidas en números del mismo color.\n");
    }
}

void promedioApuestasPorRonda(int *arraynApuestas, int nRondas)
{
    float totalApuestas = 0;
    int i;

    for(i=0; i<nRondas; i++)
    {
        totalApuestas += arraynApuestas[i];
    }
    printf("El promedio de apuestas por rondas es: %.2f.\n", totalApuestas / nRondas);
}

void ceroOmultiplosdeDiez(int *arrayGiros, int nRondas)
{
    int i=0;
    int cero = FALSE;
    int multiplo = FALSE;

    for(i=0; i<nRondas; i++)
    {
         if(arrayGiros[i]==0)
         {
             cero=TRUE;
         }
         if(arrayGiros[i]%10==0)
         {
             multiplo = TRUE;
         }
    }

    if(cero==TRUE && multiplo==FALSE)
    {
        printf("El 0 fue un resultado del giro de la ruleta.\n");

    }else if(multiplo==TRUE && cero==FALSE)
    {
        printf("Hubo múltiplos de 10 en los resultados del giro de la ruleta.\n");

    }else if(cero==TRUE && multiplo==TRUE)
    {
        printf("En los resultados del giro de la ruleta salieron tanto el 0 como múltiplos de 10");
    }else
    {
        printf("En los resultados del giro de la ruleta no salió el 0 ni ningún múltiplo de 10");
    }
}

void numeroPrimo(int *arrayGiros, int nRondas)
{
    int i, j;
    int cont;
    int primo = 0;
    for(i=0; i<nRondas; i++)
    {
        cont = 0;
        for(j=1; j<=arrayGiros[i]; j++)
        {
            if(arrayGiros[i]%j==0)
            {
                cont ++;
            }
        }
        if(cont==2)
        {
            primo++;
        }
    }

    if(primo>0)
    {
        if(primo==1)
        {
            printf("La bola cayó una vez en un número primo\n");
        }else
        {
            printf("La bola cayó %d veces en un número primo\n", primo);
        }
    }else
    {
        printf("La bola no cayó en ningún número primo\n");
    }
}

int giroRuleta()
{
    srand(time(NULL));
    int giro = 0;
    giro = rand()%38;
    return giro;
}
