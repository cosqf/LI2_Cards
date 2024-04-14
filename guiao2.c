#include <stdio.h>
#include <wchar.h>
#include <assert.h>
#include "guiao1.h"
#include "guiao2.h"

// AQUI, TODAS AS QUE DIZEM "equivalente a..." MUDAM APENAS O TIPO (de CARTA para wchar_t)

void leInputs (int ntestes, TESTE inputs[]) {   // lê os inputs para um array 3d, usando como auxiliar a regista (que faz o registo para 2d)
    int nlinhas;
    
    for (int i = 0; i < ntestes; i++) {
        wscanf (L"%d\n", &nlinhas);
        regista (inputs[i].cartas, nlinhas);
        inputs[i].nlinhas = nlinhas;
    }
}

void registaTamanhos (int ntestes, TESTE inputs[]) {
    size_t tamanho;
    
    for (int i = 0; i < ntestes; i++) {
        tamanho = wcslen (inputs[i].cartas[0]);
        for (int j = 1; j < inputs[i].nlinhas && tamanho != 0; j++) {
            if (tamanho != wcslen (inputs[i].cartas[j])) tamanho = 0;
        }
        inputs[i].tamanho = tamanho;
    }
}



void ordenaTeste (TESTE *teste) {
    for (int i = 0; i < teste->nlinhas; i++) {
        qsort (teste->cartas[i], teste->tamanho);
    }
}

void ordena (int ntestes, TESTE teste[]) {
    for (int i = 0; i < ntestes; i++) {
        if (teste[i].tamanho != 0) {
            ordenaTeste (&teste[i]);
        }
    }
}