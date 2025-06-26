/*
Programa: menu.c
Objetivos: Arquivo de implementacao do TAD Menu
Entrada/Saida:
Autores:TF9-João Gabriel Poester Oliveira da Costa;
           -Leonardo Moreira Leon;
           -Sergio Artur Luz Wagner.
Data:24/06/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "menu.h"

#define limpar_tela() system("cls")

char menu_abertura(){
    char tecla;
    limpar_tela();
    printf("1. Iniciar novo jogo\n");
    printf("2. Carregar jogo salvo\n");
    printf("3. Ver ranking\n");
    printf("4. Sair");
    while(1){
        tecla = _getch();
        if(tecla == '1' || tecla == '2' || tecla == '3' || tecla == '4')
                return tecla;
    }
}

/*/Funcao que abre a tela de pausa do jogo
void menu_pausa(){
}

//Funcao que abre a tela de encerramento do jogo
void menu_encerramento(){
    /*
    ●	Vitória: todos os itens foram coletados
●	Derrota: o jogador perdeu todas as vidas
●	Exibição de pontuação e tempo (e ranking, se implementado)

}

//Funcao que abre a tela de classificacao de jogo
void menu_classificacao(){
}
*/
