/*
Programa: pac-man.c
Objetivos: Arquivo da aplicacao principal, cliente dos TADs
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

#define limpar_tela() system("cls")

int main(){
    Cenario* cena;
    char tecla = menu_abertura();
    if(tecla == '1'){
        cena = cenario_cria("mapa.txt");
    }
    if(tecla == '2'){
        limpar_tela();
        char arqCena[20];
        printf("Digite o nome do arquivo: ");
        scanf("%s", &arqCena);
        cena = cenario_carrega(arqCena);
    }
    while(1){
        if(_kbhit()){
            tecla = _getch();
            if(tecla == 27)
                break;
        }
        _sleep(10);
        limpar_tela();
        mapa_exibe(cena->mapa);
        printf("executando...\n");
        printf("teclou: %c\n", tecla);
    }
    cenario_destroi(cena);
    return 0;
}
