/* ARQUITETURA E ORGANIZACAO DE COMPUTADORES II - SIMULADOR DE MAQUINA DE PILHA

Autor: Andrei Pochmann Koenich

O programa a seguir simula uma arquitetura computacional baseada em uma maquina de pilha. O programa recebe do usuario
via teclado um arquivo texto, contendo outro programa escrito com o assembly da maquina, e retorna na saida os resultados
esperados por meio da execucao das instrucoes do arquivo de entrada. Caso o arquivo texto de entrada possua instrucoes
invalidas, o programa indica quais linhas contem essas instrucoes e qual o erro especifico. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <unistd.h>
#include <termios.h>

#include "../Headers/constantes.h"
#include "../Headers/gerais.h"
#include "../Headers/controleArquivo.h"

const char instrucoes[TOTALINSTRUCOES][NOMEINSTRUCAO] = {"ADD","SUB","MUL","DIV","MOD","AND","OR","NOT","MIR","POP","OUT","CLEAR","PUSH"};

void iniciaPrograma()
{
    char tecla;
    do
    {
        system("clear");

        printf("ARQUITETURA E ORGANIZACAO DE COMPUTADORES II\n");
        printf("\nSIMULADOR DE MAQUINA DE PILHA\n");
        printf("\nAndrei Pochmann Koenich\n");
        printf("\n----------------------------------------\n");

        abreArquivo();
        printf("\nPressione ESC para encerrar a execucao do programa.\n");
        printf("Pressione qualquer outra tecla para realizar uma nova leitura.\n");

        tecla = getch_();

    } while (tecla != ESC);
}

int main ()
{
    iniciaPrograma();
    return 0;
}