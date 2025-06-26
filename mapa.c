/*
Programa: mapa.c
Objetivos: Arquivo de implementacao do TAD Mapa
Entrada/Saida:
Autores:TF9-João Gabriel Poester Oliveira da Costa;
           -Leonardo Moreira Leon;
           -Sergio Artur Luz Wagner.
Data:16/06/2025
*/

#include <stdio.h>                                                  //(?)necessaria devido ao uso do valor NULL no codigo
#include <stdlib.h>                                                 //necessaria devido ao uso das funcoes de gerenciamento de memoria malloc() e free() no codigo

#include "mapa.h"                                                   //interface do TAD

//Funcao que retorna um ponteiro para uma struct Mapa alocada dinamicamente
Mapa* mapa_cria(int lin, int col){
    Mapa* mapa = (Mapa*) malloc(sizeof(Mapa));                      //aloca dinamicamente uma struct Mapa
    if(!mapa)                                                       //se o ponteiro para Mapa nao aponta para uma struct Mapa dinamicamente alocada
        return NULL;                                                //retorna o valor NULL, significando que nao alocou struct alguma
    mapa->lin = lin;                                                //atribui o valor do campo lin da struct Mapa dinamicamente alocada
    mapa->col = col;                                                //atribui o valor do campo col da struct Mapa dinamicamente alocada
    mapa->mat = (char**) malloc(lin * sizeof(char*));               //aloca dinamicamente o vetor de ponteiros para vetores de caracteres, que representa as linhas da matriz de caracteres da struct Mapa
    if(!mapa->mat){                                                 //se o ponteiro nao aponta para um vetor de ponteiros para vetores de caracteres dinamicamente alocado
        free(mapa);                                                 //desaloca a struct Mapa
        return NULL;                                                //retorna o valor NULL, significando que nao alocou struct alguma
    }
    for(int j = 0; j < lin; j++){                                   //laco que aloca dinamicamente, para cada indice(linha) do vetor de ponteiros para vetores de characteres,
        mapa->mat[j] = (char*) malloc(col * sizeof(char));          //um novo vetor de caracteres de tamanho igual ao numero de colunas da matriz de caracteres da struct Mapa
        if(!mapa->mat[j]){                                          //se algum dos vetores de caracteres nao for dinamicamente alocado
            for(--j; j >= 0; j--)                                   //tem de, para cada indice do vetor de ponteiros,
                free(mapa->mat[j]);                                 //desalocar todo eventual vetor de caracteres alocado e por ele apontado,
            free(mapa->mat);                                        //desalocar o vetor de ponteiros para vetores de caracteres,
            free(mapa);                                             //desalocar a struct Mapa,
            return NULL;                                            //retorna o valor NULL, significando que nao alocou struct alguma
        }
    }
    return mapa;                                                    //caso todas as alocacoes sejam efetivadas retorna o valor do ponteiro para a struct Mapa dinamicamente alocada
}                                                                   //Complexidade linear - O(n)

//Funcao que desaloca uma struct Mapa dinamicamente alocada
void mapa_destroi(Mapa* mapa){
    if(mapa){                                                       //se o ponteiro recebido efetivamente apontar para uma struct Mapa
        for(int i = 0; i < mapa->lin; i++){                         //tem de, para cada indice do vetor de ponteiros,
            free(mapa->mat[i]);                                     //desalocar todo eventual vetor de caracteres alocado e por ele apontado,
        }
        free(mapa->mat);                                            //desalocar o vetor de ponteiros para vetores de caracteres,
        free(mapa);                                                 //desalocar a struct Mapa.
    }
}                                                                   //Complexidade linear - O(n)

//Funcao que instancia um mapa, carregado a partir de um arquivo, e retorna um ponteiro para essa struct dinamicamente alocada
Mapa* mapa_carrega(const char* nomeArq){
    int x, y;                                                       //variaveis que receberao os valores de linhas e colunas do mapa lidos a partir do arquivo
    FILE* arquivo = fopen(nomeArq, "r");                            //alocacao da struct FILE(buffer de acesso 'a midia do arquivo)
    if(!arquivo){                                                   //se o ponteiro nao apontar para uma struct FILE
        return NULL;                                                //retorna o valor NULL, significando que nao carregou o mapa do arquivo
    }
    //ponteiro para FILE aponta para um arquivo
    if(fscanf(arquivo, "%d,%d\n", &y, &x) != 2){                    //caso a leitura da primeira linha do arquivo do mapa e atribuicao do valor 'a y falhe
        fclose(arquivo);                                            //desaloca a struct FILE
        return NULL;                                                //retorna o valor NULL, significando que nao carregou o mapa do arquivo
    }
    Mapa* mapa = mapa_cria(y, x);                                   //aloca dinamicamente uma struct Mapa com a quantidade de linhas e colunas do arquivo
    if(!mapa){                                                      //se o ponteiro para Mapa nao aponta para uma struct Mapa dinamicamente alocada
        fclose(arquivo);                                            //desaloca a struct FILE
        return NULL;                                                //retorna o valor NULL, significando que nao carregou o mapa do arquivo
    }
    //caso a alocacao da struct Mapa seja efetivada com sucesso
    for(int i = 0; i < y; i++){                                     //inicia-se o laco de preenchimento da matriz de caracteres da struct Mapa que percorrera cada indice do vetor de ponteiros(linhas)
        for(int j = 0; j < x; j++){                                 //e cada indice do vetor de caracteres(colunas)
            mapa->mat[i][j] = fgetc(arquivo);                       //atribuindo cada caracter lido a partir do arquivo do mapa
            if(mapa->mat[i][j] == EOF){                             //caso o arquivo termine sem que a matriz seja totalmente preenchida ou ocorra uma falha na leitura de algum caractere
                mapa_destroi(mapa);                                 //desalocar a struct Mapa,
                fclose(arquivo);                                    //e "fechar" o arquivo(que e' desalocar a struct FILE - o buffer de acesso 'a midia)
                return NULL;                                        //retorna o valor NULL, significando que nao carregou o mapa do arquivo
            }
        }
    }
    fclose(arquivo);                                                //ao final do laco de preenchimento sem falhas desaloca a struct FILE
    return mapa;                                                    //e retorna o valor do ponteiro para a struct Mapa
}                                                                   //Complexidade linear - O(n)

//Funcao que exibe um mapa no console
void mapa_exibe(Mapa* mapa){
    if(mapa){                                                       //se o ponteiro recebido efetivamente apontar para uma struct Mapa
        for(int j = 0; j < mapa->lin; j++){                         //para cada indice do vetor de ponteiros(linha),
            for(int i = 0; i < mapa->col; i++){                     //e para cada indice do vetor de caracteres(coluna),
                printf("%c", mapa->mat[j][i]);                      //exibe o caractere armazenado
            }
            printf("\n");                                           //avancando uma linha ao final de cada linha de caracteres, antes do inicio de nova iteracao do laco mais externo
        }
    }
}                                                                   //Complexidade linear - O(n)
