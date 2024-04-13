#ifndef __GUIAO2_H__
#define __GUIAO2_H__

typedef struct teste {
    int nlinhas;                // tamanho do array 2d
    size_t tamanho;                // tamanho comum a todas as linhas; se for 0, o tamanho das linhas
    wchar_t cartas[MAX][MAX];
} TESTE;

void leInputs (int, TESTE[MAX]);

void registaTamanhos (int, TESTE[MAX]);

void swap(wchar_t[], int, int);

int maior(wchar_t, wchar_t);

int partition (wchar_t[], int, wchar_t);

void qsort (wchar_t[], int);

void ordenaTeste (TESTE *);

void ordena (int, TESTE[MAX]);

#endif