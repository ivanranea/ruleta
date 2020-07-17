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
// TODO Convertir en constantes
//int numerosRojos[]={1,3,5,7,9,12,14,16,18,19,21,23,25,27,30,32,34,36};
//int numerosNegros[]={2,4,6,8,10,11,13,15,17,20,22,24,26,28,29,31,33,35};
//int columna1[]={1,4,7,10,13,16,19,22,25,28,31,34};
//int columna2[]={2,5,8,11,14,17,20,23,26,29,32,35};
//int columna3[]={3,6,9,12,15,18,21,24,27,30,33,36};
#define A_NUMERO 1

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


typedef struct {
    int tipo; // Numero, paridad, color, fila, etc
    int valor; // 34, rojo, par, fila 2
    int fichas; // cantidad de fichas apostadas
} Apuesta;
// Para apostar 5 fichas al rojo Apuesta(tipo: 5, valor: 1, fichas: 5)

void imprimirApuesta(Apuesta a){
    printf("Apuesta | tipo: %d | valor: %d | fichas: %d |\n", a.tipo, a.valor, a.fichas);
}


//int main2()
//{
//    int giro = 20;
//    int ganancia = 0;
//    int perdida = 0;
//    int nApuestas = 8;
//    int tipoApuestas[nApuestas]; //Array en el que se va a guardar el código del tipo de apuesta
//    int fichasApostadas[nApuestas]; //Array en el que se va a guardar la cantidad de fichas apostadas en un tipo de apuesta
//    int tipoDocena [3];
//    int tipoColor [2];
//    int parOimpar [2];
//    int tipoColumna [3];
//    int apuestaGanada = FALSE;
//    int plenos[nApuestas];
//    int dineroTotalJugador = 200; //Dinero inicial del jugador, no se discriminan las fichas.
//    int fichasTemp = 0;
//    int i, j;
//    i = 0;
//    j = 0;
//
//
//
//    ///INICIO FUNCION INGRESO DE APUESTAS
//
//    printf("Elija la cantidad de apuestas: ");
//    scanf("%d", &nApuestas);
//
//    for(i=0; i<nApuestas; i++)
//    {
//        fichasApostadas[i] = 0;
//    }
//
//    preguntarApuestasAlUsuario(nApuestas, &tipoApuetas, &fichasApostadas);
//
//    /// INICIO FUNCION RESOLUCION DE PREMIOS
//
//    for(i=0; i<nApuestas; i++) // Inicio for principal
//    {
//
//        switch(tipoApuestas[i])
//        {
//            case 1: //Numeros Plenos
//
//                if(giro==plenos[i])
//                {
//                    ganancia += 35*fichasApostadas[i];
//
//                }else
//                {
//                    perdida += fichasApostadas[i];
//                }
//                break;
//
//            case 2: //Docenas
//                switch(tipoDocena[i])
//                {
//                    case 1: //Primera docena
//
//                        if(giro>0 && giro<=12)
//                        {
//                            ganancia += 3*fichasApostadas[i];
//
//                        }else
//                        {
//                            perdida += fichasApostadas[i];
//                        }
//                        break;
//
//                    case 2: //Segunda docena
//
//                        if(giro>12 && giro<=24)
//                        {
//                            ganancia += 3*fichasApostadas[i];
//
//                        }else
//                        {
//                            perdida += fichasApostadas[i];
//                        }
//                        break;
//
//                    case 3: //Tercera docena
//
//                        if(giro>24)
//                        {
//                            ganancia += 3*fichasApostadas[i];
//
//                        }else
//                        {
//                            perdida += fichasApostadas[i];
//                        }
//                        break;
//                }
//
//            case 3: //Falta (1 al 18)
//
//                if(giro>0 && giro<=18)
//                {
//                    ganancia += 2*fichasApostadas[i];
//
//                }else
//                {
//                    perdida += fichasApostadas[i];
//                }
//                break;
//
//            case 4: //Pasa (19 al 36)
//
//                if(giro>=19 && giro<=36)
//                {
//                    ganancia += 2*fichasApostadas[i];
//
//                }else
//                {
//                    perdida += fichasApostadas[i];
//                }
//                break;
//
//            case 5: //Color
//
//                switch(tipoColor[i])
//                {
//                    case 1: //Rojo
//
//                        apuestaGanada = FALSE;
//                        for(j=0; j<CANTROJOS; j++)
//                        {
//                            if(giro==numerosRojos[j])
//                            {
//                                ganancia += 2*fichasApostadas[i];
//                                apuestaGanada = TRUE;
//                                break;
//
//                            }
//                        }
//                        if(apuestaGanada==FALSE)
//                        {
//                            perdida += fichasApostadas[i];
//                        }
//                        break;
//
//                    case 2: //Negro
//
//                        apuestaGanada = FALSE;
//                        for(j=0; j<CANTNEGROS; j++)
//                        {
//                            if(giro==numerosNegros[j])
//                            {
//                                ganancia += 2*fichasApostadas[i];
//                                apuestaGanada = TRUE;
//                                break;
//
//                            }
//                        }
//                        if(apuestaGanada==FALSE)
//                        {
//                            perdida += fichasApostadas[i];
//                        }
//                        break;
//                }
//
//            case 6: //Pares o Impares
//
//                switch(parOimpar[i])
//                {
//                    case 1: //Par
//
//                        if(giro%2==0)
//                        {
//                            ganancia += 2*fichasApostadas[i];
//
//                        }else
//                        {
//                            perdida += fichasApostadas[i];
//                        }
//                        break;
//
//                    case 2: //Impar
//
//                        if(giro%2!=0)
//                        {
//                            ganancia += 2*fichasApostadas[i];
//
//                        }else
//                        {
//                            perdida += fichasApostadas[i];
//                        }
//                        break;
//                }
//
//            case 7: // Columnas
//
//                apuestaGanada = FALSE;
//                switch(tipoColumna[i])
//                {
//                    case 1: //Columna del 1
//
//
//                        for(j=0; j<NROSPORCOLUMNA; j++)
//                        {
//                            if(giro==columna1[j])
//                            {
//                                ganancia += 3*fichasApostadas[i];
//                                apuestaGanada = TRUE;
//                                break;
//                            }
//                        }
//                        if(apuestaGanada==FALSE)
//                        {
//                            perdida += fichasApostadas[i];
//                        }
//                        break;
//
//                    case 2: //Columna del 2
//
//                        for(j=0; j<NROSPORCOLUMNA; j++)
//                        {
//                            if(giro==columna2[j])
//                            {
//                                ganancia += 3*fichasApostadas[i];
//                                apuestaGanada = TRUE;
//                                break;
//
//                            }
//                        }
//                        if(apuestaGanada==FALSE)
//                        {
//                            perdida += fichasApostadas[i];
//                        }
//                        break;
//
//                    case 3: //Columna del 3
//
//                        for(j=0; j<NROSPORCOLUMNA; j++)
//                        {
//                            if(giro==columna3[j])
//                            {
//                                ganancia += 3*fichasApostadas[i];
//                                apuestaGanada = TRUE;
//                                break;
//
//                            }
//                        }
//                        if(apuestaGanada==FALSE)
//                        {
//                            perdida += fichasApostadas[i];
//                        }
//                        break;
//                } //Fin switch Columnas
//
//            default: break;
//
//        } //Fin switch principal
//
//
//    } //Fin for principal
//
//    printf("\nGanancias: %d\n", ganancia);
//    printf("Perdidas: %d\n", perdida);
//
//    return 0;
//}

int registrarMontoFichas(){
    // TODO Pasar como parametro dineroTotalJugador
    while(TRUE) // Inicio ingreso de fichas para la apuesta
    {
        printf("\nFichas disponibles: $1, $2, $5, $10, $50, $100\nDinero disponible: %d\nCuando desee finalizar la apuesta ingrese 0\nIngrese la ficha que desea apostar: ", dineroTotalJugador);
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
            fichasApostadas[i] += fichasTemp;

            if(fichasApostadas[i]>dineroTotalJugador)
            {
                printf("\nEl valor de las fichas excede su dinero disponible ($%d),\nvuelva a ingresar las fichas.\n", dineroTotalJugador);
                fichasApostadas[i] = 0;
                fichasTemp = 0;

            }else
            {
                printf("\nApuesta total: $%d\n", fichasApostadas[i]);
                dineroTotalJugador -= fichasTemp;
            }

        }
    }
    // TODO retornar entero que representa fichas
}


Apuesta registrarApuestaPlenos(){
    int valor;
    printf("Ingrese el número al cual desea apostar (0 al 36): ");
    scanf("%d", &valor);
    while(valor<0 || valor>36)
    {
        printf("Ingreso incorrecto, elija un número entre el 0 y el 36: ");
        scanf("%d", &valor);
    }
    Apuesta a;
    a.tipo = A_NUMERO;
    a.valor = valor;
    a.fichas = registrarMontoFichas();
    return a;
}

Apuesta registrarApuestaDocenas(){
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
    a.tipo = A_DOCENA;
    a.valor = valor;
    a.fichas = registrarMontoFichas();
    return a;
}

Apuesta registrarApuestaColor(){
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
    a.fichas = registrarMontoFichas();
    return a;
}

Apuesta registrarApuestaParidad(){
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
    a.fichas = registrarMontoFichas();
    return a;
}

Apuesta registrarApuestaColumna(){
    int valor;
    printf("Ingrese el tipo de columna a la que desea apostar:\n1.Columna del 1\n2.Columna del 2\n3.Columna del 3\n");
    scanf("%d", &tipoColumna[i]);
    while(valor<=0 || valor>3)
    {
        printf("Ingreso incorrecto, elija a qué columna desea apostar (1, 2 o 3): ");
        scanf("%d", &valor);
    }


    Apuesta a;
    a.tipo = A_COLUMNA;
    a.valor = valor;
    a.fichas = registrarMontoFichas();
    return a;
}



void preguntarApuestasAlUsuario(int nApuestas){
    Apuesta apuestas[];
    printf("Elija cuál será el nro de tipo de apuesta a realizar:\n");

    for(i=0; i<nApuestas; i++) // Comienzo for apuestas
    {

        printf("\n1.Pleno\n2.Docenas\n3.Falta (1 al 18)\n4.Pasa (19 al 36)\n5.Color\n6.Pares o Impares\n7.Columnas\n");
        printf("\nApuesta nro %d: ", i+1);
        scanf("%d", &tipoApuestas[i]);

        while(tipoApuestas[i]<=0 || tipoApuestas[i]>7)
        {
            printf("Ingreso incorrecto, elija un tipo de apuesta (1 al 7): ");
            scanf("%d", &tipoApuestas[i]);
        }

        switch(tipoApuestas[i]) //Inicio Swith Tipo Apuestas
        {
            case A_NUMERO: //Plenos
                apuestas[i] = registrarApuestaPlenos();
                break;

            case A_DOCENAS: //Docenas
                apuestas[i] = registrarApuestaDocenas();
                break;

            case 3: break; // Falta
                // TODO - Ivi
            case 4: break; // Pasa
                // TODO - Ivi
            case A_COLOR: // Color
                apuestas[i] = registrarApuestaColor(); // TODO Mover a una funcion - Lore
                break;

            case A_PARIDAD: // Par o Impar
                apuestas[i] = registrarApuestaParidad();
                // TODO Mover a una funcion - Lore
                break;

            case A_COLUMNA: // Columnas =
                apuestas[i] = registrarApuestaColumna();
                // TODO Mover a una funcion - Lore
                break;

            default: break;

        } // Fin Switch Tipo Apuestas






    } //Fin for Apuestas
    // TODO retornar array
}

void main(){
    // Esta funcion es un test para preguntarApuestasAlUsuario()
    int dineroTotalJugador = 1000;
    printf("Elija la cantidad de apuestas: ");
    scanf("%d", &nApuestas);

    Apuesta apuestas = preguntarApuestasAlUsuario(nApuestas);
    for (int i=0;i<nApuestas;i++){
        imprimirApuesta(apuestas[i])
    }
}

void main3(){
    // Esta funcion es un test para registrarMontoFichas
    int resultado = registrarMontoFichas(500);
    printf("La cantidad de fichas apostadas es: %d\n", resultado);
}
