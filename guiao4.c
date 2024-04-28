#include <stdio.h>
#include <wchar.h>
#include <assert.h>
#include "guiao1.h"
#include "guiao2.h"
#include "guiao3.h"
#include "guiao4.h"

void getLinha (wchar_t linha[]){
    wchar_t buffer[BUFSIZ]; 
    
    assert (fgetws (buffer, BUFSIZ, stdin) != NULL);
    assert (buffer[wcslen (buffer) - 1] == '\n');
    buffer [wcslen (buffer) - 1] = '\0';
    wcscpy (linha, buffer);
}

void getTestes (TESTED inputs[], int ntestes) {
    for (int i = 0; i < ntestes; i++) {
        getLinha (inputs[i].ultima);
        getLinha (inputs[i].mao);

        qsort(inputs[i].ultima, wcslen(inputs[i].ultima));
        qsort(inputs[i].mao, wcslen(inputs[i].mao));
    }
}

COMBINACAO combinacaoUltima (wchar_t ultima[]) { 
    int tam = wcslen(ultima);
    COMBINACAO r = Nada; 
    if (verificaConjunto (ultima,tam)) r = Conjunto;
    else if (verificaSequencia (ultima, tam)) r = Sequencia;
    else if (verificaSequenciaDupla (ultima, tam)) r = DuplaSequencia;
    return r;   // r = 0 invalido
}

void geraCombinacoes (TESTED *teste) {      // PÔR AQUI OS CASOS DOS REIS
    COMBINACAO r = combinacaoUltima (teste->ultima);
    int size_ult = wcslen(teste->ultima);
    wchar_t maior = teste->ultima[size_ult-1];
    
    if (r == Conjunto) geraConjuntos (teste->mao, size_ult, maior);
    else if (r == Sequencia) geraSequencias (teste->mao, size_ult, maior);
    else if (r == DuplaSequencia) geraDuplasSequencias (teste->mao, size_ult, maior);
}

void geraConjuntos (wchar_t mao[], int size_ult, wchar_t maior_ult) {
    int i;
    for (i = 0; mao[i] && maior(maior_ult, mao[i]); i++);

    wchar_t mao_usable[wcslen(mao)-i];

    
}