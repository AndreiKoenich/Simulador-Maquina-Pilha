#ifndef GERAIS_H
#define GERAIS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <math.h>

#include "constantes.h"

char getch_();
void* inicializaEstrutura(); /* Inicializa uma lista simplesmente encadeada, que sera usada como uma pilha ou como uma lista de erros. */
int contaPalavras(char *frase); /* Conta quantas palavras uma frase possui. */
void obtemNomeArquivo(char* comando);  /* Funcao para obter o nome do arquivo digitado pelo usuario. */
int contaOcorrencias(const char palavra[], const char subpalavra[]); /* Determina quantas vezes uma subpalavra ocorre dentro de uma palavra. */
void converteComplemento2(int numero, int saida[]); /* Converte o numero para binario, em complemento de dois. */
int calculaDecimal(int n[]); /* Converte um numero binario em complemento de 2 para decimal. */

#endif