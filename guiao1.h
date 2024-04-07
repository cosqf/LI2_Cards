#ifndef __GUIAO1_H__
#define __GUIAO1_H__

#define MAX 15          // máximo de cartas que podem ser jogadas de uma vez (mão inteira)

typedef enum naipe {Espadas = 1, Copas, Ouros, Paus} NAIPE;

typedef enum valor {As = 1, Dois, Tres, Quatro, Cinco, Seis, Sete, Oito, Nove, Dez, Valete, Cavaleiro, Rainha, Rei} VALOR;

typedef struct carta {
    NAIPE naipe;
    VALOR valor;
    wchar_t hex;
} CARTA;

NAIPE naipe(wchar_t);

VALOR valor(wchar_t);

void regista(wchar_t[][MAX], int);

void converte(wchar_t[][MAX], CARTA[][MAX], int);

void swap(CARTA [], int, int);

int maior (CARTA *,CARTA *);

int partition (CARTA [], int, CARTA *);

void qsort(CARTA [],int);

int valorIgual(CARTA *, CARTA *);

int verificaConjunto(CARTA [], int);

int verificaSequencia(CARTA [], int );

int verificaSequenciaDupla(CARTA [], int);

void resultado(CARTA [], int);

#endif