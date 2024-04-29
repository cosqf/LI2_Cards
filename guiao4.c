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
    
    if (r == Conjunto)  geraConjuntos (teste->mao, size_ult, maior);
    // else if (r == Sequencia) geraSequencias (teste->mao, size_ult, maior);
    // else if (r == DuplaSequencia) geraDuplasSequencias (teste->mao, size_ult, maior);
}

/*
int frequencia (wchar_t mao[]){
    int freq=1;
        for (size_t j =0;j<wcslen(mao)-1;j++) {
        if(valor(mao[j]) ==valor(mao[j+1])) freq++; 
    }
    return freq;
}

void filtraArray (wchar_t mao_maiores[], int size_ult, wchar_t mao_usable[]){

    int i;
    for (i = 0; mao_maiores[i]; i++) {
        if ()
    }

    for (size_t j =0 ;j<wcslen(mao_maiores);) // n tenho certeza se tenho que por -1
    {
        int freq = frequencia(mao_maiores+j);
        if (freq >= size_ult) {
            wcsncpy(mao_usable,mao_maiores+j,freq);
        }
        j=j+freq;
    }
}

*/

void geraConjuntos  (wchar_t mao[], int size_ult, wchar_t maior_ult) {
    int i;
    for (i = 0; mao[i] && maior(maior_ult, mao[i]); i++);

    wchar_t mao_maiores[wcslen(mao)-i];
    wcscpy(mao_maiores,mao+i);
    wchar_t mao_usable[MAX_MAO] = {0};

    filtraArray (mao_maiores, size_ult, mao_usable);

    wchar_t jogadasPossiveis[MAX_MAO] = {0};
    if (mao_usable[0] == '\0') printf ("PASSO\n");
    else iniciaALista(jogadasPossiveis, mao_usable, size_ult);

}

int frequencia (wchar_t mao[], wchar_t carta) {
    int i, freq = 0;
    for (i=0; mao[i]; i++) {
        if (valor (mao[i]) == valor (carta)) freq++;
    }
    return freq;
}

void filtraArray (wchar_t mao_maiores[], int size_ult, wchar_t mao_usable[]){
    int i,j;
    for (i = 0, j = 0; mao_maiores[i]; i++) {
        int freq = frequencia (mao_maiores, mao_maiores[i]);
        if (freq >= size_ult) {
            mao_usable[j] = mao_maiores[i];
            j++;
        }
    }
}

void iniciaALista (wchar_t jogada[], wchar_t mao[], int tamanho){
    for (int i = 0; mao[i] != 0 ; i++){
        jogada[0] = mao[i];
        adicionaAlista (1,jogada,mao,i,tamanho);
    }
}

void adicionaAlista(int i, wchar_t jogada[], wchar_t mao[], int ant, int tamanho){
    if (i == tamanho) printaComb (jogada);
    else
    for (int j = ant+1 ; valor (jogada[0]) == valor (mao[j]);j ++){
        jogada[i] = mao[j];
        i++;
        adicionaAlista(i,jogada,mao,j,tamanho);
    }
}

void printaComb (wchar_t comb[]) {
    int i;
    for (i = 0; comb[i] != '\0'; i++) {
        wprintf (L"%lc ", comb[i]);
    }
    wprintf (L"\n");
}