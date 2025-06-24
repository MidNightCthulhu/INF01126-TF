/*
Programa: teste.c
Objetivos: Arquivo cliente para testes dos TADs
Entrada/Saida:
Autores:TF9-João Gabriel Poester Oliveira da Costa;
           -Leonardo Moreira Leon;
           -Sergio Artur Luz Wagner.
Data:21/06/2025
*/

#include <stdio.h>
#include <stdlib.h>
//#include "conio.h"
//#include "entidade.h"                                                           //interface do TAD Entidade
#include "dijkstra.h"                                                           //interface do TAD Dijkstra
//#include "grafo.h"                                                              //interface do TAD Grafo
#include "cenario.h"                                                            //interface do TAD Cenario
//#include "mapa.h"                                                               //interface do TAD Mapa
//#include "mapa.c"                                                               //apenas para IDEs mal acabadas, como CxStudio para Android, nos demais casos mantenha essa linha comentada

int main(){
    printf("vai gerar cenario a partir de arquivo de mapa\n");
    Cenario* cena1 = cenario_cria("mapa.txt");
    printf("vai imprimir mapa carregado no cenario a partir do arquivo de mapa\n");
    mapa_exibe(cena1->mapa);

    printf("Lista(vetor) de entidades do cenario1:\nChave\tCelula\tTipo\tnoMapa\tLin\tCol\n");

    for(int i = 0; i < cena1->nEntes; i++){
        printf("%d\t%d\t%c\t%d\t%d\t%d\n", cena1->entes[i]->chave, cena1->entes[i]->cel, cena1->entes[i]->tipo, cena1->entes[i]->noMapa, cena1->entes[i]->y, cena1->entes[i]->x);
    }

    printf("Matriz de adjacencias do digrafo\nV.partida   Vertices de chegada e peso da aresta\n");
    grafo_imprime(cena1->grafo);

    printf("Vai salvar o cenario gerado a partir do arquivo de mapa\n");
    cenario_salva(cena1, "cena.txt");
    printf("Vai destruir o cenario gerado a partir do arquivo de mapa\n");
    cenario_destroi(cena1);
    printf("Vai carregar o cenario a partir de arquivo de cenario\n");
    Cenario* cena2 = cenario_carrega("cena.txt");
    printf("vai imprimir mapa carregado no cenario a partir do arquivo de cenario\n");
    mapa_exibe(cena2->mapa);

    printf("Lista(vetor) de entidades do cenario2:\nChave\tCelula\tTipo\tnoMapa\tLin\tCol\n");

    for(int i = 0; i < cena2->nEntes; i++){
        printf("%d\t%d\t%c\t%d\t%d\t%d\n", cena2->entes[i]->chave, cena2->entes[i]->cel, cena2->entes[i]->tipo, cena2->entes[i]->noMapa, cena2->entes[i]->y, cena2->entes[i]->x);
    }

    printf("Matriz de adjacencias do digrafo\nV.partida   Vertices de chegada e peso da aresta\n");
    grafo_imprime(cena2->grafo);

    cenario_ataca(cena2, cena2->entes[85]);

    cenario_destroi(cena2);

    return 0;
}
