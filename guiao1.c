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