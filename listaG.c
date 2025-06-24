/*
Programa: listaG.c
Objetivos: Arquivo de implementacao do TAD ListaG - Lista linear Generica em memoria contigua(vetor)
            Fonte: Adaptado a partir do capitulo 15.3 - Fila dupla com vetor(pg.259), de Introducao a Estruturas de Dados com tecnicas de programacao em C,
                   2ª Edicao, Waldemar Celes, Renato Cerqueira e Jose Lucas Rangel
Entrada/Saida:
Autores:TF9-João Gabriel Poester Oliveira da Costa;
           -Leonardo Moreira Leon;
           -Sergio Artur Luz Wagner.
Data:21/06/2025
*/

#include <stdio.h>                                                                  //(?)necessaria devido ao uso do valor NULL no codigo
#include <stdlib.h>                                                                 //necessaria por causa das funcoes de gerenciamento de memoria malloc, realoc e free usadas no codigo
#include <string.h>                                                                 //necessaria por causa da funcao memmove usada no codigo

#include "listaG.h"                                                                 //interface do TAD ListaG

//Funcao que cria uma lista
ListaG* listaG_cria(){
    ListaG* lista = (ListaG*) malloc(sizeof(ListaG));                               //aloca dinamicamente na memoria uma struct ListaG
    if(lista){                                                                      //caso a struct seja efetivamente alocada
        lista->dim = 4;                                                             //dimensão inicial do vetor
        lista->n = 0;                                                               //representacao de lista vazia
        lista->ini = 0;                                                             //indice da posicao inicial da lista no vetor
        lista->nodos = (void**) malloc(lista->dim * sizeof(void*));                 //aloca dinamicamente na memoria um vetor com dim posicoes para ponteiros para void
        if(!lista->nodos){                                                          //caso o vetor nao seja efetivamente alocado
            free(lista);
            return NULL;                                                            //retorna NULL, a lista nao foi criada
        }
    }
    return lista;                                                                   //caso a struct ListaG nao tenha sido alocada retorna NULL, que e' o valor retornado pela funcao malloc, senao retorna o endereco de memoria armazenado no ponteiro
}                                                                                   //complexidade constante O(1)

//Funcao que retorna a cardinalidade de uma lista
int listaG_tamanho(ListaG* lista){
    if(lista)                                                                       //se o ponteiro recebido aponta de fato para uma struct ListaG alocada na memoria
        return lista->n;                                                            //retorna o valor do campo n da struct
    return 0;                                                                       //caso o ponteiro recebido nao aponte para uma struct ListaG, para todos os efeitos, e' um ponteiro para uma "lista" vazia
}

//Funcao que destroi uma lista
void listaG_destroi(ListaG* lista){                                                 //ja que essa funcao nao tem retorno, a partir da sua chamada, deve-se considerar que qualquer struct ListaG apontada(ou nao) pelo ponteiro lista foi desalocada
    if(lista){                                                                      //se o ponteiro recebido aponta de fato para uma struct ListaG alocada na memoria
        free(lista->nodos);                                                         //desaloca da memoria o vetor de ponteiros para void apontado pelo ponteiro nodos da Struct ListaG lista
        free(lista);                                                                //desaloca da memoria a struct ListaG apontada pelo ponteiro lista
    }
}                                                                                   //complexidade constante O(1)

//Funcao que insere um nodo antes do inicio de uma lista(por cima)
void listaG_insere_ini(ListaG* lista, void* info){
    if(lista){
        if(lista->n == lista->dim){                                                 //capacidade esgotada
            lista->dim *= 2;                                                        //dobra a capacidade da lista
            lista->nodos = (void**) realloc(lista->nodos, lista->dim * sizeof(void*));//realoca o vetor com a nova dimensao
            if(lista->ini != 0){                                                    //caso o inicio da lista esteja deslocado do indice 0(zero) do vetor
                memmove(&lista->nodos[lista->n + lista->ini],                       //endereco destino
                &lista->nodos[lista->ini],                                          //endereco origem
                (lista->n - lista->ini) * sizeof(void*));                           //numero de bytes
                lista->ini += lista->n;                                             //atribuicao do novo indice do inicio da lista no vetor acrescido do numero de itens da lista
            }
        }
        lista->ini = (lista->ini - 1 + lista->dim) % lista->dim;                    //decrementa(circularmente) indice de inicio ******************
        lista->nodos[lista->ini] = info;                                            //armazena a info recebida
        lista->n++;                                                                 //atualiza quantidade de intens
    }
}                                                                                   //complexidade constante O(1)

// Funcao que insere um nodo depois do final de uma lista(por baixo)
void listaG_insere_fim(ListaG* lista, void* info){
    if(lista){
        if(lista->n == lista->dim){                                                 //capacidade esgotada
            lista->dim *= 2;                                                        //dobra a capacidade da lista
            lista->nodos = (void**) realloc(lista->nodos, lista->dim * sizeof(void*));//realoca o vetor com a nova dimensao
            if(lista->ini != 0){                                                    //caso o inicio da lista esteja deslocado do indice 0(zero) do vetor
                memmove(&lista->nodos[lista->n + lista->ini],                       //endereco destino
                &lista->nodos[lista->ini],                                          //endereco origem
                (lista->n - lista->ini) * sizeof(void*));                           //numero de bytes
                lista->ini += lista->n;                                             //atribuicao do novo indice do inicio da lista no vetor
            }
        }
        lista->nodos[(lista->ini + lista->n++) % lista->dim] = info;                //armazena a info recebida no final da lista e, depois, incrementa o campo n *****************
    }
}                                                                                   //complexidade constante O(1)

//Funcao que insere um nodo em uma posicao de uma lista retornando 1(um) quando efetivamente inserido na posicao e 0(zero) caso contrario
int listaG_insere_pos(ListaG* lista, void* info, int pos){                          /*pos e' a posicao do item na lista, nao o indice do item no arranjo!!! Se uma lista tiver apenas um item
                                                                                      ele ocupa a primeira(1a.) posicao da sequencia, convencionalmente, a posicao de cardinalidade um(1),
                                                                                      e de numero 1, cujo indice no arranjo nao e' necessariamente 0. E nem mesmo se tiver mais de um item na
                                                                                      lista o indice da primeira posicao necessariamente sera 0 ou 1, ele variara' de acordo com o historico
                                                                                      de insercoes e remocoes podendo ser qualquer indice do vetor.*/
    int i;
    if(lista){
        if(lista->n == lista->dim){                                                 //capacidade esgotada
            lista->dim *= 2;                                                        //dobra a capacidade da lista
            lista->nodos = (void**) realloc(lista->nodos, lista->dim * sizeof(void*));//realoca o vetor com a nova dimensao
            if(lista->ini != 0){                                                    //caso o inicio da lista esteja deslocado do indice 0(zero) do vetor
                memmove(&lista->nodos[lista->n + lista->ini],                       //endereco destino
                &lista->nodos[lista->ini],                                          //endereco origem
                (lista->n - lista->ini) * sizeof(void*));                            //numero de bytes
                lista->ini += lista->n;                                             //atribuicao do novo indice do inicio da lista no vetor
            }
        }
        if(pos > 0 && pos <= lista->n / 2){                                         //se a posicao recebida estiver entre o inicio e a metade da lista
            for(i = lista->ini; pos > 1; i = (i + 1) % lista->dim){
                lista->nodos[(i - 1 + lista->dim) % lista->dim] = lista->nodos[i];
                pos--;
            }
            lista->nodos[i] = info;
            lista->ini = (lista->ini - 1 + lista->dim) % lista->dim;
            lista->n++;
            return 1;
        }
        if(pos > lista->n / 2 && pos <= lista->n + 1){                              //se a posicao recebida estiver entre a metade e o fim da lista
            for(i = (lista->ini + lista->n - 1) % lista->dim; pos > 2; i = (i - 1 + lista->dim) % lista->dim){
                lista->nodos[(i + 1 + lista->dim) % lista->dim] = lista->nodos[i];
                pos--;
            }
            lista->nodos[i] = info;
            lista->n++;
            return 1;
        }
    }
    return 0;                                                                       //casos em que a posicao de insercao recebida no argumento da chamada da funcao e' invalida ou que o ponteiro lista nao aponta para uma struct ListaG retorna erro, insercao mal sucedida
}                                                                                   //Complexidade linear O(n)

//Funcao que remove um nodo do inicio de uma lista
void listaG_remove_ini(ListaG* lista){
    if(lista){
        if(lista->n > 0){
            lista->ini = (lista->ini + 1) % lista->dim;                             //calcula e atribui o indice no vetor do novo primeiro ponteiro da fila, proximo a ser desenfileirado
            lista->n--;                                                              //decrementa a quantidade de ponteiros na lista
        }
    }
}                                                                                   //complexidade constante O(1)

//Funcao que remove um nodo do final de uma lista
void listaG_remove_fim(ListaG* lista){
    if(lista){
        if(lista->n > 0){
            lista->n--;                                                              //decrementa a quantidade de ponteiros na lista
        }
    }
}                                                                                   //complexidade constante O(1)

//Funcao que remove um nodo em uma posicao de uma lista
int listaG_remove_pos(ListaG* lista, int pos){
    int i, j;
    if(lista){
        if(pos > 0 && pos <= lista->n / 2){                                         //se a posicao recebida estiver entre o inicio e a metade da lista
            for(i = (lista->ini + pos - 1) % lista->dim; pos > 1; i = (i - 1 + lista->dim) % lista->dim){
                lista->nodos[i] = lista->nodos[(i - 1 + lista->dim) % lista->dim];
                pos--;
            }
            lista->ini = (lista->ini + 1) % lista->dim;
            lista->n--;
            return 1;
        }
        if(pos > lista->n / 2 && pos <= lista->n){                                  //se a posicao recebida estiver entre a metade e o fim da lista
            j = lista->n - pos;
            for(i = (lista->ini + pos - 1) % lista->dim; j > 0; i = (i + 1) % lista->dim){
                lista->nodos[i] = lista->nodos[(i + 1) % lista->dim];
                j--;
            }
            lista->n--;
            return 1;
        }
    }
    return 0;                                                                       //casos em que a posicao de remocao recebida no argumento da chamada da funcao e' invalida ou que o ponteiro lista nao aponta para uma struct ListaG retorna erro, remocao mal sucedida
}                                                                                   //Complexidade linear O(n)

//Funcao que consulta um nodo do inicio de uma lista
void* listaG_busca_ini(ListaG* lista){
    if(lista){
        if(lista->n != 0)
            return lista->nodos[lista->ini];
    }
    return NULL;
}                                                                                   //Complexidade constante O(1)

//Funcao que consulta um nodo do fim de uma lista
void* listaG_busca_fim(ListaG* lista){
    if(lista){
        if(lista->n != 0)
            return lista->nodos[(lista->ini + lista->n - 1) % lista->dim];
    }
    return NULL;
}                                                                                   //Complexidade constante O(1)

//Funcao que consulta um nodo de uma posicao de uma lista
void* listaG_busca_pos(ListaG* lista, int pos){
    if(lista){
        if(pos > 0 && pos <= lista->n)
            return lista->nodos[(lista->ini + pos - 1) % lista->dim];
    }
    return NULL;
}                                                                                   //complexidade constante O(1)

//Funcao que copia o conteudo de uma lista para uma nova lista e retorna um ponteiro para a copia
ListaG* listaG_copia(ListaG* lista){
    if(lista){
        if(lista->n > 0){
            ListaG* copia = listaG_cria();
            if(copia){
                for(int i = 1; i <= lista->n; i++)
                    listaG_insere_fim(copia, listaG_busca_pos(lista, i));
                return copia;
            }
        }
    }
    return NULL;
}                                                                                   //Complexidade linear O(n)

//Funcao que concatena umaLista 'a outraLista ficando umaLista com todos os elementos, de ambas, concatenados
void listaG_cat(ListaG* umaLista, ListaG* outraLista){
    if(umaLista && outraLista){
        if(umaLista->n > 0 && outraLista->n > 0){
            while(umaLista->n + outraLista->n > umaLista->dim){
                umaLista->dim *= 2;
                umaLista->nodos = (void**) realloc(umaLista->nodos, umaLista->dim * sizeof(void*));//realoca o vetor com a nova dimensao
            }
            if(umaLista->ini != 0){                                                 //caso o inicio da lista esteja deslocado do indice 0(zero) do vetor
                memmove(&umaLista->nodos[umaLista->n + umaLista->ini],              //endereco destino
                &umaLista->nodos[umaLista->ini],                                    //endereco origem
                (umaLista->n - umaLista->ini) * sizeof(void*));                     //numero de bytes
                umaLista->ini += umaLista->n;                                       //atribuicao do novo indice do inicio da lista no vetor
            }
            for(int i = 1; i <= outraLista->n; i++)
                listaG_insere_fim(umaLista, listaG_busca_pos(outraLista, i));
        }
    }
}                                                                                   //Complexidade linear O(n)

//Funcao que separa uma lista em uma posicao e retorna um ponteiro para a lista separada contendo os elementos posteriores a posicao
ListaG* listaG_separa_pos(ListaG* lista, int pos){
    if(lista){
        if(pos > 0 && pos < lista->n){
            ListaG* separada = listaG_cria();
            if(separada){
                while(lista->n > pos){
                    listaG_insere_fim(separada, listaG_busca_pos(lista, pos + 1));
                    listaG_remove_pos(lista, pos + 1);
                }
                return separada;
            }
        }
    }
    return NULL;
}                                                                                   //Complexidade linear O(n)
