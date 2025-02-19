#ifndef LISTAS_H
#define LISTAS_H

#include <stdio.h>
#include <stdlib.h>
#include "estruturas.h"
#include "gerais.h"

int listaVazia (NodoErro *ptLista); /* Verifica se uma lista simplesmente encadeada e vazia. */
void insereErro (NodoErro **ptErro, int codigo, int linha); /* Insere o codigo de um erro e a linha onde ele ocorre, no final da lista. */
void imprimeErros(NodoErro *ptErros); /* Impressao de toda a lista de erros, utilizando comando iterativo. */
void destroiListaErros(NodoErro *ptrListaErros); /* Funcao para desalocar todo o espaco de memoria alocado pela lista de erros. */
#endif