/*
Programa: pilhaG.h
Objetivos: Arquivo de interface do TAD PilhaG - Pilha Generica implementada em memoria contigua(vetor)
Entrada/Saida:
Autores:TF9-João Gabriel Poester Oliveira da Costa;
           -Leonardo Moreira Leon;
           -Sergio Artur Luz Wagner.
Data:12/06/2025
*/

#ifndef PILHAG_H_INCLUDED
#define PILHAG_H_INCLUDED

typedef struct{
    int n;                                                                              //numero de ponteiros para struct empilhados e tambem indice da posicao do vetor onde sera' empilhado o proximo ponteiro no topo da pilha
    int dim;                                                                            //dimensao do vetor de ponteiros
    void** vet;                                                                         //ponteiro para vetor de ponteiros para void que enderecam structs
} PilhaG;

//Funcao que aloca dinamicamente na memoria uma struct PilhaG e retorna um ponteiro para ela
PilhaG* pilhaG_cria();

//Funcao que insere no topo da pilha um ponteiro para uma struct
void pilhaG_empilha(PilhaG* pilha, void* info);

//Funcao que remove do topo da pilha um ponteiro para uma struct retornando seu valor
void* pilhaG_desempilha(PilhaG* pilha);

//Funcao que retorna 1(um) se a pilha estiver vazia e 0(zero) caso a pilha nao esteja vazia
int pilhaG_vazia(PilhaG* pilha);

//Funcao que retorna o numero ponteiros para structs empilhados
int pilhaG_tamanho(PilhaG* pilha);

//Funcao que espia o topo da pilha, retorna o valor do topo sem desempilhar
void* pilhaG_topo(PilhaG* pilha);

//Funcao que desaloca da memoria uma struct PilhaG
void pilhaG_destroi(PilhaG* pilha);

#endif // PILHAG_H_INCLUDED
