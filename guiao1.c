#include <stdio.h>
#include <wchar.h>
#include <assert.h>
#include "guiao1.h"

void regista(wchar_t todosInputs[][MAX], int nlinhas) {
    int i;
    wchar_t buffer[MAX];

    for (i = 0; i < nlinhas; i++) {
        assert (fgetws (buffer, MAX, stdin) != NULL);
        assert (buffer[wcslen (buffer) - 1] == '\n');
        buffer [wcslen (buffer) - 1] = '\0';
        wcscpy (todosInputs[i], buffer);
    }
}

NAIPE naipe(wchar_t carta) {                    // calcula o naipe da carta, que coincide com o 2º dígito do
    return (((carta / 16) % 16) - 9);           // hexadecimal - 9 (1F0A1 -> A - 9 = 10 - 9 = 1)
}

VALOR valor(wchar_t carta) {                    // calcula o valor da carta, que coincide com o 1º dígito do hexadecimal
    return (carta % 16);
}

void converte(wchar_t hexadecimais[][MAX], CARTA convertidos[][MAX], int nlinhas) {
    for (int i = 0; i < nlinhas; i++) {
        int c;
        c = wcslen (hexadecimais[i]);

        for (int j = 0; j < c; j++) {
            convertidos[i][j].naipe = naipe(hexadecimais[i][j]);
            convertidos[i][j].valor = valor(hexadecimais[i][j]);
            convertidos[i][j].hex = hexadecimais[i][j];
        }
    }
}

void swap(CARTA jogada[], int pos1, int pos2) {
    CARTA temp = jogada[pos1];
    jogada[pos1] = jogada[pos2];
    jogada[pos2] = temp;
}

int maior (CARTA *carta1,CARTA *carta2){ // returna 1 se carta1 é maior que carta2
    assert(carta1->hex != carta2->hex);
    int r=0;
    if (carta1->valor > carta2->valor) r=1;
    else if (carta1->valor == carta2->valor) 
         {
            if (carta1->naipe > carta2->naipe) r=1;
         }
    return r;
}

int partition (CARTA jogada[], int tamanho, CARTA *pivo) { // , pivo- elemento mais direita , menores -> n de elementos menores que o pivo
    int menores = 0;
    int i;
    for (i = 0; i < tamanho; i++) {
        if (maior(pivo,&jogada[i])) {
            swap (jogada, i, menores);
            menores++;
        }
    }
    return menores;                
}                                                

void qsort (CARTA jogada[],int tamanho)
{
    if (tamanho > 1){
        int pos = partition(jogada,tamanho-1,&jogada[tamanho-1]);
        swap(jogada,pos,tamanho-1);
        qsort(jogada,pos);
        qsort(jogada+pos+1,tamanho-pos-1);
    }
}
/*void ordena(CARTA jogadas[][MAX],int i,int tamanho){
    qsort(jogadas[i],tamanho);
}*/

