#ifndef __BOT_H__
#define __BOT_H__

#include "guiao4.h"
#include "guiao3.h"

void inputE (TESTEC *);

void geraReiE (wchar_t [], int , wchar_t );

int  geraConjuntosReisE (wchar_t [], int , wchar_t) ;

int geraConjuntosE  (wchar_t[], int, wchar_t);

int geraSequenciasE (wchar_t[], int, wchar_t);

int geraDuplasSequenciasE (wchar_t[], int, wchar_t, int);

void combinaConjE (wchar_t[], int, int, wchar_t[], int, wchar_t, int *,int *);

void combinaSeqE (wchar_t[], int, int, wchar_t[], int, wchar_t, int *, int *);

void combinaDupSeqE (wchar_t[], int, int, wchar_t[], int, wchar_t, int *, int *);

int printConjE (wchar_t[], int, wchar_t);

int printSeqE (wchar_t[], int, wchar_t);

int printDupSeqE (wchar_t[], int, wchar_t);

void geraCombinacoesE (TESTED *);

void jogadaBOT (TESTEC *);

#endif