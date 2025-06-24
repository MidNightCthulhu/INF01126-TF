/*
Programa: grafo.c
Objetivos: Arquivo de implementacao do TAD Grafo - Direcionado(Digrafo) e ponderado
            Adaptado a partir do TAD grafo fornecido na Atividade Pratica 6,  alem de renomeadas, foram incluidas verificacoes de seguranca nas funcoes
Entrada/Saida:
Autores:TF9-João Gabriel Poester Oliveira da Costa;
           -Leonardo Moreira Leon;
           -Sergio Artur Luz Wagner.
Data:16/06/2025
*/

#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"

//Funcao que retorna um ponteiro para uma struct Grafo dinamicamente alocada
Grafo* grafo_cria(int vertices){
    Grafo* grafo = (Grafo*) malloc(sizeof(Grafo));                  //aloca dinamicamente uma struct Grafo
    if(!grafo)                                                      //se o ponteiro nao aponta para uma struct Grafo dinamicamente alocada
        return NULL;                                                //retorna o valor NULL, significando que nao alocou struct alguma
    grafo->v = vertices;                                            //atribui o valor do campo v da struct Grafo dinamicamente alocada
    grafo->mat = (float**) malloc(vertices * sizeof(float*));       //aloca dinamicamente o vetor de ponteiros para vetores de reais, que representa os vertices de partida das arestas na matriz de adjacencias da struct Grafo
    if(!grafo->mat){                                                //se o ponteiro nao aponta para um vetor de ponteiros para vetores de reais dinamicamente alocado
        free(grafo);                                                //desaloca a struct Grafo
        return NULL;                                                //retorna o valor NULL, significando que nao alocou struct alguma
    }
    for(int j = 0; j < vertices; j++){                              //laco que aloca dinamicamente, para cada indice(vertice) do vetor de ponteiros para vetores de reais,
        grafo->mat[j] = (float*) malloc(vertices * sizeof(float));  //um novo vetor de reais de tamanho igual ao numero de vertices da struct Grafo, que representa os vertices de chegada das arestas na matriz de adjacencias da struct Grafo
        if(!grafo->mat[j]){                                         //se algum dos vetores de reais nao for dinamicamente alocado
            for(--j; j >= 0; j--)                                   //tem de, para cada indice do vetor de ponteiros,
                free(grafo->mat[j]);                                //desalocar todo eventual vetor de reais alocado e por ele apontado,
            free(grafo->mat);                                       //desalocar o vetor de ponteiros para vetores de reais,
            free(grafo);                                            //desalocar a struct Grafo,
            return NULL;                                            //retorna o valor NULL, significando que nao alocou struct alguma
        }
        for(int i = 0; i < vertices; i++)                           //para cada vetor de reais efetivamente alocado dinamicamente
            grafo->mat[j][i] = -1.0;                                //preenche todos os indices do vetor com um valor de peso considerado invalido(-1.0)
    }
    return grafo;
}                                                                   //Complexidade linear - O(n)

//Funcao que desaloca uma struct Grafo alocada dinamicamente
void grafo_destroi(Grafo* grafo){
    if(grafo){                                                      //se o ponteiro recebido efetivamente apontar para uma struct Grafo
        for(int i = 0; i < grafo->v; i++){                          //tem de, para cada indice do vetor de ponteiros,
            free(grafo->mat[i]);                                    //desalocar todo eventual vetor de reais, dinamicamente alocado e por ele apontado,
        }
        free(grafo->mat);                                           //desalocar o vetor de ponteiros para vetores de reais,
        free(grafo);                                                //desalocar a struct Grafo.
    }
}                                                                   //Complexidade linear - O(n)

//Funcao que insere uma aresta na struct Grafo
int grafo_insere(Grafo* grafo, int v1, int v2, float peso){
    if(grafo){
        if(v1 < 0 || v2 < 0 || v1 >= grafo->v || v2 >= grafo->v)
            return 0;
        grafo->mat[v1][v2] = peso;
        return 1;
    }
    return 0;
}                                                                   //Complexidade constante - O(1)

//Funcao que retira uma aresta da struct Grafo
int grafo_retira(Grafo* grafo, int v1, int v2){
    if(grafo){
        if(grafo->mat[v1][v2] != -1.0){
            grafo->mat[v1][v2] = -1.0;
            return 1;
        }
        return 0;
    }
    return 0;
}                                                                   //Complexidade constante - O(1)

//Funcao que verifica se existe uma aresta entre dois vertices do grafo
int grafo_aresta(Grafo* grafo, int v1, int v2){
    if(grafo)
        return grafo->mat[v1][v2] != -1.0;
    return 0;
}                                                                   //Complexidade constante - O(1)

//Funcao que retorna o peso de uma aresta entre dois vertices do grafo
float grafo_peso(Grafo* grafo, int v1, int v2){
    if(grafo){
        if(grafo->mat[v1][v2] != -1.0)
            return grafo->mat[v1][v2];
    }
    return 0;
}                                                                   //Complexidade constante - O(1)

//Funcao que imprime a tabela de pesos das arestas entre os vertices adjascentes
void grafo_imprime(Grafo* grafo){
    for (int i = 0; i < grafo->v; i++){
        printf("Vertice %d:", i);
        for (int j = 0; j < grafo->v; j++) {
            if (grafo->mat[i][j] != -1.0) {
                printf(" (%d, %.2f)", j, grafo->mat[i][j]);
            }
        }
        printf("\n");
    }
}

//Funcao que aloca dinamicamente uma struct Grafo carregada a partir de um arquivo e retorna um ponteiro para essa instancia
Grafo* grafo_carrega(const char* nome_arquivo){
    int num_vert, v1, v2;
    int peso;
    Grafo* grafo;
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (!arquivo)
        printf("Abertura de arquivo falhou!\n");
    else{
        if(fscanf(arquivo, "%d", &num_vert) != 1)
            printf("Leitura de arquivo falhou!\n");
        grafo = grafo_cria(num_vert);
        while(fscanf(arquivo,"%d %d %.1f\n", &v1, &v2, &peso) != 3){
            grafo_insere(grafo, v1, v2, peso);
        }
        fclose(arquivo);
    }
    return grafo;
}
