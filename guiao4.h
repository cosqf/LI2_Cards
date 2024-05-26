#ifndef __GUIAO4_H__
#define __GUIAO4_H__

#define MAX_MAO 56  // 55 cartas possíveis no máximo + 1 posição para o '\0'
#define MAX_ULT 29  // 28 cartas possíveis para a combinação mais longa (dupla sequência do ás ao rei) + 1 para o '\0'

typedef struct tested {
    wchar_t ultima[MAX_ULT];
    wchar_t mao[MAX_MAO];
} TESTED;

typedef enum comb {Nada, Conjunto, Sequencia, DuplaSequencia} COMBINACAO;

void getLinha (wchar_t[]);

void getTestes (TESTED[], int);


COMBINACAO combinacaoUltima (wchar_t[]);

void geraCombinacoes (TESTED *);

void geraConjuntos (wchar_t [], int , wchar_t );

int freqConj (wchar_t [], wchar_t );

void filtraConj (wchar_t [], int , wchar_t []);

void filtraSeq (wchar_t [], int , wchar_t [], int );

int freqSeq (wchar_t [],int,int);

void filtraDupSeq (wchar_t [], int , wchar_t [], int );

int freqDupSeq (wchar_t [],int,int);

void printConj(wchar_t [], int , wchar_t);

void printSeq(wchar_t [], int , wchar_t,int *);

void printDupSeq(wchar_t [], int , wchar_t,int *);

void combinaConj(wchar_t [], int, int , wchar_t [], int , wchar_t, int *);

void combinaSeq(wchar_t [], int, int , wchar_t [], int , wchar_t, int *);

void combinaDupSeq(wchar_t [], int, int , wchar_t [], int , wchar_t, int *);

void geraSequencias (wchar_t[], int, wchar_t);

void geraDuplasSequencias (wchar_t[], int, wchar_t,int);

void geraRei (wchar_t [], int , wchar_t );

int geraConjuntosReis (wchar_t [], int , wchar_t);

#endif