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
    
    // reis
    if(valor(teste->ultima[0]) == Rei) geraRei(teste->mao,size_ult,maior);


    else if (r == Conjunto)  geraConjuntos (teste->mao, size_ult, maior);
    else if (r == Sequencia) geraSequencias (teste->mao, size_ult, maior);
    else if (r == DuplaSequencia) geraDuplasSequencias (teste->mao, size_ult, maior,0);
}

void geraRei (wchar_t mao[], int size_ult, wchar_t maior_ult) {
    int r=0, r1=0, r2=0;
    if (size_ult == 1) {
        r1=geraConjuntosReis(mao,size_ult,maior_ult);
        r2=geraConjuntosReis(mao,4,0);
        r= r1 || r2;
        geraDuplasSequencias(mao,6,0,r);
    }
    else if (size_ult==2) {
        r=geraConjuntosReis(mao,size_ult,maior_ult);
        geraDuplasSequencias(mao,8,0,r);
    }
    else if (size_ult==3) {
        geraDuplasSequencias(mao,10,0,0);
    }
    else if (size_ult==4) {
        wprintf(L"PASSO\n");
    }
}

int  geraConjuntosReis (wchar_t mao[], int size_ult, wchar_t maior_ult) {
    int r=0;
    int check = 1;
    wchar_t mao_usable[MAX_MAO] = {0};

    filtraArray (mao, size_ult, mao_usable);

    wchar_t combinacoes[MAX_MAO] = {0};
    int size_mao = wcslen(mao_usable);

    if (mao_usable[0] == '\0' || maior (maior_ult, mao_usable[size_mao-1]));
    else {
        combina (mao_usable, size_mao, size_ult, combinacoes, 0, maior_ult, Conjunto,&check);
        r=1;
    }
    return r;
}

void geraConjuntos  (wchar_t mao[], int size_ult, wchar_t maior_ult) {
    wchar_t mao_usable[MAX_MAO] = {0};
    int check = 0;
    filtraArray (mao, size_ult, mao_usable);

    wchar_t combinacoes[MAX_MAO] = {0};
    int size_mao = wcslen(mao_usable);

    if (mao_usable[0] == '\0' || maior (maior_ult, mao_usable[size_mao-1])) wprintf (L"PASSO\n");
    else combina (mao_usable, size_mao, size_ult, combinacoes, 0, maior_ult, Conjunto,&check);
}


void geraSequencias (wchar_t mao[], int size_ult, wchar_t maior_ult) {
    int check = 0;
    wchar_t combinacoes[MAX_MAO] = {0};
    int size_mao = wcslen(mao);
    if (mao[0] == '\0' || maior (maior_ult, mao[size_mao-1])) wprintf (L"PASSO\n");
    else {
        combina (mao, size_mao, size_ult, combinacoes, 0, maior_ult, Sequencia,&check);
        if (!check) wprintf (L"PASSO\n");
    }
}

void geraDuplasSequencias (wchar_t mao[], int size_ult, wchar_t maior_ult, int r2) {

    int check = 0;
    wchar_t combinacoes[MAX_MAO] = {0};
    int size_mao = wcslen(mao);
    if ((mao[0] == '\0' || maior (maior_ult, mao[size_mao-1])) && !r2 ) wprintf (L"PASSO\n");  // r2 é igual a 1 se forem jogados reis antes de verificar as duplas sequencias
    else  {
        combina (mao, size_mao, size_ult, combinacoes, 0, maior_ult, DuplaSequencia,&check);
        if (check==0 && !r2) wprintf (L"PASSO\n");
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

void combina(wchar_t input[], int tamanho, int num, wchar_t combinacao[], int iter, wchar_t maior_ult, COMBINACAO c, int *check) {
    if (num == 0) {
        if (c == Conjunto) printConj (combinacao, iter, maior_ult);
        else if (c == Sequencia) printSeq (combinacao, iter, maior_ult, check);
        else if (c == DuplaSequencia) printDupSeq (combinacao, iter, maior_ult, check);
    }
    for (int i = 0; i < tamanho; i++) {
        combinacao[iter] = input[i];
        combina (input + i + 1, tamanho - i - 1, num - 1, combinacao, iter + 1, maior_ult, c,check);
    }
}

void printConj(wchar_t conj[], int iter, wchar_t maior_ult) {
    int i;
    if (maior (conj[iter-1], maior_ult) && verificaConjunto (conj, iter)) {
        for (i = 0; i < iter-1; i++) {
            wprintf(L"%lc ", conj[i]);
        }
        wprintf(L"%lc\n", conj[i]);
    }
}

void printSeq (wchar_t seq[], int iter, wchar_t maior_ult,int *check) {
    int i;
    if (maior (seq[iter-1], maior_ult) && verificaSequencia (seq, iter)) {
        for (i = 0; i < iter-1; i++) {
            wprintf(L"%lc ", seq[i]);
        }
        wprintf(L"%lc\n", seq[i]);
        (*check)=1;

    }
}

void printDupSeq (wchar_t seq[], int iter, wchar_t maior_ult,int *check) {
    int i;
    if (maior (seq[iter-1], maior_ult) && verificaSequenciaDupla (seq, iter)) {
        for (i = 0; i < iter-1; i++) {
            wprintf(L"%lc ", seq[i]);
        }
        wprintf(L"%lc\n", seq[i]);
        (*check)=1;
    }
}
