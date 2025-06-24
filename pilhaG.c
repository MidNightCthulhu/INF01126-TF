/*
Programa: pilhaG.c
Objetivos:  Arquivo de implementacao do TAD PilhaG - Pilha Generica em memoria contigua(vetor)
Entrada/Saida:
Autores:TF9-João Gabriel Poester Oliveira da Costa;
           -Leonardo Moreira Leon;
           -Sergio Artur Luz Wagner.
Data:12/06/2025
*/

#include <stdio.h>                                                                      //(?)necessaria devido ao uso do valor NULL no codigo
#include <stdlib.h>                                                                     //necessaria devido ao uso das funcoes de gerenciamento da memoria malloc(), realloc() e free()

#include "pilhaG.h"                                                                     //interface do TAD PilhaG

//Funcao que aloca dinamicamente na memoria uma struct PilhaG e retorna um ponteiro para ela
PilhaG* pilhaG_cria(){
    PilhaG* pilha = (PilhaG*) malloc(sizeof(PilhaG));                                   //aloca dinamicamente uma struct PilhaG
    if(pilha){
        pilha->n = 0;                                                                   //representacao de pilha vazia
        pilha->dim = 2;                                                                 //dimensao inicial do vetor
        pilha->vet = (void**) malloc(pilha->dim * sizeof(void*));                       //aloca dinamicamente o vetor
        if(!pilha->vet){                                                                //caso o vetor nao seja, por alguma causa, alocado na memoria
            free(pilha);                                                                //desaloca a struct PilhaG recentemente alocada
            return NULL;                                                                //retorna o valor NULL, significando que nao criou a pilha
        }
    }
    return pilha;                                                                       //retorna o valor do endereco da struct PilhaG, quando alocada dinamicamente na memoria, ou retorna NULL, caso nao tenha sido alocada
}                                                                                       //Complexidade constante O(1)

//Funcao que insere no topo da pilha um ponteiro para uma struct
void pilhaG_empilha(PilhaG* pilha, void* info){
    if(pilha){
        if(pilha->n == pilha->dim){                                                     //capacidade da pilha esgotada
            pilha->dim *= 2;                                                            //dobra a capacidade da pilha
            pilha->vet = (void*) realloc(pilha->vet, pilha->dim * sizeof(void));        //realoca o vetor com o novo valor do campo dim
        }
        pilha->vet[pilha->n++] = info;                                                  //insere o ponteiro recebido na proxima posicao livre e depois incrementa o numero de ponteiros empilhados
    }
}                                                                                       //Complexidade constante O(1)

//Funcao que remove do topo da pilha um ponteiro para uma struct retornando seu valor
void* pilhaG_desempilha(PilhaG* pilha){
    if(pilha){
        if(pilha->n > 0)                                                                //pilha nao vazia
            return pilha->vet[--pilha->n];                                              //retira ponteiro para struct do topo decrementando o valor do campo n e depois retornando o valor da posicao do vetor indicada por n
    }
    return NULL;
}                                                                                       //Complexidade constante O(1)

//Funcao que retorna 1(um) se a pilha estiver vazia e, caso contrario, retorna 0(zero)
int pilhaG_vazia(PilhaG* pilha){
    if(pilha)
        return (pilha->n == 0);                                                         //retorna o valor da expressao
    return 1;                                                                           //se pilha nao apontar para uma struct PilhaG, para todos os efeitos, e' uma pilha vazia
}                                                                                       //Complexidade constante O(1)

//Funcao que retorna o numero de ponteiros para structs empilhados
int pilhaG_tamanho(PilhaG* pilha){
    if(pilha)
        return pilha->n;
    return 0;                                                                           //se pilha nao apontar para uma struct PilhaG, para todos os efeitos, e' uma pilha vazia
}                                                                                       //Complexidade constante O(1)

//Funcao que espia o topo da pilha, retorna o valor do topo sem desempilhar
void* pilhaG_topo(PilhaG* pilha){
    if(pilha)
        if(pilha->n > 0)
            return pilha->vet[pilha->n - 1];
    return NULL;
}                                                                                       //Complexidade constante O(1)

//Funcao que desaloca da memoria uma struct PilhaG
void pilhaG_destroi(PilhaG* pilha){
    if(pilha){
        free(pilha->vet);
        free(pilha);
    }
}                                                                                       //Complexidade constante O(1)
