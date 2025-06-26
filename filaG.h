/*
Programa: filaG.h
Objetivos:  Arquivo de interface do TAD FilaG - Fila Generica implementada em memoria contigua(vetor)
Entrada/Saida:
Autores:TF9-João Gabriel Poester Oliveira da Costa;
           -Leonardo Moreira Leon;
           -Sergio Artur Luz Wagner.
Data:21/06/2025
*/

#ifndef FILAG_H_INCLUDED
#define FILAG_H_INCLUDED

typedef struct{                                                                         //definicao da struct FilaG
    int n;                                                                              //numero de ponteiros para struct enfileirados e tambem indice do vetor onde sera' enfileirado o proximo ponteiro na ultima posicao da fila
    int ini;                                                                            //indice do inicio da fila
    int dim;                                                                            //dimensao do vetor de ponteiros
    void** filaG;                                                                       //ponteiro para vetor de ponteiros para void que enderecam structs
} FilaG;

//Funcao que aloca dinamicamente na memoria uma struct FilaG e retorna um ponteiro para ela
FilaG* filaG_cria();

//Funcao que insere na ultima posicao da fila um ponteiro para uma struct
void filaG_enfileira(FilaG* fila, void* info);

//Funcao que remove da primeira posicao da fila um ponteiro para uma struct retornando seu valor ou retorna NULL caso a fila esteja vazia
void* filaG_desenfileira(FilaG* fila);

//Funcao que retorna 1(um) se a fila estiver vazia e 0(zero) caso a fila nao esteja vazia
int filaG_vazia(FilaG* fila);

//Funcao que retorna o numero ponteiros para structs enfileirados
int filaG_tamanho(FilaG* fila);

//Funcao que desaloca da memoria uma struct FilaG
void filaG_destroi(FilaG* fila);

//Funcao que retorna um ponteiro para a copia de uma struct FilaG
FilaG* filaG_copia(FilaG* fila);

#endif // FILAG_H_INCLUDED
