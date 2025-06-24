/*
Programa: filaG.c
Objetivos:  Arquivo de implementacao do TAD FilaG - Fila Generica em memoria contigua(vetor)
Entrada/Saida:
Autores:TF9-João Gabriel Poester Oliveira da Costa;
           -Leonardo Moreira Leon;
           -Sergio Artur Luz Wagner.
Data:21/06/2025
*/

#include <stdio.h>                                                                      //(?)necessaria devido ao uso do valor NULL no codigo
#include <stdlib.h>                                                                     //necessaria por causa das funcoes de gerenciamento de memoria malloc, realoc e free usadas no codigo
#include <string.h>                                                                     //necessaria por causa da funcao memmove usada no codigo

#include "filaG.h"                                                                      //interface do TAD FilaG

//Funcao que aloca dinamicamente na memoria uma struct FilaG e retorna um ponteiro para ela
FilaG* filaG_cria(){
    FilaG* fila = (FilaG*) malloc(sizeof(FilaG));                                       //aloca dinamicamente a struct
    if(fila){
        fila->n = 0;                                                                    //representacao de fila vazia
        fila->ini = 0;                                                                  //posicao inicial do primeiro ponteiro a ser desenfileirado no vetor
        fila->dim = 4;                                                                  //dimensao inicial do vetor
        fila->filaG = (void**) malloc(fila->dim * sizeof(void*));                       //aloca dinamicamente o vetor
        if(!fila->filaG){
            free(fila);
            return NULL;
        }
    }
    return fila;                                                                        //retorna o valor do endereco da struct FilaGCont, quando alocada dinamicamente na memoria, ou retorna NULL, caso nao tenha sido alocada
}                                                                                       //Complexidade constante O(1)

//Funcao que insere na ultima posicao da fila um ponteiro para uma struct
void filaG_enfileira(FilaG* fila, void* info){
    if(fila){
        if(fila->n == fila->dim){                                                       //capacidade esgotada
            fila->dim *= 2;                                                             //dobra a capacidade da fila
            fila->filaG = (void**) realloc(fila->filaG, fila->dim * sizeof(void*));     //realoca o vetor com o novo valor do campo dim
            if(fila->ini != 0)
                memmove(&fila->filaG[fila->dim - fila->ini],                            //endereco destino
                &fila->filaG[fila->ini],                                                //endereco origem
                (fila->n - fila->ini) * sizeof(void));                                  //numero de bytes
        }
        fila->filaG[(fila->ini + fila->n++) % fila->dim] = info;                        //enfileira o ponteiro recebido e, depois, incrementa o campo n
    }
}                                                                                       //Complexidade constante O(1)

//Funcao que remove da primeira posicao da fila um ponteiro para uma struct retornando seu valor ou retorna NULL caso a fila esteja vazia
void* filaG_desenfileira(FilaG* fila){
    void* info = NULL;
    if(fila){
        if(fila->n != 0){
            info = fila->filaG[fila->ini];                                              //desenfileira o primeiro ponteiro para struct
            fila->ini = (fila->ini + 1) % fila->dim;                                    //calcula e atribui, o indice no vetor, do novo primeiro ponteiro da fila, proximo a ser desenfileirado
            fila->n--;                                                                  //decrementa a quantidade de ponteiros enfileirados
        }
    }
    return info;
}                                                                                       //Complexidade constante O(1)

//Funcao que retorna 1(um) se a fila estiver vazia e 0(zero) caso a fila nao esteja vazia
int filaG_vazia(FilaG* fila){
    if(fila)
        return (fila->n == 0);                                                          //retorna o valor da expressao
    return 1;                                                                           //se fila nao apontar para uma struct FilaG, para todos os efeitos, e' uma fila vazia
}                                                                                       //Complexidade constante O(1)

//Funcao que retorna o numero ponteiros para structs enfileirados
int filaG_tamanho(FilaG* fila){
    if(fila)
        return fila->n;
    return 0;                                                                           //se fila nao apontar para uma struct FilaG, para todos os efeitos, e' uma fila vazia
}                                                                                       //Complexidade constante O(1)

//Funcao que desaloca da memoria uma struct FilaG
void filaG_destroi(FilaG* fila){
    if(fila){
        free(fila->filaG);
        free(fila);
    }
}                                                                                       //Complexidade constante O(1)

//Funcao que retorna um ponteiro para a copia de uma struct FilaG
FilaG* filaG_copia(FilaG* fila){
    if(fila){
        FilaG* copia = (FilaG*) malloc(sizeof(FilaG));                                  //aloca dinamicamente a struct
        if(copia){
            copia->n = fila->n;                                                         //atribui o valor do campo n
            copia->ini = fila->ini;                                                     //atribui o valor do campo ini
            copia->dim = fila->dim;                                                     //atribui o valor do campo dim
            copia->filaG = (void**) malloc(fila->dim * sizeof(void*));                  //aloca dinamicamente o vetor
            if(!copia->filaG){
                free(copia);
                return NULL;
            }
            memmove(&copia->filaG,                                                      //endereco destino
            &fila->filaG,                                                               //endereco origem
            fila->dim * sizeof(void*));                                                 //numero de bytes
        }
        return copia;
    }
    return NULL;
}
