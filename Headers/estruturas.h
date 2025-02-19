#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

typedef struct NodoPilha /* Estrutura de cada nodo da pilha. */
{
    int n;
    struct NodoPilha *prox;

} NodoPilha;

typedef struct NodoErro /* Estrutura de cada nodo da lista de erros. */
{
    int codigo;
    int linha;
    struct NodoErro *prox;

} NodoErro;

#endif