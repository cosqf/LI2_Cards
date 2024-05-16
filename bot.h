#ifndef __BOT_H__
#define __BOT_H__

#include "guiao4.h"
#include "guiao3.h"

void inputD (TESTEC );

int geraConjuntosD  (wchar_t[], int, wchar_t);

int geraSequenciasD (wchar_t[], int, wchar_t);

int geraDuplasSequenciasD (wchar_t[], int, wchar_t, int);

void combinaConjD(wchar_t[], int, int, wchar_t[], int, wchar_t, int *,int *);

void combinaSeqD(wchar_t[], int, int, wchar_t[], int, wchar_t, int *, int *);

void combinaDupSeqD(wchar_t[], int, int, wchar_t[], int, wchar_t, int *, int *);

int printConjD(wchar_t[], int, wchar_t);

int printSeqD (wchar_t[], int, wchar_t);

int printDupSeqD (wchar_t[], int, wchar_t);

void geraCombinacoesD (TESTED *);

void jogadaBOT (TESTEC);

#endif