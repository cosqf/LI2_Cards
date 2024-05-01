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
    //else if (r == Sequencia) geraSequencias (teste->mao, size_ult, maior);
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
    //for (i = 0; mao[i] && maior(maior_ult, mao[i]); i++);

    //wchar_t mao_maiores[wcslen(mao)-i];
    //wcscpy(mao_maiores,mao+i);
    wchar_t mao_usable[MAX_MAO] = {0};

    filtraArray (mao, size_ult, mao_usable);

    wchar_t combinacoes[MAX_MAO] = {0};
    int size_mao = wcslen(mao_usable);
    if (mao_usable[0] == '\0' || maior (maior_ult, mao_usable[size_mao-1])) wprintf (L"PASSO\n");
    else {
        int size_mao = wcslen (mao_usable);
        iniciaALista(combinacoes);
        combina (mao_usable, size_mao, size_ult, combinacoes, 0, maior_ult);
    }
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

void iniciaALista (wchar_t mao[]){
    for (int i = 0; mao[i] != 0 ; i++){
        mao[i] = L'\0';
    }
}

void combina(wchar_t input[], int tamanho, int num, wchar_t combinacao[], int iter, wchar_t maior_ult) {
    if (num == 0) {
        printComb(combinacao, iter, maior_ult);
        return;
    }
    for (int i = 0; i < tamanho; i++) {
        combinacao[iter] = input[i];
        combina (input + i + 1, tamanho - i - 1, num - 1, combinacao, iter + 1, maior_ult);
    }
}

void printComb(wchar_t combinacao[], int iter, wchar_t maior_ult) {
    if (maior (combinacao[iter-1], maior_ult) && verificaConjunto (combinacao, iter)) {
        for (int i = 0; i < iter; i++) {
            wprintf(L"%lc ", combinacao[i]);
        }
        wprintf(L"\n");
    }
}

void printSeq (wchar_t seq[], int iter, wchar_t maior_ult) {
    if (maior (seq[iter-1], maior_ult) && verificaSequencia (seq, iter)) {
        for (int i = 0; i < iter; i++) {
            wprintf(L"%lc ", seq[i]);
        }
        wprintf(L"\n");
    }
}