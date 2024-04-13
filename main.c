#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <assert.h>
#include "guiao1.h"
#include "guiao2.h"

int main () {
    /*
    setlocale (LC_CTYPE, "C.UTF-8");

    int nlinhas;                         // linhas de teste
    assert (wscanf (L"%d\n", &nlinhas) == 1);          // lê o nº de linhas de teste

    wchar_t todosInputs[nlinhas][MAX];    // guarda todas as linhas de teste

    regista (todosInputs, nlinhas);      // lê linha a linha e regista 

    /
    for (int i = 0; i < nlinhas; i++) {
        int c;
        c = wcslen (todosInputs[i]);
        for (int j = 0; j < c; j++)
            wprintf (L"%lc", todosInputs[i][j]);
        wprintf (L"\n");
    }
    /

    CARTA inputsConvertidos[nlinhas][MAX];          // guarda os inputs no formato CARTA (naipe, valor e hexadecimal)
    int c;
    converte (todosInputs, inputsConvertidos, nlinhas);     // converte os hexadecimais em todosInputs para o formato CARTA (inputsConvertidos)
    
    
    for (int i = 0; i < nlinhas; i++) {
        c = wcslen (todosInputs[i]);
        qsortOLD(inputsConvertidos[i],c);
    }


    
    for (int i = 0; i < nlinhas; i++) {
        c = wcslen (todosInputs[i]);
        //for (int j = 0; j < c; j++) {
            // wprintf (L"%d %d %lc       ", inputsConvertidos[i][j].naipe, inputsConvertidos[i][j].valor, inputsConvertidos[i][j].hex);
        //}
        //wprintf (L"A maior carta %lc       ",inputsConvertidos[i][c-1].hex);
        resultado(inputsConvertidos[i],c);
    }
    */

    setlocale (LC_CTYPE, "C.UTF-8");

    int ntestes;                                                // nº de testes
    assert (wscanf (L"%d\n", &ntestes) == 1);                   // lê o nº de testes

    TESTE inputs[MAX];

    leInputs (ntestes, inputs);

    registaTamanhos (ntestes, inputs);

    ordena (inputs, ntestes);

    return 0;
}