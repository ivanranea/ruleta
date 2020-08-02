#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define CANTROJOS 18
#define CANTNEGROS 18
#define NROSPORCOLUMNA 12
#define RONDAMAX 20
#define APUESTAMAX 10
#define TRUE 1
#define FALSE 0

#define A_PLENO 1

#define A_DOCENAS 2
#define A_PRIMER_DOCENA 1
#define A_SEGUNDA_DOCENA 2
#define A_TERCERA_DOCENA 3

#define A_FALTA 3 // Apuestas del 1..18

#define A_PASA 4 // Apuestas del 19..36

#define A_COLOR 5
#define A_COLOR_ROJO 1
#define A_COLOR_NEGRO 2

#define A_PARIDAD 6
#define A_PARIDAD_PAR 1
#define A_PARIDAD_IMPAR 2

#define A_COLUMNA 7
#define A_PRIMER_COLUMNA 1
#define A_SEGUNDA_COLUMNA 2
#define A_TERCERA_COLUMNA 3

#define FICHATEMP_FALTA fichaTemp.falta==fichaTemp.pasa || fichaTemp.falta==fichaTemp.color || fichaTemp.falta==fichaTemp.paridad
#define FICHATEMP_PASA fichaTemp.pasa==fichaTemp.falta || fichaTemp.pasa==fichaTemp.color || fichaTemp.pasa==fichaTemp.paridad
#define FICHATEMP_COLOR fichaTemp.color==fichaTemp.falta || fichaTemp.color==fichaTemp.pasa || fichaTemp.color==fichaTemp.paridad
#define FICHATEMP_PARIDAD fichaTemp.paridad==fichaTemp.falta || fichaTemp.paridad==fichaTemp.pasa || fichaTemp.paridad==fichaTemp.color

const int numerosRojos[] = {1,3,5,7,9,12,14,16,18,19,21,23,25,27,30,32,34,36};
const int numerosNegros[] = {2,4,6,8,10,11,13,15,17,20,22,24,26,28,29,31,33,35};
const int columna1[] = {1,4,7,10,13,16,19,22,25,28,31,34};
const int columna2[] = {2,5,8,11,14,17,20,23,26,29,32,35};
const int columna3[] = {3,6,9,12,15,18,21,24,27,30,33,36};



typedef struct {
    int tipo; // Numero, paridad, color, fila, etc
    int valor; // 34, rojo, par, fila 2
    int fichas; // cantidad de fichas apostadas
} Apuesta;
// Para apostar 5 fichas al rojo Apuesta(tipo: 5, valor: 1, fichas: 5)

typedef struct {
    int ganancia;
    int perdida;

} ganancia_perdida;

typedef struct{
    int falta;
    int pasa;
    int color;
    int paridad;

} ficha_temp;

void imprimirApuesta(Apuesta a){
    printf("Apuesta | tipo: %d | valor: %d | fichas: %d |\n", a.tipo, a.valor, a.fichas);
}

void imprimirGanancia(ganancia_perdida g){
    printf("Ganancia: %d | Perdida: %d\n", g.ganancia, g.perdida);
}


void restriccion(Apuesta *apuestas, int i, int *dineroTotalJugador, ficha_temp *fichaTemp);


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

            for(i=0; i<CANTROJOS; i++)
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

            for(i=0; i<CANTNEGROS; i++)
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

    /// INICIO FUNCION RESOLUCION DE PREMIOS
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

        } //Fin switch principal

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


    if(ganancia==0) // Deberiamos mostrar las ganancias totales o ir mostrando los resultados de cada apuesta.
    {
        printf("\nLa ganancia de la mesa fue: $%d.\nEl jugador no tuvo ganancias.\n\n", perdida);

    }else if(perdida==0)
    {
        printf("\nLa mesa no tuvo ganancias.\nLa ganancia del jugador fue: $%d.\n\n", ganancia);
    }else
    {
        printf("\nLa ganancia de la mesa fue: $%d.\nLa ganancia del jugador fue: $%d.\n\n", perdida, ganancia);
    }


} // Fin funcion resolucion de premios

int registrarMontoFichas(int *dineroTotalJugador)
{
    // Pasar como parametro dineroTotalJugador
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

    //Llamar funcion mostrar paño

    for(i=0; i<nApuestas; i++) // Comienzo for apuestas
    {
        if(i==(nApuestas-2))
        {
            printf("Esta es su penúltima apuesta\n");
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
            apuestas[i] = registrarApuestaPlenos(dineroTotalJugador);
            break;

        case A_DOCENAS: //Docenas
            apuestas[i] = registrarApuestaDocenas(dineroTotalJugador);
            break;

        case A_FALTA:  // Falta
            apuestas[i] = registrarApuestaFalta(dineroTotalJugador);
            fichaTemp.falta = apuestas[i].fichas;

            if(FICHATEMP_FALTA)
            {
                restriccion(apuestas, i, dineroTotalJugador, &fichaTemp);
            }
            break;

        case A_PASA:  // Pasa
            apuestas[i] = registrarApuestaPasa(dineroTotalJugador);
            fichaTemp.pasa = apuestas[i].fichas;
            if(FICHATEMP_PASA)
            {
                restriccion(apuestas, i, dineroTotalJugador, &fichaTemp);
            }
            break;

        case A_COLOR: // Color
            apuestas[i] = registrarApuestaColor(dineroTotalJugador);
            fichaTemp.color = apuestas[i].fichas;
             if(FICHATEMP_COLOR)
            {
                restriccion(apuestas, i, dineroTotalJugador, &fichaTemp);
            }

            break;

        case A_PARIDAD: // Par o Impar
            apuestas[i] = registrarApuestaParidad(dineroTotalJugador);
            fichaTemp.paridad = apuestas[i].fichas;
             if(FICHATEMP_PARIDAD)
            {
                restriccion(apuestas, i, dineroTotalJugador, &fichaTemp);
            }

            break;

        case A_COLUMNA: // Columnas =
            apuestas[i] = registrarApuestaColumna(dineroTotalJugador);

            break;

        default: break;

        } // Fin Switch Tipo Apuestas
    } //Fin for Apuestas
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

void balanceFinal(ganancia_perdida *registroGananciaPerdida, int nApuestas){

    int ganancia = 0;
    int perdida = 0;

    for(int i=0; i<nApuestas; i++)
    {
        ganancia += registroGananciaPerdida[i].ganancia; ///Se refiere a la ganancia del apostador
        perdida += registroGananciaPerdida[i].perdida;  ///Se refiere a la perdida del apostador
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
    float porcentajerojo= 0.0;
    float porcentajenegro = 0.0;
    float rojo = 0.0;
    float negro = 0.0;
    float contApuesta = 0.0;

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

    porcentajerojo = rojo/contApuesta;
    porcentajenegro = negro/contApuesta;

    printf("El porcentaje de apuestas realizadas al color Rojo es %.2f.\nEl porcentaje de apuestas realizadas al color negro es %.2f.\n", porcentajerojo, porcentajenegro);

}

void apuestaMayorValor(Apuesta conjuntoApuestas[RONDAMAX][APUESTAMAX], int *arraynApuestas, int nRondas){

    int h, i, j, k;

    int mayorDeApuestaPorRonda = 0;
    int mayorDeTodasLasRondas = 0;
    int sumaTotales[7];
    int mayoresApuestasPorRonda[nRondas];
    int mayorApuestaFinal;
    int mayorRondaFinal;

    for(i=0;i<7;i++)
    {
        sumaTotales[i] = 0;
    }


    for(i=0; i<nRondas;i++)
    {
        for(j=0;j<arraynApuestas[i];j++)
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

            }else
            {

                sumaTotales[6] += conjuntoApuestas[i][j].fichas;
                printf("hahaha\n");
            }


        }

        for(i=0;i<7;i++)
        {
            printf("sumastotales, posicion %d : %d\n",i , sumaTotales[i]);
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

    for(h=1;h<7;h++)
    {
        if(mayoresApuestasPorRonda[h]>mayorApuestaFinal)
        {
           mayorApuestaFinal = mayoresApuestasPorRonda[h];
           mayorRondaFinal = h + 1;

        }
    }
    printf("La mayor apuesta es %d, en la ronda %d\n", mayorApuestaFinal, mayorRondaFinal);

}




int main3(){
    // Esta funcion es un test para preguntarApuestasAlUsuario()
    int dineroTotalJugador = 1000;
    int nApuestas;
    int i;
    printf("Elija la cantidad de apuestas: ");
    scanf("%d", &nApuestas);
    Apuesta apuestas[nApuestas];
    preguntarApuestasAlUsuario(apuestas, nApuestas, &dineroTotalJugador);
    for (i=0; i<nApuestas; i++)
    {
        imprimirApuesta(apuestas[i]);
    }
    return 0;
}

int main2(){ //funcion para testear resolucion de apuestas
    int i;
    int nApuestas = 7;
    Apuesta apuestas[nApuestas];
    int giro = 1;
    for(i=0; i<nApuestas; i++)
    {
        apuestas[i].tipo = 1+i;
        apuestas[i].valor = 1;
        apuestas[i].fichas = 10;
    }

    for(i=0; i<nApuestas; i++){
        imprimirApuesta(apuestas[i]);

    }

    ganancia_perdida registroGananciaPerdida[nApuestas];

    resolucionApuestas(apuestas, registroGananciaPerdida, nApuestas, giro);

    for(i=0; i<nApuestas; i++)
    {
        imprimirGanancia(registroGananciaPerdida[i]);
    }
    return 0;
}

int main()
{
    float nRondas = 0;
    float nApuestas = 0;
    int arraynApuestas[APUESTAMAX];
    int dineroTotalJugador = 1000;
    Apuesta apuestas[APUESTAMAX];
    int i;
    int j;
    Apuesta conjuntoApuestas[RONDAMAX][APUESTAMAX];
    ganancia_perdida registroGananciaPerdida;
    registroGananciaPerdida.ganancia = 0;
    registroGananciaPerdida.perdida = 0;
    int giro = 3;


    printf("Ingrese cuántas rondas desea jugar: ");
    scanf("%f", &nRondas);

    for(i=0; i<nRondas; i++)
    {
        printf("Indique cuántas apuestas desea realizar: ");
        scanf("%f", &nApuestas);
        arraynApuestas[i]=nApuestas;

        preguntarApuestasAlUsuario(apuestas, nApuestas, &dineroTotalJugador);

        for(j=0; j<nApuestas; j++)
        {
            conjuntoApuestas[i][j] = apuestas[j];

        }
        //funcion giroRuleta
        resolucionApuestas(apuestas, &registroGananciaPerdida, nApuestas, giro);

        }

        printf("El promedio de apuestas por rondas es: %.2f.\n", nApuestas / nRondas);

        porcentajeColor(conjuntoApuestas, arraynApuestas, nRondas);

        apuestaMayorValor(conjuntoApuestas, arraynApuestas, nRondas);

    return 0;
}
