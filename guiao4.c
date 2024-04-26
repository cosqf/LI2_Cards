#include <stdio.h>
#include <wchar.h>
#include <assert.h>
#include "guiao1.h"
#include "guiao2.h"
#include "guiao3.h"
#include "guiao4.h"

void getLinha (wchar_t linha[]){
    wchar_t buffer[BUFSIZ]; 
    
    assert (fgetws (buffer, BUFSIZ, stdin) != NULL);
    assert (buffer[wcslen (buffer) - 1] == '\n');
    buffer [wcslen (buffer) - 1] = '\0';
    wcscpy (linha, buffer);
}

void getTestes (TESTED inputs[], int ntestes) {
    for (int i = 0; i < ntestes; i++) {
        getLinha (inputs[i].ultima);
        getLinha (inputs[i].mao);
    }
}