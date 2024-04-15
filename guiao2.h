#ifndef __GUIAO2_H__
#define __GUIAO2_H__

typedef struct teste {
    int nlinhas;                // tamanho do array 2d
    size_t tamanho;                // tamanho comum a todas as linhas; se for 0, o tamanho das linhas
    wchar_t cartas[MAX][MAX];
} TESTE;

void leInputs (int, TESTE[]);

void registaTamanhos (int, TESTE[]);

void ordenaTeste (TESTE *);

void ordena (int, TESTE[]);

int todasConjunto (TESTE *);

int todasSequencia (TESTE *);

int todasSequenciaDupla (TESTE *);

int testeValido (TESTE *);

void swapArray (wchar_t[][MAX], int, int);

int maiorArray (wchar_t[], wchar_t[]);

int partitionArray (wchar_t[][MAX], int, wchar_t[]);

void qsortArray (wchar_t[][MAX], int);

void printaTeste (TESTE *);

void printaOutput (int, TESTE[]);

#endif