#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <assert.h>
#include "bot.h"
#include "guiao4.h"
#include "guiao3.h"
#include "guiao2.h"
#include "guiao1.h"


void inputD (TESTEC *input) {
    wchar_t buffer[MAX];

    wscanf (L"%d\n", &(input->njogadas));
        
    assert (fgetws (buffer, MAX, stdin) != NULL);
    assert (buffer[wcslen (buffer) - 1] == '\n');
    buffer [wcslen (buffer) - 1] = '\0';
    wcscpy (input->mao, buffer);
        
    registaC (input->jogadasAns, input->njogadas);
}

void geraReiD (wchar_t mao[], int size_ult, wchar_t maior_ult) {
    int r=0, r1=0, r2=0;
    if (size_ult == 1) {
        r1=geraConjuntosReisD(mao,size_ult,maior_ult);
        r2=geraConjuntosReisD(mao,4,0);
        r= r1 || r2;
        ///*debug*/wprintf (L"r1: %d, r2: %d, r: %d\n", r1, r2, r);
        geraDuplasSequenciasD(mao,6,0,r);
    }
    else if (size_ult==2) {
        r=geraConjuntosReisD(mao,size_ult,maior_ult);
        geraDuplasSequenciasD(mao,8,0,r);
    }
    else if (size_ult==3) {
        geraDuplasSequenciasD(mao,10,0,0);
    }
    else if (size_ult==4) {
        wprintf(L"PASSO\n");
    }
}

int  geraConjuntosReisD (wchar_t mao[], int size_ult, wchar_t maior_ult) {
    int r=0;
    int check = 1;
    int checkD = 0;
    wchar_t mao_usable[MAX_MAO] = {0};

    filtraConj (mao, size_ult, mao_usable);

    wchar_t combinacoes[MAX_MAO] = {0};
    int size_mao = wcslen(mao_usable);

    if (mao_usable[0] == '\0' || maior (maior_ult, mao_usable[size_mao-1]));
    else {
        combinaConjD (mao_usable, size_mao, size_ult, combinacoes, 0, maior_ult,&check,&checkD);
        r=1;
    }
    return r;
}


int geraConjuntosD  (wchar_t mao[], int size_ult, wchar_t maior_ult) {

    ///*debug*/wprintf (L"gera conjunto, Mao:%ls\n", mao);

    wchar_t mao_usable[MAX_MAO] = {0};
    int check = 0;
    int checkD = 0;
    filtraConj (mao, size_ult, mao_usable);
    ///*debug*/wprintf (L" conjunto, mao usable: %ls\n", mao_usable);

    wchar_t combinacoes[MAX_MAO] = {0};
    int size_mao = wcslen(mao_usable);

    if (mao_usable[0] == '\0' || maior (maior_ult, mao_usable[size_mao-1]));
    else combinaConjD (mao_usable, size_mao, size_ult, combinacoes, 0, maior_ult,&check, &checkD);
    return checkD;
}


int geraSequenciasD (wchar_t mao[], int size_ult, wchar_t maior_ult) {

    ///*debug*/wprintf (L"gera seq, Mao:%ls, size: %d, maior carta: %d\n", mao, size_ult, maior_ult);

    int check = 0;
    int checkD = 0;
    int size_mao = wcslen(mao);
    wchar_t mao_usable[MAX_MAO] = {0};

    filtraSeq (mao, size_ult, mao_usable, size_mao);
    ///*debug*/wprintf (L"seq, mao usable: %ls\n", mao_usable);

    wchar_t size_mao_usable = wcslen(mao_usable);
    wchar_t combinacoes[MAX_MAO] = {0};
    if (mao[0] == '\0' || maior (maior_ult, mao_usable[size_mao_usable-1]));
    else {
        combinaSeqD (mao_usable, size_mao_usable, size_ult, combinacoes, 0, maior_ult, &check, &checkD);
        if (!check){}; // a tirar um "passo" aqui
    }
    return checkD;
}

int geraDuplasSequenciasD (wchar_t mao[], int size_ult, wchar_t maior_ult, int r2) {

    ///*debug*/wprintf (L"gera dupla seq, Mao:%ls\n", mao)
    int check = 0;
    int checkD = 0;
    int size_mao = wcslen(mao);
    wchar_t mao_usable[MAX_MAO] = {0};

    filtraDupSeq ( mao, size_ult, mao_usable, size_mao);

    ///*debug*/wprintf (L" dupla seq, mao usable: %ls\n", mao_usable);

    wchar_t size_mao_usable = wcslen(mao_usable);
    wchar_t combinacoes[MAX_MAO] = {0};

    if ((mao_usable[0] == '\0' || maior (maior_ult, mao_usable[size_mao_usable-1])) && !r2 );  // r2 é igual a 1 se forem jogados reis antes de verificar as duplas sequencias
    else  {
        combinaDupSeqD (mao_usable, size_mao_usable, size_ult, combinacoes, 0, maior_ult, &check, &checkD);
        if (check==0 && !r2){};  // a tirar um "passo" aqui
    }
    return checkD;
}



void combinaConjD(wchar_t input[], int tamanho, int num, wchar_t combinacao[], int iter, wchar_t maior_ult, int *check,int *checkD) {
    if (!*checkD) {
        if (num == 0) {
            if (printConjD (combinacao, iter, maior_ult)) *checkD = 1;
        }
        else for (int i = 0; i < tamanho && ! *checkD; i++) {
            combinacao[iter] = input[i];
            combinaConjD (input + i + 1, tamanho - i - 1, num - 1, combinacao, iter + 1, maior_ult,check, checkD);
        }
    }
}

void combinaSeqD(wchar_t input[], int tamanho, int num, wchar_t combinacao[], int iter, wchar_t maior_ult, int *check, int *checkD) {
    if (!*checkD) {
        if (num == 0) {
            if (printSeqD (combinacao, iter, maior_ult)) *checkD = 1;
        }
        else for (int i = 0; i < tamanho && ! *checkD; i++) {
            combinacao[iter] = input[i];
            if (i+1 < tamanho && valor (input[i]) == valor (input[i+1]) ) combinaSeqD (input + i + 2, tamanho - i - 1, num - 1, combinacao, iter + 1, maior_ult,check,checkD);
            else combinaSeqD (input + i + 1, tamanho - i - 1, num - 1, combinacao, iter + 1, maior_ult, check, checkD);
        }
    }
}

void combinaDupSeqD(wchar_t input[], int tamanho, int num, wchar_t combinacao[], int iter, wchar_t maior_ult, int *check, int *checkD) {
    if (!*checkD) {
        if (num == 0) {
            if (printDupSeqD (combinacao, iter, maior_ult)) *checkD = 1;
        }
        else for (int i = 0; i < tamanho && ! *checkD; i++) {
            combinacao[iter] = input[i];

            combinaDupSeqD (input + i + 1, tamanho - i - 1, num - 1, combinacao, iter + 1, maior_ult, check, checkD);
            
        }
    }
}


int printConjD(wchar_t conj[], int iter, wchar_t maior_ult) {
    int i,r=0;
    if (maior (conj[iter-1], maior_ult) && verificaConjunto (conj, iter)) {
        for (i = 0; i < iter-1; i++) {
            wprintf(L"%lc ", conj[i]);
        }
        wprintf(L"%lc\n", conj[i]);
        r=1;
    }
    return r;
}

int printSeqD (wchar_t seq[], int iter, wchar_t maior_ult) {
    int i,r=0;
    if (maior (seq[iter-1], maior_ult) && verificaSequencia (seq, iter)) {
        for (i = 0; i < iter-1; i++) {
            wprintf(L"%lc ", seq[i]);
        }
        wprintf(L"%lc\n", seq[i]);
        r=1;
    }
    return r;
}

int printDupSeqD (wchar_t seq[], int iter, wchar_t maior_ult) {
    int i, r=0;
    if (maior (seq[iter-1], maior_ult) && verificaSequenciaDupla (seq, iter)) {
        for (i = 0; i < iter-1; i++) {
            wprintf(L"%lc ", seq[i]);
        }
        wprintf(L"%lc\n", seq[i]);
        r= 1;
    }
    return r;
}

void geraCombinacoesD (TESTED *teste) {
    int p = 0;
    COMBINACAO r = combinacaoUltima (teste->ultima);
    int size_ult = wcslen(teste->ultima);
    wchar_t maior = teste->ultima[size_ult-1];
    
    // reis
    if(valor(teste->ultima[0]) == Rei) geraReiD(teste->mao,size_ult,maior);
    else {
        if (r == Conjunto)  p = geraConjuntosD (teste->mao, size_ult, maior);
        else if (r == Sequencia) p = geraSequenciasD (teste->mao, size_ult, maior);
        else if (r == DuplaSequencia) p = geraDuplasSequenciasD (teste->mao, size_ult, maior,0);
        if (!p) wprintf (L"PASSO\n");
    }
}


void jogadaBOT (TESTEC *input) {
    int ind = TresPasso(input);
    ///*debug*/wprintf (L"Tres Passo: %d\n", ind);
    TESTED t;
    wcscpy(t.mao, input->mao);
    ///*debug*/ wprintf (L"Mao na main:\n");
    ///*debug*/ wprintf (L"%ls\n", t.mao);
    if (ind != -1) {
        wcscpy(t.ultima,input->jogadasAns[ind]);
        geraCombinacoesD(&t);
    }
    else {
        int r=0;
        for (int i = 14,j = 4; i>0 && !r;i--) {
            ///*debug*/wprintf (L"tamanho seq : %d, tamanho conj: %d\n", i, j);
            r = geraDuplasSequenciasD (t.mao, i, 0, 0);
            ///*debug*/ wprintf (L"dup seq r = %d\n", r);
            if (!r) r = geraSequenciasD (t.mao, i, 0);
            ///*debug*/ wprintf (L"seq r = %d\n", r);
            if (!r && i <= 4) r = (geraConjuntosD  (t.mao, j, 0));
            ///*debug*/ wprintf (L"conj r = %d\n", r);
            if (i<=4) j--;
        }
        if (!r) wprintf (L"PASSO\n");
    }
}