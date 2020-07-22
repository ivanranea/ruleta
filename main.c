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

void imprimirApuesta(Apuesta a){
    printf("Apuesta | tipo: %d | valor: %d | fichas: %d |\n", a.tipo, a.valor, a.fichas);
}

void imprimirGanancia(ganancia_perdida g){
    printf("Ganancia: %d | Perdida: %d\n", g.ganancia, g.perdida);
}

int testResolucionApuestas(){ //funcion para testear resolucion de apuestas
    int i;
    int nApuestas = 3;
    Apuesta apuestas[nApuestas];
    Apuesta a;
    int giro = 1;
    for(i=0; i<3; i++)
    {
        a = apuestas.tipo = 1+i;
        a = apuestas.valor = 1+i;
        a = apuestas.fichas = 1+i;
        apuestas[i] = a;
    }

    ganancia_perdida registroGananciaPerdida[nApuestas];

    resolucionApuestas(apuestas, registroGananciaPerdida, nApuestas, giro);

    for(i=0; i<nApuestas; i++)
    {
        imprimirGanancia(registroGananciaPerdida[i]);
    }

}

int registrarGananciaPleno(Apuesta apuestas, int giro){
    int ganancia = 0;
    int perdida = 0;
    if(giro==apuestas.valor)
                {
                    ganancia += 35*apuestas.fichas;

                }else
                {
                    perdida += apuestas.fichas;
                }
    ganancia_perdida g;

    g.ganancia = ganancia;
    g.perdida = perdida;

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

                registroGananciaPerdida[i] = registrarGananciaPleno(a);
                break;

            case 2: //Docenas
                switch(tipoDocena[i])
                {
                    case 1: //Primera docena

                        if(giro>0 && giro<=12)
                        {
                            ganancia += 3*fichasApostadas[i];

                        }else
                        {
                            perdida += fichasApostadas[i];
                        }
                        break;

                    case 2: //Segunda docena

                        if(giro>12 && giro<=24)
                        {
                           ganancia += 3*fichasApostadas[i];

                        }else
                        {
                            perdida += fichasApostadas[i];
                        }
                        break;

                    case 3: //Tercera docena

                        if(giro>24)
                        {
                            ganancia += 3*fichasApostadas[i];

                        }else
                        {
                            perdida += fichasApostadas[i];
                        }
                        break;
                }

            case A_FALTA: //Falta (1 al 18)

                if(giro>0 && giro<=18)
                {
                   ganancia += 2*a.fichas;

                }else
                {
                    perdida += a.fichas;
                }
                break;

            case 4: //Pasa (19 al 36)

                if(giro>=19 && giro<=36)
                {
                    ganancia += 2*fichasApostadas[i];

                }else
                {
                    perdida += fichasApostadas[i];
                }
                break;

            case A_COLOR: //Color

                switch(a.valor)
                {
                    case A_COLOR_ROJO: //Rojo

                        int apuestaGanada = FALSE;
                        for(i=0; i<CANTROJOS; i++)
                        {
                            if(giro==numerosRojos[i])
                            {
                                ganancia += 2*a.fichas;
                                apuestaGanada = TRUE;
                                break;

                            }
                        }
                        if(apuestaGanada==FALSE)
                        {
                            perdida += a.fichas;
                        }
                        break;

                    case A_COLOR_NEGRO: //Negro

                        int apuestaGanada = FALSE;
                        for(i=0; i<CANTNEGROS; i++)
                        {
                            if(giro==numerosNegros[i])
                            {
                                ganancia += 2*a.fichas;
                                apuestaGanada = TRUE;
                                break;

                            }
                        }
                        if(apuestaGanada==FALSE)
                        {
                            perdida += a.fichas;
                        }
                        break;
                }

            case 6: //Pares o Impares

                switch(parOimpar[i])
                {
                    case 1: //Par

                        if(giro%2==0)
                        {
                            ganancia += 2*fichasApostadas[i];

                        }else
                        {
                            perdida += fichasApostadas[i];
                        }
                        break;

                    case 2: //Impar

                        if(giro%2!=0)
                        {
                            ganancia += 2*fichasApostadas[i];

                        }else
                        {
                            perdida += fichasApostadas[i];
                        }
                        break;
                }

            case A_COLUMNA: // Columnas

                apuestaGanada = FALSE;
                switch(a.valor)
                {
                    case A_PRIMER_COLUMNA: //Columna del 1


                        for(j=0; j<NROSPORCOLUMNA; j++)
                        {
                            if(giro==columna1[j])
                            {
                                ganancia += 3*a.fichas;
                                apuestaGanada = TRUE;
                                break;
                            }
                        }
                        if(apuestaGanada==FALSE)
                        {
                            perdida += a.fichas;
                        }
                        break;

                    case A_SEGUNDA_COLUMNA: //Columna del 2

                        for(j=0; j<NROSPORCOLUMNA; j++)
                        {
                            if(giro==columna2[j])
                            {
                                ganancia += 3*a.fichas;
                                apuestaGanada = TRUE;
                                break;

                            }
                        }
                        if(apuestaGanada==FALSE)
                        {
                            perdida += a.fichas;
                        }
                        break;

                    case A_TERCERA_COLUMNA: //Columna del 3

                        for(j=0; j<NROSPORCOLUMNA; j++)
                        {
                            if(giro==columna3[j])
                            {
                                ganancia += 3*a.fichas;
                                apuestaGanada = TRUE;
                                break;

                            }
                        }
                        if(apuestaGanada==FALSE)
                        {
                            perdida += a.fichas;
                        }
                        break;
                } //Fin switch Columnas

            default: break;

        } //Fin switch principal


    } //Fin for principal


    /*if(registroGananciaPerdida.ganancia==0) // Deberiamos mostrar las ganancias totales o ir mostrando los resultados de cada apuesta.
    {
        printf("La ganancia de la mesa fue: %d.\nEl jugador no tuvo ganancias.", registroGananciaPerdida.perdida);

    }else if(registroGananciaPerdida.perdida==0)
    {
        printf("La mesa no tuvo ganancias.\nLa ganancia del jugador fue: %d.", registroGananciaPerdida.ganancia);
    }else
    {
        print("La ganancia de la mesa fue: %d.\nLa ganancia del jugador fue: %d.", registroGananciaPerdida.perdida, registroGananciaPerdida.ganancia);
    }*/


} // Fin funcion resolucion de premios


/*int registrarMontoFichas(int *dineroTotalJugador){
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
        }else
        {

            if(fichasTemp>(*dineroTotalJugador))
            {

                printf("\nEl valor de las fichas excede su dinero disponible ($%d),\nvuelva a ingresar las fichas.\n", *dineroTotalJugador);
                *dineroTotalJugador += fichasApostadas;
                fichasApostadas = 0;
                fichasTemp = 0;


            }else
            {
                *dineroTotalJugador -= fichasTemp;
                fichasApostadas += fichasTemp;
                printf("\nApuesta total: $%d\n", fichasApostadas);


            }

        }
    }
    return fichasApostadas; //retornar entero que representa fichas
}*/


/*Apuesta registrarApuestaPlenos(int *dineroTotalJugador){
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

Apuesta registrarApuestaDocenas(int *dineroTotalJugador){
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

Apuesta registrarApuestaFalta(int *dineroTotalJugador){

    Apuesta a;
    a.tipo = A_FALTA;
    a.valor = 0;
    a.fichas = registrarMontoFichas(dineroTotalJugador);
    return a;
}

Apuesta registrarApuestaPasa(int *dineroTotalJugador){

    Apuesta a;
    a.tipo = A_PASA;
    a.valor = 0;
    a.fichas = registrarMontoFichas(dineroTotalJugador);
    return a;
}


Apuesta registrarApuestaColor(int *dineroTotalJugador){
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

Apuesta registrarApuestaParidad(int *dineroTotalJugador){
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

Apuesta registrarApuestaColumna(int *dineroTotalJugador){
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



void preguntarApuestasAlUsuario(Apuesta *apuestas, int nApuestas, int *dineroTotalJugador){
    int i;

    for(i=0; i<nApuestas; i++) // Comienzo for apuestas
    {
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
                break;

            case A_PASA:  // Pasa
                apuestas[i] = registrarApuestaPasa(dineroTotalJugador);
                break;

            case A_COLOR: // Color
                apuestas[i] = registrarApuestaColor(dineroTotalJugador);
                break;

            case A_PARIDAD: // Par o Impar
                apuestas[i] = registrarApuestaParidad(dineroTotalJugador);

                break;

            case A_COLUMNA: // Columnas =
                apuestas[i] = registrarApuestaColumna(dineroTotalJugador);

                break;

            default: break;

        } // Fin Switch Tipo Apuestas
    } //Fin for Apuestas
}*/

/*int main(){
    // Esta funcion es un test para preguntarApuestasAlUsuario()
    int dineroTotalJugador = 1000;
    int nApuestas;
    int i;
    printf("Elija la cantidad de apuestas: ");
    scanf("%d", &nApuestas);
    Apuesta apuestas[nApuestas];
    preguntarApuestasAlUsuario(apuestas, nApuestas, &dineroTotalJugador);
    for (i=0;i<nApuestas;i++){
        imprimirApuesta(apuestas[i]);
    }
    return 0;
}*/

int main(){
    int nApuestas = 5;
    ganancia_perdida registroGananciaPerdida[nApuestas];
    int giro = 20;
    testResolucionApuestas();
}

