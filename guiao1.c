#include <stdio.h>
#include <wchar.h>
#include <assert.h>
#include "guiao1.h"

void regista(wchar_t todosInputs[][MAX], int nlinhas) {     // lê linha a linha e regista 
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

void swapOLD(CARTA jogada[], int pos1, int pos2) {  // troca duas cartas de posição
    CARTA temp = jogada[pos1];
    jogada[pos1] = jogada[pos2];
    jogada[pos2] = temp;
}

int maiorOLD (CARTA *carta1,CARTA *carta2){     // retorna 1 se carta1 é maior que carta2
    assert(carta1->hex != carta2->hex);
    int r=0;
    if (carta1->valor > carta2->valor) r=1;
    else if (carta1->valor == carta2->valor) 
         {
            if (carta1->naipe > carta2->naipe) r=1;
         }
    return r;
}

int partitionOLD (CARTA jogada[], int tamanho, CARTA *pivo) { // pivo -> elemento mais direita , menores -> n de elementos menores que o pivo
    int menores = 0;
    int i;
    for (i = 0; i < tamanho; i++) {
        if (maiorOLD(pivo,&jogada[i])) {
            swapOLD (jogada, i, menores);
            menores++;
        }
    }
    return menores;                
}                                                

void qsortOLD (CARTA jogada[],int tamanho)
{
    if (tamanho > 1){
        int pos = partitionOLD(jogada,tamanho-1,&jogada[tamanho-1]);
        swapOLD(jogada,pos,tamanho-1);
        qsortOLD(jogada,pos);
        qsortOLD(jogada+pos+1,tamanho-pos-1);
    }
}

int valorIgual(CARTA *c1, CARTA *c2) { // ve se o valor é igual
int resultado=0;
  if (c1->valor == c2->valor) resultado= 1; // se o valor for igual dá 1
  return resultado;
}

/*int naipeIgual(CARTA c1, CARTA c2) {
  int resultado;
  if (c1.naipe == c2.naipe)
    resultado= 1; // se o valor for igual dá 1
  else
    resultado= 0;
  return resultado;
}*/

int verificaConjunto(CARTA linhaCartas[], int tamanho) { // return 1 se for conjunto
    int resultado = 1;
    for (int i = 0; i < tamanho - 1; i++) {
        if (!valorIgual(&linhaCartas[i], &linhaCartas[i + 1])) resultado= 0;
    }
    return resultado;
}

int verificaSequencia(CARTA linhaCartas[], int tamanhoLinha) { // verifica se é uma sequencia
    int resultado = 1;
    if (tamanhoLinha <=2) resultado=0;
    else for (int i = 0; i < tamanhoLinha - 1 && resultado; i++) {
         if (linhaCartas[i].valor + 1 != linhaCartas[i+1].valor ) resultado=0;
    }
    return resultado;
}

int verificaSequenciaDupla(CARTA linhaCartas[], int tamanhoLinha) {
    int resultado = 1;
    if(tamanhoLinha<6) resultado =0; 
    else for (int i = 0; i < tamanhoLinha - 1 && resultado; i++) {
        if (i%2==0) 
        {
            if(!valorIgual(&linhaCartas[i],&linhaCartas[i+1])) resultado=0;
        }
        else{
            if (linhaCartas[i].valor + 1 != linhaCartas[i+1].valor ) resultado=0;
        }
    }
    return resultado;
}

void resultado(CARTA linhaCartas[], int tamanho){
    if (verificaConjunto(linhaCartas,tamanho))
    {
       wprintf(L"conjunto com %d cartas onde a carta mais alta é %lc\n",tamanho,linhaCartas[tamanho-1].hex); 
    }
    else if (verificaSequencia(linhaCartas,tamanho))
    {
       wprintf(L"sequência com %d cartas onde a carta mais alta é %lc\n",tamanho,linhaCartas[tamanho-1].hex);
    }
    else if (verificaSequenciaDupla(linhaCartas,tamanho))
    {
       wprintf(L"dupla sequência com %d cartas onde a carta mais alta é %lc\n",tamanho/2,linhaCartas[tamanho-1].hex);
    }
    else wprintf(L"Nada!\n");
}
