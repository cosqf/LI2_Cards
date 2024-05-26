#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <assert.h>
#include "bot.h"
#include "guiao1.h"
#include "guiao2.h"
#include "guiao3.h"
#include "guiao4.h"

int main () {
    setlocale (LC_CTYPE, "C.UTF-8");

    
/* Main guiao 1
    int nlinhas;                         // linhas de teste
    assert (wscanf (L"%d\n", &nlinhas) == 1);          // lê o nº de linhas de teste

    wchar_t todosInputs[nlinhas][MAX];    // guarda todas as linhas de teste

    regista (todosInputs, nlinhas);      // lê linha a linha e regista 

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

/* Main guiao 2
    int ntestes;                                                // nº de testes
    assert (wscanf (L"%d\n", &ntestes) == 1);                   // lê o nº de testes

    TESTE inputs[ntestes];

    leInputs (ntestes, inputs);

    registaTamanhos (ntestes, inputs);

    ordena (ntestes, inputs);

    printaOutput (ntestes, inputs);
    
*/
    
/*  Main guiao 3
    int ntestes;                                                // nº de testes
    assert (wscanf (L"%d\n", &ntestes) == 1);                   // lê o nº de testes

    TESTEC inputs[ntestes];

    input (ntestes, inputs);

    organizaJogadas(ntestes,inputs);

    output(ntestes,inputs);

*/

/*  Main guiao 4
    int ntestes;
    assert (wscanf (L"%d\n", &ntestes) == 1);

    TESTED inputs[ntestes];

    getTestes (inputs, ntestes);
    
    for (int i=0;i<ntestes;i++)
    {
        wprintf (L"Teste %d\n", i+1);
        geraCombinacoes(&inputs[i]);
    }
*/
    
//  Main bot

    TESTEC input;

    inputD (&input);

    jogadaBOT (&input);

    return 0;
}