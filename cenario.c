/*
Programa: cenario.c
Objetivos: Arquivo de implementacao do TAD Cenario
            - orquestrar o estado geral (mapa, entidades, pontuacao, eventos).
            - gerenciar loops, colisoes, entradas, vitorias/derrotas.
            - salvar e carregar cenario do jogo
Entrada/Saida:
Autores:TF9-João Gabriel Poester Oliveira da Costa;
           -Leonardo Moreira Leon;
           -Sergio Artur Luz Wagner.
Data:21/06/2025
*/

#include <stdio.h>
#include <stdlib.h>

#include "entidade.h"                                                                                   //interface do TAD Entidade
#include "cenario.h"                                                                                    //interface do TAD Cenario
#include "dijkstra.h"                                                                                   //interface do TAD dijkstra

//Funcao que recebe um arquivo de struct Mapa e retorna um ponteiro para uma struct Cenario dinamicamente alocada gerada a partir desse arquivo
Cenario* cenario_cria(const char* arqMapa){
    Cenario* cena = (Cenario*) malloc(sizeof(Cenario));                                                 //aloca dinamicamente uma struct Cenario
    if(cena){                                                                                           //caso a struct Cenario tenha sido de fato dinamicamente alocada
        cena->mov = 'w';                                                                                //atribuicao do valor da intensao de movimentacao do Pac-Man
        cena->pontos = 0;                                                                               //atribuicao do valor dos pontos do jogador
        cena->vidas = 3;                                                                                //atribuicao do valor da quantidade de vidas do Pac-Man
        cena->imortal = 0;                                                                              //atribuicao do valor inicial da duracao da imortalidade do Pac-Man
        cena->mapa = mapa_carrega(arqMapa);                                                             //atribui ao ponteiro para Mapa da struct Cenario o endereco de uma struct Mapa carregada a partir de um arquivo
        if(!cena->mapa){                                                                                //caso o carregamento da struct Mapa falhe
            free(cena);                                                                                 //desaloca a struct Cenario recentemente alocada
            return NULL;                                                                                //e retorna NULL significando que nenhuma struct Cenario foi efetivamente alocada
        }
        cena->dimEntes = (cena->mapa->lin * cena->mapa->col) / 4;                                       //tamanho inicial do vetor de ponteiros para struct Entidade(1/4 da quantidade de celulas do mapa)
        cena->nEntes = 0;                                                                               //quantidade inicial de ponteiros de struct Entidade armazenados no vetor e valor do indice livre apos o final da lista
        cena->entes = (Entidade**) malloc(cena->dimEntes * sizeof(Entidade*));                          //caso o mapa seja carregado, atribui ao ponteiro entes da struct Cenario um vetor de ponteiros para Entidade dinamicamente alocado
        if(!cena->entes){                                                                               //caso a alocacao do vetor falhe
            mapa_destroi(cena->mapa);                                                                   //desaloca a struct Mapa
            free(cena);                                                                                 //desaloca a struct Cenario
            return NULL;                                                                                //e retorna NULL significando que nenhuma struct Cenario foi efetivamente alocada
        }
        cena->fantasmas = filaG_cria();                                                                 //caso o vetor de entidades seja efetivamente alocado, atribui ao ponteiro fantasmas da struct Cenario uma struct FilaG dinamicamente alocada
        if(!cena->fantasmas){                                                                           //se a fila de fantasmas nao for de fato criada
            free(cena->entes);                                                                          //desaloca o vetor de ponteiros para struct Entidade
            mapa_destroi(cena->mapa);                                                                   //desaloca a struct Mapa
            free(cena);                                                                                 //desaloca a struct Cenario
            return NULL;                                                                                //e retorna NULL significando que nenhuma struct Cenario foi efetivamente alocada
        }
        //preenchimento do vetor de ponteiros para struct Entidade
        Entidade* ente;                                                                                 //declara estaticamente um ponteiro para struct Entidade auxiliar para o processo
        for(int i = 0; i < cena->mapa->lin; i++){                                                       //inicia o laco que percorrera' os indices das linhas da matriz de caracteres do mapa
            for(int j = 0; j < cena->mapa->col; j++){                                                   //inicia o laco que percorrera' os indices das colunas da matriz de caracteres do mapa
                if(cena->mapa->mat[i][j] != '#' && cena->mapa->mat[i][j] != ' '){                       //se um dado caractere de uma celula(i x j) do mapa for entidade(diferente de parede'#' e de chao' ')
                    ente = entidade_cria(cena->mapa->mat[i][j], cena->nEntes, j, i);//aloca dinamicamente uma struct Entidade, passando os argumentos da chamada da funcao entidade_cria(tipo, chave, x, y) adequados, e atribui sua posicao na memoria ao valor do ponteiro ente
                    if(!ente){                                                                          //se a struct Entidade nao for de fato alocada
                        filaG_destroi(cena->fantasmas);                                                 //desaloca a struct FilaG
                        free(cena->entes);                                                              //desaloca o vetor de ponteiros para struct Entidade
                        mapa_destroi(cena->mapa);                                                       //desaloca a struct Mapa
                        free(cena);                                                                     //desaloca a struct Cenario
                        return NULL;                                                                    //e retorna NULL significando que nenhuma struct Cenario foi efetivamente alocada
                    }
                    if(cena->nEntes == cena->dimEntes){                                                 //caso a struct Entidade seja de fato criada, verifica se a capacidade do vetor esta' esgotada
                        cena->dimEntes *= 2;                                                            //dobra a capacidade do vetor
                        cena->entes = (Entidade**) realloc(cena->entes, cena->dimEntes * sizeof(Entidade*));//realoca o vetor com a nova dimensao
                    }
                    cena->entes[cena->nEntes] = ente;                                                   //atribui o valor do ponteiro ente ao indice do fim da lista no vetor, que por sua vez devera' coincidir com o valor do campo chave da Entidade
                    if(cena->mapa->mat[i][j] == 'F')                                                    //e quando a entidade for o fantasma F
                        cena->chaveF = cena->nEntes;                                                    //atribui a chave da entidade ao campo chaveP do cenario
                    if(cena->mapa->mat[i][j] == 'G')                                                    //e quando a entidade for o fantasma G
                        cena->chaveG = cena->nEntes;                                                    //atribui a chave da entidade ao campo chaveP do cenario
                    if(cena->mapa->mat[i][j] == 'H')                                                    //e quando a entidade for o fantasma H
                        cena->chaveH = cena->nEntes;                                                    //atribui a chave da entidade ao campo chaveP do cenario
                    if(cena->mapa->mat[i][j] == 'J')                                                    //e quando a entidade for o fantasma J
                        cena->chaveJ = cena->nEntes;                                                    //atribui a chave da entidade ao campo chaveP do cenario
                    if(cena->mapa->mat[i][j] == 'P')                                                    //e quando a entidade for o Pac-Man
                        cena->chaveP = cena->nEntes;                                                    //atribui a chave da entidade ao campo chaveP do cenario
                    cena->nEntes++;                                                                     //e incrementa o valor do numero de entidades na lista do cenario
                }
            }
        }
        cena->grafo = grafo_cria(cena->mapa->lin * cena->mapa->col);                                    //aloca dinamicamente uma struct Grafo, com numero de vertices igual ao de celulas do mapa, para o ponteiro grafo da struct Cenario
        if(!cena->grafo){                                                                               //se a struct Grafo nao for de fato alocada
            filaG_destroi(cena->fantasmas);                                                             //desaloca a struct FilaG
            free(cena->entes);                                                                          //desaloca o vetor de ponteiros para struct Entidade
            mapa_destroi(cena->mapa);                                                                   //desaloca a struct Mapa
            free(cena);                                                                                 //desaloca a struct Cenario
            return NULL;                                                                                //e retorna NULL significando que nenhuma struct Cenario foi efetivamente alocada
        }
        //preenchimento da matriz de adjacencias do digrafo ponderado
        for(int i = 0; i < cena->mapa->lin; i++){
            for(int j = 0; j < cena->mapa->col; j++){
                if(cena->mapa->mat[i][j] != '#'){                                                       //se uma celula do mapa contem um caractere diferente de parede
                    if(cena->mapa->mat[i][(j + 1) % cena->mapa->col] != '#')                            //e se o caractere da celula 'a direita(circularmente) tambem for diferente de parede
                        grafo_insere(cena->grafo, (i * cena->mapa->col) + j, (i * cena->mapa->col) + ((j + 1) % cena->mapa->col), 1.0);//insere uma aresta de peso 1.0 entre esses vertices
                    if(cena->mapa->mat[((i - 1) + cena->mapa->lin) % cena->mapa->lin][j] != '#')        //e se o caractere da celula de cima(circularmente) tambem for diferente de parede
                        grafo_insere(cena->grafo, (i * cena->mapa->col) + j, ((((i - 1) + cena->mapa->lin) % cena->mapa->lin) * cena->mapa->col) + j, 1.0);//insere uma aresta de peso 1.0 entre esses vertices
                    if(cena->mapa->mat[i][((j - 1) + cena->mapa->col) % cena->mapa->col] != '#')        //e se o caractere da celula 'a esquerda(circularmente) tambem for diferente de parede
                        grafo_insere(cena->grafo, (i * cena->mapa->col) + j, (i * cena->mapa->col) + (((j - 1) + cena->mapa->col) % cena->mapa->col), 1.0);//insere uma aresta de peso 1.0 entre esses vertices
                    if(cena->mapa->mat[(i + 1) % cena->mapa->lin][j] != '#')                            //e se o caractere da celula de baixo(circularmente) tambem for diferente de parede
                        grafo_insere(cena->grafo, (i * cena->mapa->col) + j, (((i + 1) % cena->mapa->lin) * cena->mapa->col) + j, 1.0);//insere uma aresta de peso 1.0 entre esses vertices
                }
            }
        }
    }
    return cena;
}

//Funcao que desaloca uma struct Cenario dinamicamente alocada
void cenario_destroi(Cenario* cena){
    if(cena){
        filaG_destroi(cena->fantasmas);                                                                 //desaloca a struct FilaG
        free(cena->entes);                                                                              //desaloca o vetor de ponteiros para struct Entidade
        mapa_destroi(cena->mapa);                                                                       //desaloca a struct Mapa
        free(cena);                                                                                     //desaloca a struct Cenario
    }
}

//Funcao que salva uma struct Cenario em arquivo
int cenario_salva(Cenario* cena, const char* nomeArq){
    if(!cena)                                                                                           //caso o ponteiro recebido nao aponte para uma struct Cenario
        return 0;                                                                                       //retorna o valor 0(zero), significando que nao salvou a struct Cenario em arquivo
    Entidade* enteAux;                                                                                  //ponteiro auxiliar para acessar os campos do TAD Entidade do vetor e da fila(generica) de fantasmas
    FILE* arquivo = fopen(nomeArq, "w");                                                                //alocacao da struct FILE(buffer de acesso 'a midia do arquivo)
    if(!arquivo)                                                                                        //se o ponteiro nao apontar para uma struct FILE
        return 0;                                                                                       //retorna o valor 0(zero), significando que nao salvou a struct Cenario no arquivo
    //ponteiro para FILE aponta para um arquivo na midia
    if(fprintf(arquivo, "%c,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n", cena->mov, cena->vidas, cena->pontos,
        cena->imortal, cena->chaveF, cena->chaveG, cena->chaveH, cena->chaveJ, cena->chaveP,
        cena->dimEntes, cena->nEntes, cena->mapa->lin, cena->mapa->col) < 27){                          //caso a escrita da primeira linha do arquivo, contendo os valores dos campos mov, vidas, pontos, e dos campos lin e col da struct Mapa apontada pelo ponteiro mapa da struct Cenario recebida, falhe
        fclose(arquivo);                                                                                //desaloca a struct FILE
        return 0;                                                                                       //retorna o valor 0(zero), significando que nao salvou a struct Cenario no arquivo
    }
    for(int i = 0; i < cena->mapa->lin; i++){                                                           //inicia o laco que vai escrever a segunda linha do arquivo,
        for(int j = 0; j < cena->mapa->col; j++){                                                       //contendo todos os caracteres da matriz do mapa
            if(fputc(cena->mapa->mat[i][j], arquivo) == EOF){                                           //caso alguma operacao de escrita no arquivo falhe
                fclose(arquivo);                                                                        //desaloca a struct FILE
                return 0;                                                                               //retorna o valor 0(zero), significando que nao salvou a struct Cenario no arquivo
            }
        }
    }
    if(fputc('\n', arquivo) == EOF){
        fclose(arquivo);                                                                                //desaloca a struct FILE
        return 0;                                                                                       //retorna o valor 0(zero), significando que nao salvou a struct Cenario no arquivo
    }
    //inicio da escrita das linhas do arquivo que conterao os valores referentes 'a lista das entidades
    for(int i = 0; i < cena->nEntes; i++){
        enteAux =  cena->entes[i];
        if(fprintf(arquivo, "%d,%d,%d,%d,%d,%d,%c\n", enteAux->chave, enteAux->imortal, enteAux->noMapa,
            enteAux->tregua, enteAux->x, enteAux->y, enteAux->tipo) < 14){                              //caso a escrita falhe
            fclose(arquivo);                                                                            //desaloca a struct FILE
        return 0;                                                                                       //retorna o valor 0(zero), significando que nao salvou a struct Cenario no arquivo
        }
    }
    //inicio da escrita das linhas do arquivo que conterao os valores referentes 'a fila de fantasmas
    //primeiro o tamanho da fila
    if(fprintf(arquivo, "%d\n", filaG_tamanho(cena->fantasmas)) < 2){                                   //caso a escrita do tamanho da fila de fantasmas na setima linha do arquivo, falhe
        fclose(arquivo);                                                                                //desaloca a struct FILE
        return 0;                                                                                       //retorna o valor 0(zero), significando que nao salvou a struct Cenario em arquivo
    }
    //depois, se houver, a fila dos fantasmas(apenas suas chaves correspondentes a suas posicoes no vetor das entidades)
    if(filaG_tamanho(cena->fantasmas) > 0){                                                             //se houver algum fantasma na fila
        FilaG* copia = filaG_copia(cena->fantasmas);                                                    //cria uma copia da fila de fantasmas que sera consumida para escrever no arquivo
        if(!copia){                                                                                     //se a copia nao for alocada
            fclose(arquivo);                                                                            //desaloca a struct FILE
            return 0;                                                                                   //retorna o valor 0(zero), significando que nao salvou a struct Cenario em arquivo
        }
        for(int i = filaG_tamanho(cena->fantasmas); i > 0; i--){
            enteAux = (Entidade*) filaG_desenfileira(copia);                                            //mudanca explicita de tipo do ponteiro retornado pela fila generica de void* para Entidade*
            if(fprintf(arquivo, "%d\n", enteAux->chave) < 2){                                           //caso a escrita no arquivo falhe
                fclose(arquivo);                                                                        //desaloca a struct FILE
                return 0;                                                                               //retorna o valor 0(zero), significando que nao salvou a struct Cenario em arquivo
            }
        }
        filaG_destroi(copia);                                                                           //desaloca a copia da fila de fantasmas, que ficou vazia
    }
    fclose(arquivo);
    return 1;
}

//Funcao que carrega uma struct Cenario a partir de um arquivo
Cenario* cenario_carrega(const char* nomeArq){
    int lin = 0, col = 0;                                                                               //variaveis auxiliares
    Entidade* enteAux;                                                                                  //ponteiro auxiliar para struct Entidade
    FILE* arquivo = fopen(nomeArq, "r");                                                                //alocacao da struct FILE(buffer de acesso 'a midia do arquivo)
    if(!arquivo)                                                                                        //se o ponteiro nao apontar para uma struct FILE
        return NULL;                                                                                    //retorna o valor NULL, significando que nao carregou a struct Cenario do arquivo
    //ponteiro para FILE aponta para um arquivo na midia
    Cenario* cena = (Cenario*) malloc(sizeof(Cenario));                                                 //aloca dinamicamente uma struct Cenario
    if(!cena){
        fclose(arquivo);                                                                                //desaloca a struct FILE
        return NULL;                                                                                    //retorna o valor NULL, significando que nao carregou a struct Cenario do arquivo
    }
    //caso a struct Cenario tenha sido de fato dinamicamente alocada
    if(fscanf(arquivo, "%c,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n", &cena->mov, &cena->vidas,
        &cena->pontos, &cena->imortal, &cena->chaveF, &cena->chaveG, &cena->chaveH, &cena->chaveJ,
        &cena->chaveP, &cena->dimEntes, &cena->nEntes, &lin, &col) != 13){                              //se a leitura da primeira linha do arquivo do Cenario, falhar
        free(cena);                                                                                     //desaloca a struct Cenario
        fclose(arquivo);                                                                                //desaloca a struct FILE
        return NULL;                                                                                    //retorna o valor NULL, significando que nao carregou a struct Cenario do arquivo
    }
    cena->mapa = mapa_cria(lin, col);                                                                   //atribui ao ponteiro para Mapa da struct Cenario o endereco de uma nova struct Mapa dinamicamente alocada
    if(!cena->mapa){                                                                                    //caso a alocacao da struct Mapa falhe
        free(cena);                                                                                     //desaloca a struct Cenario
        fclose(arquivo);                                                                                //desaloca a struct FILE
        return NULL;                                                                                    //retorna o valor NULL, significando que nao carregou a struct Cenario do arquivo
    }
    //caso a nova struct Mapa seja de fato dinamicamente alocada, preenchemos sua matriz de caracteres lendo cada caractere da segunda linha do arquivo de Cenario
    for(int i = 0; i < cena->mapa->lin; i++){                                                           //para cada linha da matriz de caracteres do mapa
        for(int j = 0; j < cena->mapa->col; j++){                                                       //e para cada coluna da matriz de caracteres do mapa
            cena->mapa->mat[i][j] = fgetc(arquivo);
            if(cena->mapa->mat[i][j] == EOF){
                mapa_destroi(cena->mapa);                                                               //desaloca a struct Mapa
                free(cena);                                                                             //desaloca a struct Cenario
                fclose(arquivo);                                                                        //desaloca a struct FILE
                return NULL;                                                                            //retorna o valor NULL, significando que nao carregou a struct Cenario do arquivo
            }
        }
    }
    //apos preencher a matriz de caracteres da struct Mapa
    cena->entes = (Entidade**) malloc(cena->dimEntes * sizeof(Entidade*));                              //caso o mapa seja carregado, atribui ao ponteiro entes da struct Cenario um vetor de ponteiros para Entidade dinamicamente alocado
    if(!cena->entes){                                                                                   //caso a alocacao do vetor falhe
        mapa_destroi(cena->mapa);                                                                       //desaloca a struct Mapa
        free(cena);                                                                                     //desaloca a struct Cenario
        fclose(arquivo);                                                                                //desaloca a struct FILE
        return NULL;                                                                                    //e retorna NULL significando que nenhuma struct Cenario foi efetivamente alocada
    }
    //a essa altura do codigo o vetor das entidades esta alocado e deve ser preenchido com o conteudo do arquivo
    for(int i = 0; i < cena->nEntes; i++){
        enteAux = entidade_cria('\0',0,0,0);                                                            //aloca dinamicamente uma struct Entidade
        if(!enteAux){                                                                                   //caso nao seja alocada
            free(cena->entes);                                                                          //desaloca o vetor de ponteiros para Entidade
            mapa_destroi(cena->mapa);                                                                   //desaloca a struct Mapa
            free(cena);                                                                                 //desaloca a struct Cenario
            fclose(arquivo);                                                                            //desaloca a struct FILE
            return NULL;                                                                                //e retorna NULL significando que nenhuma struct Cenario foi efetivamente alocada
        }
        if(fscanf(arquivo, "%d,%d,%d,%d,%d,%d,%c\n", &enteAux->chave, &enteAux->imortal,
            &enteAux->noMapa, &enteAux->tregua, &enteAux->x, &enteAux->y, &enteAux->tipo) != 7){        //caso a leitura falhe
            free(cena->entes);                                                                          //desaloca o vetor de ponteiros para Entidade
            mapa_destroi(cena->mapa);                                                                   //desaloca a struct Mapa
            free(cena);                                                                                 //desaloca a struct Cenario
            fclose(arquivo);                                                                            //desaloca a struct FILE
            return NULL;                                                                                //e retorna NULL significando que nenhuma struct Cenario foi efetivamente alocada
        }
        if(cena->nEntes == cena->dimEntes){                                                             //caso a struct Entidade seja de fato criada, verifica se a capacidade do vetor esta' esgotada
            cena->dimEntes *= 2;                                                                        //dobra a capacidade do vetor
            cena->entes = (Entidade**) realloc(cena->entes, cena->dimEntes * sizeof(Entidade*));        //realoca o vetor com a nova dimensao
        }
        cena->entes[i] = enteAux;                                                                       //atribui ao indice do vetor o valor do ponteiro auxiliar para struct Entidade
        if(enteAux->tipo == 'F')                                                                        //e quando a entidade for o fantasma F
            cena->chaveF = enteAux->chave;                                                              //atribui a chave da entidade ao campo chaveP do cenario
        if(enteAux->tipo == 'G')                                                                        //e quando a entidade for o fantasma G
            cena->chaveG = enteAux->chave;                                                              //atribui a chave da entidade ao campo chaveP do cenario
        if(enteAux->tipo == 'H')                                                                        //e quando a entidade for o fantasma H
            cena->chaveH = enteAux->chave;                                                              //atribui a chave da entidade ao campo chaveP do cenario
        if(enteAux->tipo == 'J')                                                                        //e quando a entidade for o fantasma J
            cena->chaveJ = enteAux->chave;                                                              //atribui a chave da entidade ao campo chaveP do cenario
        if(enteAux->tipo == 'P')                                                                        //e quando a entidade for o Pac-Man
            cena->chaveP = enteAux->chave;                                                              //atribui a chave da entidade ao campo chaveP do cenario
    }
    //apos preencher o vetor das entidades falta ainda criar e carregar a fila de fantasmas
    cena->fantasmas = filaG_cria();                                                                     //caso a lista de entidades seja efetivamente alocada, atribui ao ponteiro fantasmas da struct Cenario uma struct FilaG dinamicamente alocada
    if(!cena->fantasmas){                                                                               //se a fila de fantasmas nao for de fato criada
        free(cena->entes);                                                                              //desaloca o vetor de ponteiros para Entidade
        mapa_destroi(cena->mapa);                                                                       //desaloca a struct Mapa
        free(cena);                                                                                     //desaloca a struct Cenario
        fclose(arquivo);                                                                                //desaloca a struct FILE
        return NULL;                                                                                    //e retorna NULL significando que nenhuma struct Cenario foi efetivamente alocada
    }
    if(fscanf(arquivo, "%d\n", &lin) != 1){                                                             //se a leitura da linha do arquivo do Cenario, contendo o valor do tamanho da fila de fantasmas, falhar
        filaG_destroi(cena->fantasmas);                                                                 //desaloca a struct FilaG
        free(cena->entes);                                                                              //desaloca o vetor de ponteiros para Entidade
        mapa_destroi(cena->mapa);                                                                       //desaloca a struct Mapa
        free(cena);                                                                                     //desaloca a struct Cenario
        fclose(arquivo);                                                                                //desaloca a struct FILE
        return NULL;                                                                                    //e retorna NULL significando que nenhuma struct Cenario foi efetivamente alocada
    }
    if(lin > 0){                                                                                        //se houver algum fantasma na fila
        for(int i = lin; i > 0; i--){
            if(fscanf(arquivo, "%d\n", &col) != 1){                                                     //caso a leitura de qualquer das chaves de entidade fantasma da fila falhe
                filaG_destroi(cena->fantasmas);                                                         //desaloca a struct FilaG
                free(cena->entes);                                                                      //desaloca o vetor de ponteiros para Entidade
                mapa_destroi(cena->mapa);                                                               //desaloca a struct Mapa
                free(cena);                                                                             //desaloca a struct Cenario
                fclose(arquivo);                                                                        //desaloca a struct FILE
                return NULL;                                                                            //e retorna NULL significando que nenhuma struct Cenario foi efetivamente alocada
            }
            filaG_enfileira(cena->fantasmas, cena->entes[col]);                                         //obtendo a leitura do arquivo, insere na fila os ponteiros para os fantasmas, cujas chaves lidas do arquivo sao seus indices no vetor ponteiros para Entidade
        }
    }
    fclose(arquivo);
    //agora alocaremos o digrafo para a struct Cenario e preencheremos de acordo com os dados ja' lidos do arquivo(mais exatamente a matriz de caracteres do mapa)
    cena->grafo = grafo_cria(cena->mapa->lin * cena->mapa->col);                                        //aloca dinamicamente uma struct Grafo, com numero de vertices igual ao de celulas do mapa, para o ponteiro grafo da struct Cenario
    if(!cena->grafo){                                                                                   //se a struct Grafo nao for de fato alocada
        filaG_destroi(cena->fantasmas);                                                                 //desaloca a struct FilaG
        free(cena->entes);                                                                              //desaloca o vetor de ponteiros para struct Entidade
        mapa_destroi(cena->mapa);                                                                       //desaloca a struct Mapa
        free(cena);                                                                                     //desaloca a struct Cenario
        return NULL;                                                                                    //e retorna NULL significando que nenhuma struct Cenario foi efetivamente alocada
    }
    //preenchimento da matriz de adjacencias do digrafo ponderado
    for(int i = 0; i < cena->mapa->lin; i++){
        for(int j = 0; j < cena->mapa->col; j++){
            if(cena->mapa->mat[i][j] != '#'){                                                           //se uma celula do mapa contem um caractere diferente de parede
                if(cena->mapa->mat[i][(j + 1) % cena->mapa->col] != '#')                                //e se o caractere da celula 'a direita(circularmente) tambem for diferente de parede
                    grafo_insere(cena->grafo, (i * cena->mapa->col) + j, (i * cena->mapa->col) + ((j + 1) % cena->mapa->col), 1.0);//insere uma aresta de peso 1.0 entre esses vertices
                if(cena->mapa->mat[((i - 1) + cena->mapa->lin) % cena->mapa->lin][j] != '#')            //e se o caractere da celula de cima(circularmente) tambem for diferente de parede
                    grafo_insere(cena->grafo, (i * cena->mapa->col) + j, ((((i - 1) + cena->mapa->lin) % cena->mapa->lin) * cena->mapa->col) + j, 1.0);//insere uma aresta de peso 1.0 entre esses vertices
                if(cena->mapa->mat[i][((j - 1) + cena->mapa->col) % cena->mapa->col] != '#')            //e se o caractere da celula 'a esquerda(circularmente) tambem for diferente de parede
                    grafo_insere(cena->grafo, (i * cena->mapa->col) + j, (i * cena->mapa->col) + (((j - 1) + cena->mapa->col) % cena->mapa->col), 1.0);//insere uma aresta de peso 1.0 entre esses vertices
                if(cena->mapa->mat[(i + 1) % cena->mapa->lin][j] != '#')                                //e se o caractere da celula de baixo(circularmente) tambem for diferente de parede
                    grafo_insere(cena->grafo, (i * cena->mapa->col) + j, (((i + 1) % cena->mapa->lin) * cena->mapa->col) + j, 1.0);//insere uma aresta de peso 1.0 entre esses vertices
            }
        }
    }
    return cena;
}

//Funcoes de movimentacao dos fantasmas
void cenario_move_ente(Cenario* cena, int* chFant){
    int tam, lin, col;                                                                                  //dimensao do vetor de vertices que sera' gerado pelo algoritmo de Dijkstra
    if(cena->entes[cena->chaveP]->imortal > 0)
        int* caminho = RETORNO DA FUNCAO FOGE;
    else
        int* caminho = RETORNO DA FUNCAO ATACA;
    for(int i = 0; i < tam; i++){
        col = caminho[i] % cena->mapa->col;                                                             //atribuimos o valor da abscissa do destino da entidade no mapa
        lin = caminho[i] / cena->mapa->col;                                                             //atribuimos o valor da ordenada do destino da entidade no mapa
        if(cena->entes[chFant]->x != col)
            cena->entes[chFant]->x = col;
        if(cena->entes[chFant]->y != lin)
            cena->entes[chFant]->y = lin;
    }
}

//Ataques
int* cenario_F_ataca(Cenario* cena; int* tam){
    Dijkstra* f = dijkstra(cena->grafo, (cena->entes[cena->chaveF]->y * cena->mapa->col) + cena->entes[cena->chaveF]->x);//alocamos uma struct Dijkstra baseada no Digrafo da struct Cenario e com origem no vertice da Entidade fantasma F
    int* caminho = dijkstra_reconstroi_caminho(f, (cena->entes[cena->chaveP]->y * cena->mapa->col) + cena->entes[cena->chaveP]->x, &tam);//obtem o vetor com a sequencia dos vertices entre o vertice origem do fantasma e o vertice destino do Pac-Man
    dijkstra_destroi(f);
    return caminho;
}
