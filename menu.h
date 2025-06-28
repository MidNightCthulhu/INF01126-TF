/*
Programa: menu.h
Objetivos: Arquivo de interface do modulo Menu
Entrada/Saida:
Autores:TF9-João Gabriel Poester Oliveira da Costa;
           -Leonardo Moreira Leon;
           -Sergio Artur Luz Wagner.
Data:24/06/2025
*/

#include "cenario.h"

#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

//Funcao que exibe a tela de abertura do jogo
Cenario* menu_abertura(int* fimJogo);

//Funcao que exibe a tela de pausa do jogo
Cenario* menu_pausa(Cenario* cena, int* fimJogo);

//Funcao que exibe a tela de encerramento do jogo
void menu_encerramento(Cenario* cena, int* fimJogo);

//Funcao que exibe a tela de classificacao de jogo
void menu_classificacao(Cenario* cena, int* fimJogo);

//Funcao que exibe a tela de salvamento de jogo
void menu_salva(Cenario* cena);

//Funcao que exibe a tela de carregamento de jogo
Cenario* menu_carrega();

#endif // MENU_H_INCLUDED
