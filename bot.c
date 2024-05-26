#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <assert.h>
#include "bot.h"
#include "guiao4.h"
#include "guiao3.h"
#include "guiao2.h"
#include "guiao1.h"


void inputE (TESTEC *input) {
    wchar_t buffer[MAX];

    wscanf (L"%d\n", &(input->njogadas));
        
    assert (fgetws (buffer, MAX, stdin) != NULL);
    assert (buffer[wcslen (buffer) - 1] == '\n');
    buffer [wcslen (buffer) - 1] = '\0';
    wcscpy (input->mao, buffer);
        
    registaC (input->jogadasAns, input->njogadas);
}

void geraReiE (wchar_t mao[], int size_ult, wchar_t maior_ult) {
    int r=0, r1=0, r2=0;
    if (size_ult == 1) {
        r1 = geraConjuntosReis(mao, size_ult, maior_ult); // gera os reis maiores q o rei anterior
        r2 = geraConjuntosReis(mao,4,0); // gera conjuntos de reis de tamanho 4
        r = r1 || r2;
        geraDuplasSequencias(mao,6,0,r); // gera dup sequencias de tamanho 6 
    }
    else if (size_ult==2) {
        r=geraConjuntosReisE(mao,size_ult,maior_ult);
        geraDuplasSequenciasE(mao,8,0,r);
    }
    else if (size_ult==3) {
        geraDuplasSequenciasE(mao,10,0,0);
    }
    else if (size_ult==4) {
        wprintf(L"PASSO\n");
    }
}

int  geraConjuntosReisE (wchar_t mao[], int size_ult, wchar_t maior_ult) {
    int r=0;
    int check = 1;
    int checkE = 0;
    wchar_t mao_usable[MAX_MAO] = {0};

    filtraConj (mao, size_ult, mao_usable);

    wchar_t combinacoes[MAX_MAO] = {0};
    int size_mao = wcslen(mao_usable);

    if (mao_usable[0] == '\0' || maior (maior_ult, mao_usable[size_mao-1]));
    else {
        combinaConjE (mao_usable, size_mao, size_ult, combinacoes, 0, maior_ult, &check, &checkE);
        r = 1;
    }
    return r;
}


int geraConjuntosE  (wchar_t mao[], int size_ult, wchar_t maior_ult) {

    wchar_t mao_usable[MAX_MAO] = {0};
    int check = 0;
    int checkE = 0;
    filtraConj (mao, size_ult, mao_usable);

    wchar_t combinacoes[MAX_MAO] = {0};
    int size_mao = wcslen(mao_usable);

    if (mao_usable[0] == '\0' || maior (maior_ult, mao_usable[size_mao-1]));
    else combinaConjE (mao_usable, size_mao, size_ult, combinacoes, 0, maior_ult, &check, &checkE);
    return checkE;
}


int geraSequenciasE (wchar_t mao[], int size_ult, wchar_t maior_ult) {

    int check = 0;
    int checkE = 0;
    int size_mao = wcslen(mao);
    wchar_t mao_usable[MAX_MAO] = {0};

    filtraSeq (mao, size_ult, mao_usable, size_mao);

    wchar_t size_mao_usable = wcslen(mao_usable);
    wchar_t combinacoes[MAX_MAO] = {0};
    if (mao[0] == '\0' || maior (maior_ult, mao_usable[size_mao_usable-1]));
    else {
        combinaSeqE (mao_usable, size_mao_usable, size_ult, combinacoes, 0, maior_ult, &check, &checkE);
    }
    return checkE;
}

int geraDuplasSequenciasE (wchar_t mao[], int size_ult, wchar_t maior_ult, int r2) {
    int check = 0;
    int checkE = 0;
    int size_mao = wcslen(mao);
    wchar_t mao_usable[MAX_MAO] = {0};

    filtraDupSeq ( mao, size_ult, mao_usable, size_mao);

    wchar_t size_mao_usable = wcslen(mao_usable);
    wchar_t combinacoes[MAX_MAO] = {0};

    if ((mao_usable[0] == '\0' || maior (maior_ult, mao_usable[size_mao_usable-1])) && !r2 );  // r2 é igual a 1 se forem jogados reis antes de verificar as duplas sequencias
    else  {
        combinaDupSeqE (mao_usable, size_mao_usable, size_ult, combinacoes, 0, maior_ult, &check, &checkE);
    }
    return checkE;
}



void combinaConjE(wchar_t input[], int tamanho, int num, wchar_t combinacao[], int iter, wchar_t maior_ult, int *check,int *checkE) {
    if (!*checkE) {
        if (num == 0) {
            if (printConjE (combinacao, iter, maior_ult)) *checkE = 1;
        }
        else for (int i = 0; i < tamanho && ! *checkE; i++) {
            combinacao[iter] = input[i];
            combinaConjE (input + i + 1, tamanho - i - 1, num - 1, combinacao, iter + 1, maior_ult,check, checkE);
        }
    }
}

void combinaSeqE(wchar_t input[], int tamanho, int num, wchar_t combinacao[], int iter, wchar_t maior_ult, int *check, int *checkE) {
    if (!*checkE) {
        if (num == 0) {
            if (printSeqD (combinacao, iter, maior_ult)) *checkE = 1;
        }
        else for (int i = 0; i < tamanho && ! *checkE; i++) {
            combinacao[iter] = input[i];
            if (i+1 < tamanho && valor (input[i]) == valor (input[i+1]) ) combinaSeqE (input + i + 2, tamanho - i - 1, num - 1, combinacao, iter + 1, maior_ult,check,checkE);
            else combinaSeqE (input + i + 1, tamanho - i - 1, num - 1, combinacao, iter + 1, maior_ult, check, checkE);
        }
    }
}

void combinaDupSeqE(wchar_t input[], int tamanho, int num, wchar_t combinacao[], int iter, wchar_t maior_ult, int *check, int *checkE) {
    if (!*checkE) {
        if (num == 0) {
            if (printDupSeqE (combinacao, iter, maior_ult)) *checkE = 1;
        }
        else for (int i = 0; i < tamanho && ! *checkE; i++) {
            combinacao[iter] = input[i];

            combinaDupSeqE (input + i + 1, tamanho - i - 1, num - 1, combinacao, iter + 1, maior_ult, check, checkE);
            
        }
    }
}


int printConjE(wchar_t conj[], int iter, wchar_t maior_ult) {
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

int printDupSeqE (wchar_t seq[], int iter, wchar_t maior_ult) {
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

void geraCombinacoesE (TESTED *teste) {
    int p = 0;
    COMBINACAO r = combinacaoUltima (teste->ultima);
    int size_ult = wcslen(teste->ultima);
    wchar_t maior = teste->ultima[size_ult-1];
    
    // reis
    if(valor(teste->ultima[0]) == Rei) geraReiE(teste->mao,size_ult,maior);
    else {
        if (r == Conjunto)  p = geraConjuntosE (teste->mao, size_ult, maior);
        else if (r == Sequencia) p = geraSequenciasE (teste->mao, size_ult, maior);
        else if (r == DuplaSequencia) p = geraDuplasSequenciasE (teste->mao, size_ult, maior,0);
        if (!p) wprintf (L"PASSO\n");
    }
}


void jogadaBOT (TESTEC *input) {
    int ind = TresPasso(input);
    TESTED t;
    wcscpy(t.mao, input->mao);
   
    if (ind != -1) {
        wcscpy(t.ultima,input->jogadasAns[ind]);
        geraCombinacoesE(&t);
    }
    else {
        int r = 0; // check se printou
        for (int i = 14,j = 4; i>0 && !r ;i--) {
            r = geraDuplasSequenciasE (t.mao, i, 0, 0);
            if (!r) r = geraSequenciasE (t.mao, i, 0);
            if (!r && i <= 4) r = (geraConjuntosE  (t.mao, j, 0));
            if (i <= 4) j--;
        }
        if (!r) wprintf (L"PASSO\n");
    }
}