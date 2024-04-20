#ifndef __GUIAO3_H__
#define __GUIAO3_H__

typedef struct testec {
    int njogadas;
    wchar_t mao[MAX];
    wchar_t jogadasAnts[MAX][MAX];
    wchar_t jogada[MAX];
} TESTEC;

void input (int, TESTEC[]);

#endif