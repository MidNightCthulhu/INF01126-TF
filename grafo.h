/*
Programa: grafo.h
Objetivos: Arquivo de interface do TAD Grafo - Direcionado e ponderado
            Adaptado a partir do TAD grafo fornecido na Atividade Pratica 6,  alem de renomeadas, foram incluidas verificacoes de seguranca nas funcoes
Entrada/Saida:
Autores:TF9-João Gabriel Poester Oliveira da Costa;
           -Leonardo Moreira Leon;
           -Sergio Artur Luz Wagner.
Data:16/06/2025
*/

#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

typedef struct{
    int v;                                                  //numero de vertices do grafo
    float** mat;                                            //ponteiro para vetor de ponteiros para reais(tabela de pesos das arestas entre vertices adjacentes)
} Grafo;

//Funcao que retorna um ponteiro para uma struct Grafo dinamicamente alocada
Grafo* grafo_cria(int vertices);

//Funcao que desaloca uma struct Grafo alocada dinamicamente
void grafo_destroi(Grafo* grafo);

//Funcao que insere uma aresta na struct Grafo
int grafo_insere(Grafo* grafo, int v1, int v2, float peso);

//Funcao que retira uma aresta da struct Grafo
int grafo_retira(Grafo* grafo, int v1, int v2);

//Funcao que verifica se existe uma aresta entre dois vertices do grafo
int grafo_aresta(Grafo* grafo, int v1, int v2);

//Funcao que retorna o peso de uma aresta entre dois vertices do grafo
float grafo_peso(Grafo* grafo, int v1, int v2);

//Funcao que imprime a tabela de pesos das arestas entre os vertices adjacentes
void grafo_imprime(Grafo* grafo);

//Funcao que aloca dinamicamente uma struct Grafo carregada a partir de um arquivo e retorna um ponteiro para essa instancia
Grafo* grafo_carrega(const char* nome_arquivo);

#endif // GRAFO_H_INCLUDED
