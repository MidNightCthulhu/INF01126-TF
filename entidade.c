/*
Programa: entidade.c
Objetivos: Arquivo de implementacao do TAD Entidade
            -Representar as entidades dinâmicas efemeras, em contraste com o perene mapa, do jogo: Pac-Man, Fantasmas, pastilhas normais e pastilhas de imortalidade
Entrada/Saida:
Autores:TF9-João Gabriel Poester Oliveira da Costa;
           -Leonardo Moreira Leon;
           -Sergio Artur Luz Wagner.
Data:12/06/2025
*/

#include <stdio.h>
#include <stdlib.h>

#include "entidade.h"

//Funcao que retorna um ponteiro para uma struct Ente dinamicamente alocada
Entidade* entidade_cria(char tipo, int chave, int cel, int x, int y){
    Entidade* ente = (Entidade*) malloc(sizeof(Entidade));
    if(ente){
        ente->chave = chave;
        ente->cel = cel;
        ente->x = x;
        ente->y = y;
        ente->noMapa = 1;
        switch(tipo){
            case '.':
                ente->tipo = '.';
                ente->imortal = -1;
                ente->tregua = -1;
                break;
            case 'o':
                ente->tipo = 'o';
                ente->imortal = -1;
                ente->tregua = -1;
                break;
            case 'P':
                ente->tipo = 'P';
                ente->imortal = 0;
                ente->tregua = -1;
                break;
            case 'F':
                ente->tipo = 'F';
                ente->imortal = -1;
                ente->tregua = 10;
                break;
            case 'G':
                ente->tipo = 'G';
                ente->imortal = -1;
                ente->tregua = 10;
                break;
            case 'H':
                ente->tipo = 'H';
                ente->imortal = -1;
                ente->tregua = 10;
                break;
            case 'J':
                ente->tipo = 'J';
                ente->imortal = -1;
                ente->tregua = 10;
                break;
        }
    }
    return ente;
}

//Funcao que desaloca uma struct Ente dinamicamente alocada
void entidade_destroi(Entidade* ente){
    if(ente)
        free(ente);
}
