#include <stdio.h>
#include <wchar.h>
#include <assert.h>
#include "guiao1New.h"



NAIPE naipe(wchar_t carta) {                    // calcula o naipe da carta, que coincide com o 2º dígito do
    return (((carta / 16) % 16) - 9);           // hexadecimal - 9 (1F0A1 -> A - 9 = 10 - 9 = 1)
}

VALOR valor(wchar_t carta) {                    // calcula o valor da carta, que coincide com o 1º dígito do hexadecimal
    return (carta % 16);
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



int valorIgual(wchar_t c1, wchar_t c2) { // ve se o valor é igual
int resultado=0;
  if (valor(c1) == valor(c2)) resultado= 1; // se o valor for igual dá 1
  return resultado;
}

int verificaConjunto(wchar_t linhaCartas[], int tamanho) { // return 1 se for conjunto
    int resultado = 1;
    for (int i = 0; i < tamanho - 1; i++) {
        if (!valorIgual(linhaCartas[i], linhaCartas[i + 1])) resultado= 0;
    }
    return resultado;
}

int verificaSequencia(wchar_t linhaCartas[], int tamanhoLinha) { // verifica se é uma sequencia
    int resultado = 1;
    if (tamanhoLinha <=2) resultado=0;
    else for (int i = 0; i < tamanhoLinha - 1 && resultado; i++) {
         if (valor(linhaCartas[i]) + 1 != valor(linhaCartas[i+1]) ) resultado=0;
    }
    return resultado;
}

int verificaSequenciaDupla(wchar_t linhaCartas[], int tamanhoLinha) {
    int resultado = 1;
    if(tamanhoLinha<6) resultado =0; 
    else for (int i = 0; i < tamanhoLinha - 1 && resultado; i++) {
        if (i%2==0) 
        {
            if(!valorIgual(linhaCartas[i],linhaCartas[i+1])) resultado=0;
        }
        else{
            if (valor(linhaCartas[i]) + 1 != valor(linhaCartas[i+1]) ) resultado=0;
        }
    }
    return resultado;
}
