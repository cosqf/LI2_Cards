#include <stdio.h>
#include <wchar.h>
#include <assert.h>
#include "guiao1.h"
#include "guiao2.h"

void leInputs (int ntestes, TESTE inputs[]) {   // constrói o array de TESTEs, guardando o nº de linhas
    int nlinhas;                                // e o array correspondente (usando a regista do guião 1) em cada struct
    
    for (int i = 0; i < ntestes; i++) {
        wscanf (L"%d\n", &nlinhas);
        regista (inputs[i].cartas, nlinhas);
        inputs[i].nlinhas = nlinhas;
    }
}

void registaTamanhos (int ntestes, TESTE inputs[]) {    // regista os tamanhos para cada struct; se este é 0,
    size_t tamanho;                                     // as combinações nessa struct não são do mesmo tipo;
                                                        // caso contrário, este tamanho corresponde ao nº de cartas de cada jogada (é o mesmo)
    for (int i = 0; i < ntestes; i++) {
        tamanho = wcslen (inputs[i].cartas[0]);
        for (int j = 1; j < inputs[i].nlinhas && tamanho != 0; j++) {
            if (tamanho != wcslen (inputs[i].cartas[j])) tamanho = 0;
        }
        inputs[i].tamanho = tamanho;
    }
}

void ordenaTeste (TESTE *teste) {   // ordena todas as jogadas (linhas) numa struct; AS JOGADAS NÃO FICAM ORDENADAS ENTRE SI (por combinação mais forte)
    for (int i = 0; i < teste->nlinhas; i++) {
        qsort (teste->cartas[i], teste->tamanho);
    }
}

void ordena (int ntestes, TESTE teste[]) {      // ordena os arrays do array principal; só chama a ordenaTeste se
    for (int i = 0; i < ntestes; i++) {         // as combinações forem do mesmo tipo, i.e., tamanho diferente de 0
        if (teste[i].tamanho != 0) {
            ordenaTeste (&teste[i]);
        }
    }
}

int todasConjunto (TESTE *teste){   // verifica se todas as linhas de um teste são do tipo conjunto
    int r = 1;
    for (int i = 0; i < teste->nlinhas && r != 0; i++) {
        if (verificaConjunto(teste->cartas[i], teste->tamanho) == 0) r = 0;  
    }
    return r;
}


int todasSequencia (TESTE *teste){  // verifica se todas as linhas de um teste são do tipo sequência
    int r = 1;
    for (int i = 0; i < teste->nlinhas && r != 0; i++) {
        if (verificaSequencia(teste->cartas[i], teste->tamanho) == 0) r = 0;  
    }
    return r;
}


int todasSequenciaDupla (TESTE *teste){     // verifica se todas as linhas de um teste são do tipo sequencia dupla
    int r = 1;
    for (int i = 0; i < teste->nlinhas && r != 0; i++) {
        if (verificaSequenciaDupla(teste->cartas[i], teste->tamanho) == 0) r = 0;  
    }
    return r;
}

int testeValido (TESTE *teste) {    // verifica se um teste tem todas as linhas do mesmo tipo
    int r = 0;
    if (todasConjunto (teste) || todasSequencia (teste) || todasSequenciaDupla (teste)) r = 1;
    return r;
}

void swapArray (wchar_t cartas[][MAX], int pos1, int pos2) {   // troca dois arrays de posição
    int c = wcslen (cartas[0]);
    wchar_t temp[MAX];
    wcsncpy (temp, cartas[pos1], c);
    wcsncpy (cartas[pos1], cartas[pos2], c);
    wcsncpy (cartas[pos2], temp, c);
}

int maiorArray (wchar_t jogada1[], wchar_t jogada2[]){    // compara dois arrays ordenados, comparando apenas a última carta
    int c = wcslen (jogada1);
    wchar_t carta1 = jogada1[c-1];
    wchar_t carta2 = jogada2[c-1];
    
    /*
    assert (carta1 != carta2);
    int r = 0;
    
    if (valor(carta1) > valor(carta2)) r = 1;
    else if (valor(carta1) == valor(carta2)) {
            if (naipe(carta1) > naipe(carta2)) r = 1;
         }
    return r;
    */
    
    return maior (carta1, carta2);
}

int partitionArray (wchar_t cartas[][MAX], int nlinhas, wchar_t pivo[]) {   // pivo -> elemento mais direita, menores -> n de elementos menores que o pivo
    int menores = 0;
    int i;
    for (i = 0; i < nlinhas; i++) {
        if (maiorArray(pivo, cartas[i])) {
            swapArray (cartas, i, menores);
            menores++;
        }
    }
    return menores;                
}


void qsortArray (wchar_t cartas[][MAX], int nlinhas) {
    if (nlinhas > 1){
        int pos = partitionArray(cartas, nlinhas-1, cartas[nlinhas-1]);
        swapArray(cartas, pos, nlinhas-1);
        qsortArray(cartas,pos);
        qsortArray(cartas+pos+1, nlinhas-pos-1);
    }
}

void printaTeste (TESTE *teste) {   // imprime as linhas de um teste (não usa wprintf (L"%ls", teste->cartas[i]) por causa dos espaços)
    int i;
    size_t j;
    
    for (i = 0; i < teste->nlinhas; i++) {
        for (j = 0; j < teste->tamanho-1; j++) {
            wprintf (L"%lc ", teste->cartas[i][j]);
        }
        wprintf (L"%lc\n", teste->cartas[i][j]);
    }
}

void printaOutput (int ntestes, TESTE inputs[]) {   // imprime o output, verificando se o tamanho é 0 (comb ñ iguais)
    for (int i = 0; i < ntestes; i++) {             // ou, caso contrário, ordena as linhas e imprime-as
        wprintf (L"Teste %d\n", i+1);
        if (inputs[i].tamanho == 0 || !(testeValido(&inputs[i]))) wprintf (L"Combinações não iguais!\n");
        else {
            qsortArray (inputs[i].cartas, inputs[i].nlinhas);
            printaTeste (&inputs[i]);
        }
    }
}