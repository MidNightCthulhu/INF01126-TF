/*
Programa: mapa.h
Objetivos: Arquivo de interface do TAD Mapa
Entrada/Saida:
Autores:TF9-João Gabriel Poester Oliveira da Costa;
           -Leonardo Moreira Leon;
           -Sergio Artur Luz Wagner.
Data:16/06/2025
*/

#ifndef MAPA_H_INCLUDED
#define MAPA_H_INCLUDED

typedef struct{                                             //definicao da struct Mapa
    int lin;                                                //quantidade de linhas do mapa
    int col;                                                //quantidade de colunas do mapa
    char** mat;                                             //ponteiro para matriz de caracteres
} Mapa;

//Funcao que retorna um ponteiro para uma struct Mapa dinamicamente alocada
Mapa* mapa_cria(int lin, int col);

//Funcao que desaloca uma struct Mapa dinamicamente alocada
void mapa_destroi(Mapa* mapa);

//Funcao que instancia um mapa, carregado a partir de um arquivo, e retorna um ponteiro para essa instancia de TAD Mapa
Mapa* mapa_carrega(const char* nomeArq);

//Funcao que exibe um mapa no console
void mapa_exibe(Mapa* mapa);

#endif // MAPA_H_INCLUDED
