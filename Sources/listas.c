#include "../Headers/listas.h"

int listaVazia (NodoErro *ptLista) /* Verifica se uma lista simplesmente encadeada e vazia. */
{
    if (ptLista == NULL)
        return 1;

    else
        return 0; 
}

void insereErro (NodoErro **ptErro, int codigo, int linha) /* Insere o codigo de um erro e a linha onde ele ocorre, no final da lista. */
{
    NodoErro *novo;
    NodoErro *ptaux = *ptErro;

    novo = (NodoErro*) malloc (sizeof(NodoErro));
    novo->codigo = codigo;
    novo->linha = linha;
    novo->prox = NULL;

    if (ptaux != NULL) 
    {
        for (ptaux = *ptErro; ptaux->prox != NULL; ptaux = ptaux->prox);

        ptaux->prox = novo;
    }

    else 
        *ptErro = novo;
}

void imprimeErros(NodoErro *ptrListaErros) /* Impressao de toda a lista de erros, utilizando comando iterativo. */
{
    NodoErro *ptaux;

    printf("ERROS:\n\n");

    for (ptaux = ptrListaErros; ptaux != NULL; ptaux = ptaux->prox) 
    {
        if (ptaux != NULL)
        {
            switch(ptaux->codigo) 
            {
                case ERROSINTAXE:
                    printf("Linha %d - Erro de sintaxe. As instrucoes devem possuir zero ou um operandos.\n", ptaux->linha);
                break;

                case ERROINVALIDA:
                    printf("Linha %d - Instrucao invalida.\n", ptaux->linha);
                break;

                case ERROARGUMENTO:
                    printf("Linha %d - Argumento invalido para instrucao.\n", ptaux->linha);
                break;

                case ERROPOP:
                    printf("Linha %d - POP em pilha vazia.\n", ptaux->linha);
                break;

                case ERROCHEIA:
                    printf("Linha %d - PUSH em pilha cheia.\n", ptaux->linha);
                break;

                case ERROINSUFICIENTE:
                    printf("Linha %d - Pilha com elementos insuficientes para a instrucao.\n", ptaux->linha);
                break;
            }
        }
    }
}

void destroiListaErros(NodoErro *ptrListaErros) {

    if (ptrListaErros == NULL)
        return;

    NodoErro *ptaux = ptrListaErros;
    while (ptrListaErros != NULL) {
        ptrListaErros = ptrListaErros->prox;
        free(ptaux);
        ptaux = ptrListaErros;
    }
}