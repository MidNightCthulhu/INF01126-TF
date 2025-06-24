/*
Programa: entidade.h
Objetivos: Arquivo de interface do TAD Entidade
            -Representar as entidades dinâmicas efemeras, em contraste com o perene mapa, do jogo: Pac-Man, Fantasmas, pastilhas normais e pastilhas de imortalidade
Entrada/Saida:
Autores:TF9-João Gabriel Poester Oliveira da Costa;
           -Leonardo Moreira Leon;
           -Sergio Artur Luz Wagner.
Data:12/06/2025
*/

#ifndef ENTIDADE_H_INCLUDED
#define ENTIDADE_H_INCLUDED

typedef struct{                                                             //definicao da struct Entidade
    char tipo;                                                              //identificacao do ente se Pac-Man(P), Fantasma(F,G,H ou J), pastilha normal(.) ou pastilha de imortalidade(o)
    int chave;                                                              //identificacao unica do ente na lista de entidades do TAD Cena
    int imortal;                                                            //contador regressivo da duracao da imortalidade do Pac-Man apos consumir uma pastilha de imortalidade
    int tregua;                                                             //contador regressivo da tregua antes do Fantasma atacar o Pac-Man
    int noMapa;                                                             //indicador da presenca do Ente no mapa
    int cel;                                                                //celula do mapa onde se localiza a Entidade(indice do vertice do grafo gerado a partir da posicao no mapa)
    int x;                                                                  //abscissa da posicao do ente no mapa(coluna)
    int y;                                                                  //ordenada da posicao do ente no mapa(linha)
} Entidade;

//Funcao que retorna um ponteiro para uma struct Ente dinamicamente alocada
Entidade* entidade_cria(char tipo, int chave, int cel, int x, int y);

//Funcao que desaloca uma struct Ente alocada dinamicamente
void entidade_destroi(Entidade* ente);

#endif // ENTIDADE_H_INCLUDED
