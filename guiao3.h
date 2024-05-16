#ifndef __GUIAO3_H__
#define __GUIAO3_H__

typedef struct testec {
    int njogadas;
    wchar_t mao[40];
    wchar_t jogadasAns[250][20];
    wchar_t jogada[20];
} TESTEC;

void registaC(wchar_t [][20], int );

void input (int, TESTEC[]);

void organizaJogadas(int ,TESTEC []);

int TresPasso (TESTEC *);

int jogadaPossivel (TESTEC *);

int verificaRei (TESTEC *);

int verificaReiAux (TESTEC *);

int jogadaValida(TESTEC *);

void retiraCartas(TESTEC *);

void output (int ,TESTEC []);

#endif