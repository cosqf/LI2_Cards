#include <stdio.h>
#include <wchar.h>
#include <assert.h>
#include "guiao1.h"
#include "guiao2.h"

// AQUI, TODAS AS QUE DIZEM "equivalente a..." MUDAM APENAS O TIPO (de CARTA para wchar_t)

void leInputs (int ntestes, TESTE inputs[MAX]) {   // lê os inputs para um array 3d, usando como auxiliar a regista (que faz o registo para 2d)
    int nlinhas;
    
    for (int i = 0; i < ntestes; i++) {
        wscanf (L"%d\n", &nlinhas);
        regista (inputs[i].cartas, nlinhas);
        inputs[i].nlinhas = nlinhas;
    }
}

void registaTamanhos (int ntestes, TESTE inputs[MAX]) {
    size_t tamanho;
    
    for (int i = 0; i < ntestes; i++) {
        tamanho = wcslen (inputs[i].cartas[0]);
        for (int j = 1; j < inputs[i].nlinhas && tamanho != 0; j++) {
            if (tamanho != wcslen (inputs[i].cartas[j])) tamanho = 0;
        }
        inputs[i].tamanho = tamanho;
    }
}

void swap(wchar_t jogada[], int pos1, int pos2) {   // troca duas cartas de posição; equivalente a swapOLD
    wchar_t temp = jogada[pos1];
    jogada[pos1] = jogada[pos2];
    jogada[pos2] = temp;
}

int maior (wchar_t carta1, wchar_t carta2){    // retorna 1 se carta1 é maior que carta2; equivalente a maiorOLD
    assert(carta1 != carta2);
    int r = 0;
    if (valor(carta1) > valor(carta2)) r = 1;
    else if (valor(carta1) == valor(carta2)) 
         {
            if (naipe(carta1) > naipe(carta2)) r=1;
         }
    return r;
}

int partition (wchar_t jogada[], int tamanho, wchar_t pivo) { // pivo -> elemento mais direita , menores -> n de elementos menores que o pivo; equivalente a partitionOLD
    int menores = 0;
    int i;
    for (i = 0; i < tamanho; i++) {
        if (maior(pivo, jogada[i])) {
            swap (jogada, i, menores);
            menores++;
        }
    }
    return menores;                
}

void qsort (wchar_t jogada[], int tamanho) {    // equivalente a qsortOLD
    if (tamanho > 1){
        int pos = partition(jogada,tamanho-1,jogada[tamanho-1]);
        swap(jogada,pos,tamanho-1);
        qsort(jogada,pos);
        qsort(jogada+pos+1,tamanho-pos-1);
    }
}

void ordenaTeste (TESTE *teste) {
    for (int i = 0; i < teste->nlinhas; i++) {
        qsort (teste->cartas[i], teste->tamanho);
    }
}

void ordena (int ntestes, TESTE teste[MAX]) {
    for (int i = 0; i < ntestes; i++) {
        if (teste[i].tamanho != 0) {
            ordenaTeste (&teste[i]);
        }
    }
}