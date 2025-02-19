#include "../Headers/pilha.h"

void insereTopo(NodoPilha **ptrPilha, int numero) /* Insere um numero no topo da pilha. */
{
    NodoPilha *novo;

    novo = (NodoPilha*)malloc(sizeof(NodoPilha));
    novo->n = numero;
    novo->prox = *ptrPilha;
    *ptrPilha = novo;
}

void clear(NodoPilha **ptrPilha) /* Remove todos os numero das pilha. */
{
    NodoPilha *ptaux;

    while (*ptrPilha != NULL) 
    {
        ptaux = *ptrPilha;
        *ptrPilha = (*ptrPilha)->prox;
        free(ptaux);
    }

    free(*ptrPilha);
}

void pop(NodoPilha **ptrPilha) /* Elimina o elemento no topo da pilha. */
{
    if (*ptrPilha == NULL) 
        return;

    NodoPilha *novo = (*ptrPilha)->prox; 

    free(*ptrPilha);
    *ptrPilha = novo;
}

int dimensaoPilha(NodoPilha *ptrPilha) /* Determina a quantidade de nodos da pilha. */
{
    NodoPilha *ptaux;
    int contador = 0;

    for (ptaux = ptrPilha; ptaux != NULL; ptaux = ptaux->prox)
        contador++; 

    return contador;
}

void adicao (int *R,NodoPilha **ptrPilha) /* Faz uma adicao entre os dois numeros no topo da pilha e armazena o resultado em R. */
{
    *R = (*ptrPilha)->n + (*ptrPilha)->prox->n;
}

void subtracao (int *R,NodoPilha **ptrPilha) /* Faz uma subtracao entre os dois numeros no topo da pilha e armazena o resultado em R. */
{
    *R = (*ptrPilha)->n - (*ptrPilha)->prox->n;
}

void multiplicacao (int *R,NodoPilha **ptrPilha) /* Faz uma multiplicacao entre os dois numeros no topo da pilha e armazena o resultado em R. */
{
    *R = (*ptrPilha)->n * (*ptrPilha)->prox->n;
}

void divisao(int *R,NodoPilha **ptrPilha, int numeroLinha) /* Faz uma divisao entre os dois numeros no topo da pilha e armazena o resultado em R. */
{
    if ((*ptrPilha)->prox->n == 0) /* Evita divisoes por zero. */
    {
        system("clear");
        printf("Divisao por zero ocorrida na linha %d. Fim do programa.\n", numeroLinha);
        exit(1); 
    }

    *R = (*ptrPilha)->n / (*ptrPilha)->prox->n;
}

void restoDivisao (int *R,NodoPilha **ptrPilha, int numeroLinha) /* Calcula o resto da divisao entre os dois numeros no topo da pilha e armazena o resultado em R. */
{
    if ((*ptrPilha)->prox->n == 0)
    {
        system("clear");
        printf("Operacao de resto de divisao com zero ocorrida na linha %d. Fim do programa.\n", numeroLinha);
        exit(1);
    }

    *R = (*ptrPilha)->n % (*ptrPilha)->prox->n;
}

void operacaoAnd(int *R, NodoPilha **ptrPilha) /* Realiza a operacao AND bit a bit com os operandos. */
{
    int n1 = (*ptrPilha)->n; 
    int n2 = (*ptrPilha)->prox->n;

    int v1[TOTALBITS], v2[TOTALBITS], saida[TOTALBITS]; 

    converteComplemento2(n1,v1); 
    converteComplemento2(n2,v2); 

    for (int i = 0; i < TOTALBITS; i++)
    {
        if (v1[i] == 0 || v2[i] == 0)
            saida[i] = 0;

        else
            saida[i] = 1;
    }

    *R = calculaDecimal(saida);
}

void operacaoOr(int *R, NodoPilha **ptrPilha) /* Realiza a operacao OR bit a bit com os operandos. */
{
    int n1 = (*ptrPilha)->n;
    int n2 = (*ptrPilha)->prox->n;

    int v1[TOTALBITS], v2[TOTALBITS], saida[TOTALBITS];

    converteComplemento2(n1,v1); 
    converteComplemento2(n2,v2);

    for (int i = 0; i < TOTALBITS; i++) 
    {
        if (v1[i] == 0 && v2[i] == 0)
            saida[i] = 0;

        else
            saida[i] = 1;
    }

    *R = calculaDecimal(saida);
}

void operacaoNot(int *R, NodoPilha **ptrPilha) /* Realiza a operacao NOT bit a bit com o operando. */
{
    int n1 = (*ptrPilha)->n; 
    int v1[TOTALBITS], saida[TOTALBITS];

    converteComplemento2(n1,v1); 

    for (int i = 0; i < TOTALBITS; i++) 
    {
        if (v1[i] == 0)
            saida[i] = 1;

        else if (v1[i] == 1)
            saida[i] = 0;
    }

    *R = calculaDecimal(saida); 
}

void operacaoMir(int *R, NodoPilha **ptrPilha) 
{
    int n1 = (*ptrPilha)->n; 

    int v1[TOTALBITS], saida[TOTALBITS]; 

    converteComplemento2(n1,v1);

    for (int i = TOTALBITS-1; i >= 0; i--) 
        saida[TOTALBITS-i-1] = v1[i];

    *R = calculaDecimal(saida); 
}

void push(NodoPilha **ptrPilha, int R, char linha[]) /* Obtem um novo numero e insere no topo da pilha. */
{
    int indice_numero = 0;
    char aux_numero[DIMENSAONUMERO];

    if (strstr(linha,NOMEREGISTRADOR)) 
        insereTopo(ptrPilha,R);

    else
    {
        for (int i = 0; linha[i] != '\0' && linha[i] != '\n' && linha[i] != COMENTARIO ; i++)
            if(isdigit(linha[i])) 
            {
                aux_numero[indice_numero] = linha[i];
                indice_numero++;
            }

        int valor = atoi(aux_numero);

        for (int i = 0; linha[i] != '\0' && linha[i] != '\n' && linha[i] != COMENTARIO ; i++)
            if(linha[i] == '-') 
                valor *= -1;

        insereTopo(ptrPilha,valor); 
    }
}

void realizaOperacao(int *R, NodoPilha **ptrPilha,int indiceInstrucao, NodoErro **ptrListaErros, int numeroLinha) /* Realiza a operacao a partir do indice determinado. */
{
    int totalNodos = dimensaoPilha(*ptrPilha); 

    if (indiceInstrucao >= INDICEADD && indiceInstrucao <= INDICEOR) 
    {
        if(totalNodos < 2)
        {
            insereErro(ptrListaErros,ERROINSUFICIENTE,numeroLinha); 
            return;
        }
    }

    else if (indiceInstrucao == INDICENOT || indiceInstrucao == INDICEMIR) 
    {
        if(totalNodos < 1)
        {
            insereErro(ptrListaErros,ERROINSUFICIENTE,numeroLinha); 
            return;
        }

        else if (totalNodos >= TAMANHOPILHA) 
        {
            insereErro(ptrListaErros,ERROCHEIA,numeroLinha);
            return;
        }
    }

    switch(indiceInstrucao) 
    {
        case INDICEADD:
            adicao(R,ptrPilha); 
        break;

        case INDICESUB:
            subtracao(R,ptrPilha);
        break;

        case INDICEMUL:
            multiplicacao(R,ptrPilha); 
        break;

        case INDICEDIV:
            divisao(R,ptrPilha, numeroLinha);
        break;

        case INDICEMOD:
            restoDivisao(R,ptrPilha,numeroLinha); 
        break;

        case INDICEAND:
            operacaoAnd(R,ptrPilha);
        break;

        case INDICEOR: 
            operacaoOr(R,ptrPilha);
        break;

        case INDICENOT: 
            operacaoNot(R,ptrPilha);
        break;

        case INDICEMIR:
            operacaoMir(R,ptrPilha);
        break;

        case INDICEPOP: 
        {
            if(totalNodos == 0)
                insereErro(ptrListaErros,ERROPOP,numeroLinha); 

            else
                pop(ptrPilha); 
        }
        break;

        case INDICEOUT:
        {
            if(totalNodos == 0)
                insereErro(ptrListaErros,ERROINSUFICIENTE,numeroLinha); 

            else
                printf("TOPO DA PILHA = %d\n", (*ptrPilha)->n); 
        }
        break;

        case INDICECLEAR:
            clear(ptrPilha);
        break;
    }
}

void destroiPilha(NodoPilha *ptrPilha) { /* Funcao para desalocar todo o espaco de memoria alocado pela lista de erros. */

    if (ptrPilha == NULL)
        return;

    NodoPilha *ptaux = ptrPilha;
    while (ptrPilha != NULL) {
        ptrPilha = ptrPilha->prox;
        free(ptaux);
        ptaux = ptrPilha;
    }
}