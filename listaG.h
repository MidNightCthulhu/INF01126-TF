/*
Programa: listaG.h
Objetivos: Arquivo da interface do TAD ListaG - Lista linear Generica implementada em memoria contigua(vetor)
            Fonte: Adaptado a partir do capitulo 15.3 - Fila dupla com vetor(pg.259), de Introducao a Estruturas de Dados com tecnicas de programacao em C,
                   2ª Edicao, Waldemar Celes, Renato Cerqueira e Jose Lucas Rangel
Entrada/Saida:
Autores:TF9-João Gabriel Poester Oliveira da Costa;
           -Leonardo Moreira Leon;
           -Sergio Artur Luz Wagner.
Data:21/06/2025
*/

#ifndef _LISTAG_H_
#define _LISTAG_H_

typedef struct{                                                                     //definicao da struct ListaG
   int n;                                                                           //numero de elementos da lista
   int ini;                                                                         //indice do inicio da lista dentro do vetor
   int dim;                                                                         //dimensao atual do vetor
   void** nodos;                                                                    //ponteiro para vetor de ponteiros para void (structs quaisquer)
} ListaG;

//Funcao que cria uma lista
ListaG* listaG_cria();

//Funcao que retorna a cardinalidade de uma lista
int listaG_tamanho(ListaG* lista);

//Funcao que destroi uma lista
void listaG_destroi(ListaG* lista);

//Funcao que insere um nodo antes do inicio de uma lista(por cima)
void listaG_insere_ini(ListaG* lista, void* info);

//Funcao que insere um nodo depois do final de uma lista(por baixo)
void listaG_insere_fim(ListaG* lista, void* info);

//Funcao que insere um nodo em uma posicao de uma lista retornando 1(um) quando efetivamente inserido na posicao e 0(zero) caso contrario
int listaG_insere_pos(ListaG* lista, void* info, int pos);

//Funcao que remove um nodo do inicio de uma lista
void listaG_remove_ini(ListaG* lista);

//Funcao que remove um nodo do final de uma lista
void listaG_remove_fim(ListaG* lista);

//Funcao que remove um nodo em uma posicao de uma lista
int listaG_remove_pos(ListaG* lista, int pos);

//Funcao que consulta um nodo do inicio de uma lista
void* listaG_busca_ini(ListaG* lista);

//Funcao que consulta um nodo do fim de uma lista
void* listaG_busca_fim(ListaG* lista);

//Funcao que consulta um nodo de uma posicao de uma lista
void* listaG_busca_pos(ListaG* lista, int pos);

//Funcao que copia o conteudo de uma lista para uma nova lista e retorna um ponteiro para a copia
ListaG* listaG_copia(ListaG* lista);

//Funcao que concatena umaLista 'a outraLista ficando umaLista com todos os elementos, de ambas, concatenados
void listaG_cat(ListaG* umaLista, ListaG* outraLista);

//Funcao que separa uma lista em uma posicao e retorna um ponteiro para a lista separada contendo os elementos posteriores a posicao
ListaG* listaG_separa_pos(ListaG* lista, int pos);

#endif //_LISTAG_H_
