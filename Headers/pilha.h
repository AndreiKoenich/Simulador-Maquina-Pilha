#ifndef PILHA_H
#define PILHA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "estruturas.h"
#include "constantes.h"
#include "gerais.h"
#include "listas.h"

void insereTopo(NodoPilha **ptPilha, int numero); /* Insere um numero no topo da pilha. */
void clear(NodoPilha **ptPilha); /* Remove todos os numero das pilha. */
void pop(NodoPilha **ptPilha); /* Elimina o elemento no topo da pilha. */
int dimensaoPilha(NodoPilha *ptPilha); /* Determina a quantidade de nodos da pilha. */
void adicao (int *R,NodoPilha **ptPilha); /* Faz uma adicao entre os dois numeros no topo da pilha e armazena o resultado em R. */
void subtracao (int *R,NodoPilha **ptPilha); /* Faz uma subtracao entre os dois numeros no topo da pilha e armazena o resultado em R. */
void multiplicacao (int *R,NodoPilha **ptPilha); /* Faz uma multiplicacao entre os dois numeros no topo da pilha e armazena o resultado em R. */
void divisao(int *R,NodoPilha **ptPilha, int numeroLinha); /* Faz uma divisao entre os dois numeros no topo da pilha e armazena o resultado em R. */
void restoDivisao (int *R,NodoPilha **ptPilha, int numeroLinha); /* Calcula o resto da divisao entre os dois numeros no topo da pilha e armazena o resultado em R. */
void operacaoAnd(int *R, NodoPilha **ptPilha); /* Realiza a operacao AND bit a bit com os operandos. */
void operacaoOr(int *R, NodoPilha **ptPilha); /* Realiza a operacao OR bit a bit com os operandos. */
void operacaoNot(int *R, NodoPilha **ptPilha); /* Realiza a operacao NOT bit a bit com o operando. */
void operacaoMir(int *R, NodoPilha **ptPilha); /* Realiza a operacao MIR com o operando. */
void push(NodoPilha **ptPilha, int R, char linha[]); /* Obtem um novo numero e insere no topo da pilha. */
void realizaOperacao(int *R, NodoPilha **ptPilha,int indiceInstrucao, NodoErro **ptErros, int numeroLinha); /* Realiza a operacao a partir do indice determinado. */
void realizaOperacao(int *R, NodoPilha **ptPilha,int indiceInstrucao, NodoErro **ptErros, int numeroLinha); /* Realiza a operacao a partir do indice determinado. */
void destroiListaErros(NodoErro *ptrListaErros); /* Funcao para desalocar todo o espaco de memoria alocado pela lista de erros. */
void destroiPilha(NodoPilha *ptrPilha); /* Funcao para desalocar todo o espaco de memoria alocado pela lista de erros. */

#endif