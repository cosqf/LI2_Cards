#include <stdio.h>
#include <wchar.h>
#include <assert.h>
#include "guiao1.h"
#include "guiao2.h"
#include "guiao3.h"

void input (int ntestes, TESTEC inputs[]) {
    wchar_t buffer[MAX];

    for (int i = 0; i < ntestes; i++)
    {
        wscanf (L"%d\n", &(inputs[i].njogadas));
        
        assert (fgetws (buffer, MAX, stdin) != NULL);
        assert (buffer[wcslen (buffer) - 1] == '\n');
        buffer [wcslen (buffer) - 1] = '\0';
        wcscpy (inputs[i].mao, buffer);
        
        regista (inputs[i].jogadasAnts, inputs[i].njogadas);
        
        assert (fgetws (buffer, MAX, stdin) != NULL);
        assert (buffer[wcslen (buffer) - 1] == '\n');
        buffer [wcslen (buffer) - 1] = '\0';
        wcscpy (inputs[i].jogada, buffer);
    }
}