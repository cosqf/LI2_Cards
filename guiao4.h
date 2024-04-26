#ifndef __GUIAO4_H__
#define __GUIAO4_H__

#define MAX_MAO 56  // 55 cartas possíveis no máximo + 1 posição para o '\0'
#define MAX_ULT 29  // 28 cartas possíveis para a combinação mais longa (dupla sequência do ás ao rei) + 1 para o '\0'

typedef struct tested {
    wchar_t ultima[MAX_ULT];
    wchar_t mao[MAX_MAO];
} TESTED;

void getLinha (wchar_t[]);

void getTestes (TESTED[], int);

#endif