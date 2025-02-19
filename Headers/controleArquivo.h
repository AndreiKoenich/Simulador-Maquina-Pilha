#ifndef CONTROLEARQUIVO_H
#define CONTROLEARQUIVO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "pilha.h"
#include "estruturas.h"
#include "constantes.h"
#include "gerais.h"

int controlaInstrucao(char linha[], NodoErro **ptErros, int numeroLinha, int indiceInstrucao); /* Segunda verificacao da instrucao da linha. */
int verificaInstrucao(char linha[], NodoErro **ptErros, int numeroLinha); /* Primeira verificacao da instrucao da linha. */
void leituraArquivo(FILE *arq); /* Realiza a leitura de todas as linhas do arquivo texto de entrada. */
void abreArquivo(); /* Abre e inicia a leitura do arquivo de entrada. */

#endif 