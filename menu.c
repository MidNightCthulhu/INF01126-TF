/*
Programa: menu.c
Objetivos: Arquivo de implementacao do modulo Menu
Entrada/Saida:
Autores:TF9-João Gabriel Poester Oliveira da Costa;
           -Leonardo Moreira Leon;
           -Sergio Artur Luz Wagner.
Data:24/06/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "menu.h"

#define tela_limpa() system("cls")

//Funcao que exibe a tela de abertura do jogo
Cenario* menu_abertura(int* fimJogo){
    char tecla = '\0';
    while(tecla != '1' && tecla != '2' && tecla != '3' && tecla != '4'){
        tela_limpa();
        printf("\t[INICIO]\n1. Iniciar novo jogo\n2. Carregar jogo salvo\n3. Ver ranking\n4. Sair");
        tecla = _getch();
        if(tecla == '1'){
            Cenario* cena = cenario_cria("mapa.txt");
            if(cena != NULL)
                return cena;
        }
        if(tecla == '2'){
            Cenario* cena_carga = menu_carrega();
            if(cena_carga != NULL)
                return cena_carga;
        }
        //if(tecla == '3')
        if(tecla == '4'){
            *fimJogo = 1;
            return NULL;
        }
    }
}

//Funcao que exibe a tela de pausa do jogo
Cenario* menu_pausa(Cenario* cena, int* fimJogo){
    char tecla;
    while(tecla != 27 && tecla != '1' && tecla != '2' && tecla != '3' && tecla != '4' && tecla != '5'){
        tela_limpa();
        printf("\t[PAUSA]\nTecle:\nESC. Continuar\n1. Iniciar novo jogo\n2. Salvar jogo\n3. Carregar jogo salvo\n4. Ver ranking\n5. Sair");
        tecla = _getch();
        if(tecla == 27){
            return cena;
        }
        if(tecla == '1'){
            cenario_destroi(cena);
            cena = cenario_cria("mapa.txt");
            return cena;
        }
        if(tecla == '2'){
            menu_salva(cena);
            return cena;
        }
        if(tecla == '3'){
            Cenario* cena_carga = menu_carrega();
            if(cena_carga != NULL){
                cena = cena_carga;
                return cena;
            }
        }
        //if(tecla == '4')
        if(tecla == '5'){
            *fimJogo = 1;
            return cena;
        }
    }
}

//Funcao que exibe a tela de salvamento de jogo
void menu_salva(Cenario* cena){
    char arqCena[20];
    tela_limpa();
    printf("Digite o nome do arquivo: ");
    scanf("%s", arqCena);
    cenario_salva(cena, arqCena);
    return;
}

//Funcao que exibe a tela de carregamento de jogo
Cenario* menu_carrega(){
    char arqCena[20];
    tela_limpa();
    printf("Digite o nome do arquivo: ");
    scanf("%s", arqCena);
    Cenario* cena_carga = cenario_carrega(arqCena);
    if(!cena_carga){
        printf("\nArquivo inexistente!");
        _sleep(3000);
    }
    return cena_carga;
}

/*/Funcao que exibe a tela de encerramento do jogo
char menu_encerramento(Cenario* cena, int* fimJogo){
    char tecla;
    limpar_tela();
    printf("1. Iniciar novo jogo\n");
    printf("2. Salvar jogo\n");
    printf("3. Carregar jogo salvo\n");
    printf("4. Ver ranking\n");
    printf("5. Sair");
    while(1){
        tecla = _getch();
        if(tecla == '1' || tecla == '2' || tecla == '3' || tecla == '4' || tecla == '5')
                return tecla;
    }

    ●	Vitória: todos os itens foram coletados
●	Derrota: o jogador perdeu todas as vidas
●	Exibição de pontuação e tempo (e ranking, se implementado)

}

//Funcao que exibe a tela de classificacao de jogo
void menu_classificacao(Cenario* cena, int* fimJogo){
}
*/
