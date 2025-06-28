/*
Programa: pac-man.c
Objetivos: Arquivo da aplicacao principal(funcao main), cliente dos TADs
            - gerenciar loops, colisoes, entradas, vitorias/derrotas.
Entrada/Saida:
Autores:TF9-João Gabriel Poester Oliveira da Costa;
           -Leonardo Moreira Leon;
           -Sergio Artur Luz Wagner.
Data:21/06/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "time.h"
#include "cenario.h"                                                            //interface do TAD Cenario
#include "menu.h"

#define tela_limpa() system("cls")

int main(){
    int fimJogo = 0;                                                            //variavel sinalizadora de final da partida, inicialmente resetada(atribuicao do valor 0(zero))
    char tecla;                                                                 //variavel do caracter da entrada de teclado("buffer")
    Cenario* cena = menu_abertura(&fimJogo);                                    //declaracao do ponteiro para struct Cenario que recebera' o retorno da funcao do menu de abertura
    while(1){                                                                   //inicio do laco principal("infinito")
        if(fimJogo)                                                             //verifica se a sinalizadora de final da partida foi setada(atribuicao do valor 1(um))
            break;                                                              //caso em que o laco e' interrompido
        if(_kbhit()){                                                           //verifica se alguma tecla esta' acionada
            tecla = _getch();                                                   //se o jogador estiver teclando, captura o caracter
            switch(tecla){                                                      //inicio do tratamento da entrada de teclado
                case 27:                                                        //caso a tecla acionada seja ESC, a do caracter SCAPE
                    cena = menu_pausa(cena, &fimJogo);                          //chama a funcao do menu da pausa do jogo
                    break;
                case 'w':                                   //ou 'H'(depois do caracter latino 'O' maiusculo com acento agudo) para seta para cima
                    cena->mov = tecla;
                    break;
                case 'a':                                   //ou 'K'(depois do caracter latino 'O' maiusculo com acento agudo) para ceta para esquerda
                    cena->mov = tecla;
                    break;
                case 's':                                   //ou 'P'(depois do caracter latino 'O' maiusculo com acento agudo) para ceta para baixo
                    cena->mov = tecla;
                    break;
                case 'd':                                   //ou 'M'(depois do caracter latino 'O' maiusculo com acento agudo) para ceta para direita
                    cena->mov = tecla;
            }
        }
        _sleep(10);
        tela_limpa();
        printf("Vidas:%d Pontos:%d\n", cena->vidas, cena->pontos);
        mapa_exibe(cena->mapa);
        printf("executando...\n");
        printf("teclou: %c\n", tecla);
    }
    if(cena != NULL)
        cenario_destroi(cena);
    return 0;
}
