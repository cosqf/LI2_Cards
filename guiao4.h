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

int frequencia (wchar_t []);

void escreve (wchar_t [],int);

void func (wchar_t [],int); 

void geraCombinacoes (TESTED *);

void geraConjuntos (wchar_t [], int , wchar_t );

int frequencia (wchar_t [], wchar_t );

void filtraArray (wchar_t [], int , wchar_t []);

void printaComb (wchar_t []);

void iniciaALista (wchar_t [],wchar_t [], int );

void adicionaAlista(int , wchar_t [], wchar_t [], int , int );


//void geraSequencias (wchar_t[], int, wchar_t);

//void geraDuplasSequencias (wchar_t[], int, wchar_t);

#endif