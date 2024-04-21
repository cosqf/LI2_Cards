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
        
        regista (inputs[i].jogadasAns, inputs[i].njogadas);
        
        assert (fgetws (buffer, MAX, stdin) != NULL);
        assert (buffer[wcslen (buffer) - 1] == '\n');
        buffer [wcslen (buffer) - 1] = '\0';
        wcscpy (inputs[i].jogada, buffer);
    }
}

void organizaJogadas(int ntestes,TESTEC inputs[])
{
    for(int i=0;i<ntestes;i++)
    {
        if(inputs[i].jogada[0] != 'P') qsort(inputs[i].jogada,wcslen(inputs[i].jogada));
    }   
}

int TresPasso (TESTEC *teste)
{
    int i,r=1;
    for ((i=(teste->njogadas) - 1); i > (teste->njogadas - 4) && r != 0;i--)
    {   
        if (teste->jogadasAns[i][0] != 'P') 
        {
            r=0;
            i++;
        }
    }
    if (r==1) i=0;  
    return i;  // devolve 0 se os ultimos 3 sao PASSO ou devolve a posicao da linha que nao foi PASSO;
}

int jogadaPossivel(TESTEC *teste)
{
    int r=1;
    int tamanho=wcslen(teste->jogada);  
    if (teste->jogada[0] != 'P')
    {
        for(int i=0;teste->jogada[i] && r!=0;i++)
        {
            if(wcschr(teste->mao,teste->jogada[i])==NULL) r=0;
        }
        if (verificaConjunto(teste->jogada,tamanho) == 0 && verificaSequencia(teste->jogada,tamanho) == 0 && verificaSequenciaDupla(teste->jogada,tamanho) == 0 && r==1) r=0; 
    } 
    return r;
}

int verificaRei (TESTEC *teste)
{
    int r=0;
    int linha = TresPasso(teste);
    int tamanho = wcslen(teste->jogada);
    int tamanhoAns = wcslen(teste->jogadasAns[linha]);
    if (valor(teste->jogadasAns[linha][0])==Rei && tamanhoAns == 1) 
    {
        if ((tamanho == 4 && verificaConjunto(teste->jogada,tamanho)) || (tamanho == 6 && verificaSequenciaDupla(teste->jogada,tamanho))) r=1;
    }
    else if (valor(teste->jogadasAns[linha][1])==Rei && valor(teste->jogadasAns[linha][0])==Rei && tamanhoAns == 2) 
    {
        if (tamanho == 8 && verificaSequenciaDupla(teste->jogada,tamanho)) r=1;
    }
    else if (valor(teste->jogadasAns[linha][1])==Rei && valor(teste->jogadasAns[linha][0])==Rei && valor(teste->jogadasAns[linha][2])==Rei && tamanhoAns == 3) 
    {
        if (tamanho == 10 && verificaSequenciaDupla(teste->jogada,tamanho)) r=1;
    }
    return r;
}

int jogadaValida(TESTEC *teste) {
    int r=0;
    int linha = TresPasso(teste); // caso n as ultimas 3 linhas n sejam Passo esta variavel e igual a posiçao da
                                  // linha que n foi PASSO
    size_t tamanho =wcslen(teste->jogada);
    if (teste->jogada[0] == 'P') r=1;
    if (jogadaPossivel(teste) && teste->njogadas==0) r=1;
    if (jogadaPossivel(teste) && r==0)
    {
        if(linha == 0) r=1;
        else if (valor(teste->jogadasAns[linha][0])==Rei) r=verificaRei(teste);

        else if (wcslen(teste->jogadasAns[linha]) == tamanho)
        {
            if ((verificaConjunto(teste->jogadasAns[linha],tamanho) && verificaConjunto(teste->jogada,tamanho)) || (verificaSequencia(teste->jogadasAns[linha],tamanho) && verificaSequencia(teste->jogada,tamanho)) || (verificaSequenciaDupla(teste->jogadasAns[linha],tamanho) && verificaSequenciaDupla(teste->jogada,tamanho)))
            {
                qsort(teste->jogadasAns[linha],tamanho);
                if (maior(teste->jogada[tamanho-1],teste->jogadasAns[linha][tamanho-1])) r=1;
            }    
        }
    } 
    return r;
}

void retiraCartas(TESTEC *teste)
{
    for (int i=0;teste->jogada[i];i++)
    {
        for (wchar_t *j=wcschr(teste->mao,teste->jogada[i]);*(j);j++)
        {
            *j = *(j+1);
        }
    }
}

void output (int ntestes,TESTEC inputs[])
{
    for (int i = 0; i < ntestes; i++) {             // ou, caso contrário, ordena as linhas e imprime-as
        wprintf (L"Teste %d\n", i+1);
        if (jogadaValida(&inputs[i]) && inputs[i].jogada[0]!= 'P') retiraCartas(&inputs[i]);
        if (inputs[i].mao[0] != '\0')
        {
            qsort(inputs[i].mao,wcslen(inputs[i].mao));
            size_t j=0;
            for(;j<wcslen(inputs[i].mao)-1 &&inputs[i].mao[0] != 0;j++)
            {
            wprintf(L"%lc ",inputs[i].mao[j]);
            }
            wprintf(L"%lc\n",inputs[i].mao[j]);
        }
        else wprintf(L"\n");
    }
}

