/*
Programa: cenario.h
Objetivos: Arquivo de interface do TAD Cenario
            - orquestrar o estado geral (mapa, entidades, pontuacao, eventos).
            - gerenciar loops, colisoes, entradas, vitorias/derrotas.
            - salvar e carregar cenario do jogo
Entrada/Saida:
Autores:TF9-João Gabriel Poester Oliveira da Costa;
           -Leonardo Moreira Leon;
           -Sergio Artur Luz Wagner.
Data:21/06/2025
*/

#ifndef CENARIO_H_INCLUDED
#define CENARIO_H_INCLUDED

#include "filaG.h"                                                              //interface do TAD FilaG
#include "grafo.h"                                                              //interface do TAD Grafo
#include "listaG.h"                                                             //interface do TAD ListaG
#include "mapa.h"                                                               //interface do TAD Mapa
#include "entidade.h"                                                           //interface do TAD Entidade

typedef struct{                                                                 //definicao da struct Cenario
    int vidas;                                                                  //numero de vidas do Pac-Man
    int pontos;                                                                 //pontuacao do jogador
    int imortal;                                                                //contador regressivo da duracao da imortalidade do Pac-Man apos consumir uma pastilha de imortalidade
    int dimEntes;                                                               //dimensao atual do vetor de ponteiros para entidades do cenario
    int nEntes;                                                                 //quantidade de ponteiros de Entidades no vetor da struct Cenario
    char mov;                                                                   //intensao de movimentacao(w,a,s ou d) do Pac-Man
    int chaveF;                                                                 //chave do fantasma F no vetor de entidades
    int chaveG;                                                                 //chave do fantasma G no vetor de entidades
    int chaveH;                                                                 //chave do fantasma H no vetor de entidades
    int chaveJ;                                                                 //chave do fantasma J no vetor de entidades
    int chaveP;                                                                 //chave do Pac-Man no vetor de entidades
    Mapa* mapa;                                                                 //ponteiro para uma struct Mapa
    Entidade** entes;                                                           //ponteiro para vetor de ponteiros para Entidade
    FilaG* fantasmas;                                                           //ponteiro para fila dos fantasmas, que estao fora do mapa, ingressarem no mapa
    Grafo* grafo;                                                               //ponteiro para uma struct Grafo gerada com o numero de vertices igual ao numero de celulas do mapa(linhas x colunas)
}Cenario;

//Funcao que recebe um arquivo de struct Mapa e retorna um ponteiro para uma struct Cenario dinamicamente alocada gerada a partir desse arquivo
Cenario* cenario_cria(const char* arqMapa);

//Funcao que desaloca uma struct Cenario dinamicamente alocada
void cenario_destroi(Cenario* cena);

//Funcao que salva uma struct Cenario em arquivo
int cenario_salva(Cenario* cena, const char* nomeArq);

//Funcao que carrega uma struct Cenario a partir de um arquivo
Cenario* cenario_carrega(const char* nomeArq);

//Ataque
int* cenario_F_ataca(Cenario* cena; int* tam);
int* cenario_G_ataca(Cenario* cena; int* tam);
int* cenario_H_ataca(Cenario* cena; int* tam);
int* cenario_J_ataca(Cenario* cena; int* tam);

/*/Fuga


//Funcoes de movimentacao do Pac-Man
.
.
.

//Funcao detectar colisao com Pac-Man

*/
#endif // CENARIO_H_INCLUDED
