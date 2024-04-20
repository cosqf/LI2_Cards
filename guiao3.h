#ifndef __GUIAO3_H__
#define __GUIAO3_H__

typedef struct testec {
    int njogadas;
    wchar_t mao[50];
    wchar_t jogadasAns[56][50];
    wchar_t jogada[50];
} TESTEC;

void input (int, TESTEC[]);

void organizaJogadas(int ,TESTEC []);

int TresPasso (TESTEC *);

int jogadaPossivel (TESTEC *);

int verificaRei (TESTEC *);

int jogadaValida(TESTEC *);

void retiraCartas(TESTEC *);

void output (int ,TESTEC []);

#endif