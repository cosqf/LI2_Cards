#ifndef __GUIAO1New_H__
#define __GUIAO1New_H__



typedef enum naipe {Espadas = 1, Copas, Ouros, Paus} NAIPE;

typedef enum valor {As = 1, Dois, Tres, Quatro, Cinco, Seis, Sete, Oito, Nove, Dez, Valete, Cavaleiro, Rainha, Rei} VALOR;


NAIPE naipe(wchar_t);

VALOR valor(wchar_t);

void swap(wchar_t[], int, int);

int maior(wchar_t, wchar_t);

int partition (wchar_t[], int, wchar_t);

void qsort (wchar_t[], int);

int valorIgual(wchar_t , wchar_t );

int verificaConjunto(wchar_t, int);

int verificaSequencia(wchar_t[], int);

int verificaSequenciaDupla(wchar_t , int );

#endif