#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <assert.h>
#include "guiao1.h"
#include "guiao2.h"
#include "guiao3.h"

int main () {
    setlocale (LC_CTYPE, "C.UTF-8");

    
    /*
    int nlinhas;                         // linhas de teste
    assert (wscanf (L"%d\n", &nlinhas) == 1);          // lê o nº de linhas de teste

    wchar_t todosInputs[nlinhas][MAX];    // guarda todas as linhas de teste

    regista (todosInputs, nlinhas);      // lê linha a linha e regista 

    
    for (int i = 0; i < nlinhas; i++) {
        int c;
        c = wcslen (todosInputs[i]);
        for (int j = 0; j < c; j++)
            wprintf (L"%lc", todosInputs[i][j]);
        wprintf (L"\n");
    }
    
    int c;
    for (int i = 0; i < nlinhas; i++) {
        c = wcslen (todosInputs[i]);
        qsort(todosInputs[i],c);
    }


    
    for (int i = 0; i < nlinhas; i++) {
        c = wcslen (todosInputs[i]);
        printResultado(todosInputs[i],c);
    }
    */


    /*
    int ntestes;                                                // nº de testes
    assert (wscanf (L"%d\n", &ntestes) == 1);                   // lê o nº de testes

    TESTE inputs[ntestes];

    leInputs (ntestes, inputs);

    registaTamanhos (ntestes, inputs);

    ordena (ntestes, inputs);

    printaOutput (ntestes, inputs);
    */


    int ntestes;                                                // nº de testes
    assert (wscanf (L"%d\n", &ntestes) == 1);                   // lê o nº de testes

    TESTEC inputs[ntestes];

    input (ntestes, inputs);

    organizaJogadas(ntestes,inputs);

    output(ntestes,inputs);

    return 0;
}