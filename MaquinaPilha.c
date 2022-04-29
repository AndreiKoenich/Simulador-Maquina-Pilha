/* ARQUITETURA E ORGANIZACAO DE COMPUTADORES II - SIMULADOR DE MAQUINA DE PILHA.

Autor: Andrei Pochmann Koenich

O programa a seguir simula uma arquitetura computacional baseada em uma maquina de pilha. O programa recebe do usuario
via teclado um arquivo texto, contendo outro programa escrito com o assembly da maquina, e retorna na saida os resultados
esperados por meio da execucao das instrucoes do arquivo de entrada. Caso o arquivo texto de entrada possua instrucoes
invalidas, o programa indica quais linhas contem essas instrucoes e qual o erro especifico. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <math.h>

#define TOTALBITS 16 /* Numero de bits de cada palavra da pilha. */

#define DIMENSAONOME 100
#define DIMENSAONUMERO 30
#define DIMENSAOLINHA 1000

#define TOTALINSTRUCOES 13
#define NOMEINSTRUCAO 6

#define MAXINTEIRO16BITS 65536 /* Sucessor do maior valor em 16 bits. */

#define MAXTERMOS 2      /* Numero maximo de palavras validas por linha. */
#define TAMANHOPILHA 128 /* Tamanho da pilha. */

#define INDICEADD 0 /* Constantes que representam os indices das treze operacoes. */
#define INDICESUB 1
#define INDICEMUL 2
#define INDICEDIV 3
#define INDICEMOD 4
#define INDICEAND 5
#define INDICEOR 6
#define INDICENOT 7
#define INDICEMIR 8
#define INDICEPOP 9
#define INDICEOUT 10
#define INDICECLEAR 11
#define INDICEPUSH 12

#define ERROSINTAXE 0 /* Constantes que representam o codigo de cada erro, durante a leitura. */
#define ERROINVALIDA 1
#define ERROARGUMENTO 2
#define ERROPOP 3
#define ERROCHEIA 4
#define ERROINSUFICIENTE 5

#define NOMEREGISTRADOR "$R"
#define COMENTARIO ';'

#define ESC 27

/* Vetor de strings constante, contendo todas as operacoes. */
const char instrucoes[TOTALINSTRUCOES][NOMEINSTRUCAO] = {"ADD","SUB","MUL","DIV","MOD","AND","OR","NOT","MIR","POP","OUT","CLEAR","PUSH"};

typedef struct nodo_pilha /* Estrutura de cada nodo da pilha. */
{
    int n;

    struct nodo_pilha *prox;

} NODO_PILHA;

typedef struct nodo_erro /* Estrutura de cada nodo da lista de erros. */
{
    int codigo;
    int linha;
    struct nodo_erro *prox;

} NODO_ERRO;

void* inicializa_lista() /* Inicializa uma lista simplesmente encadeada, que sera usada como uma pilha ou como uma lista. */
{
    return NULL;
}

int conta_palavras(char *frase) /* Conta quantas palavras uma frase possui. */
{
    int estado = 0;
    int contador_palavras = 0;

    while (*frase) /* Iteracao para percorrer todos os caracteres da frase. */
    {
        if (*frase == ' ' || *frase == '\n' || *frase == '\t')
            estado = 0;

        else if (estado == 0)
        {
            estado = 1;
            contador_palavras++;
        }

        frase++; /* Avanca nos caracteres da frase. */
    }

    return contador_palavras; /* Retorna a quantidade de palavras da frase. */
}

int lista_vazia (NODO_ERRO *ptLista) /* Verifica se uma lista simplesmente encadeada. */
{
    if (ptLista == NULL)
        return 1; /* Retorna 1, indicando que a lista esta vazia. */

    else
        return 0; /* Retorna 0, indicando que a lista nao esta vazia. */
}

void insereTopo(NODO_PILHA **ptPilha, int numero) /* Insere um numero no topo da pilha. */
{
    NODO_PILHA *novo;

    novo = (NODO_PILHA*)malloc(sizeof(NODO_PILHA));
    novo->n = numero;
    novo->prox = *ptPilha;
    *ptPilha = novo;
}

void clear(NODO_PILHA **ptPilha) /* Remove todos os numero das pilha. */
{
    NODO_PILHA *ptaux;

    while (*ptPilha != NULL) /* Iteracao para percorrer toda a pilha e remover cada nodo. */
    {
        ptaux = *ptPilha;
        *ptPilha = (*ptPilha)->prox;
        free(ptaux);
    }

    free(*ptPilha);
}

void pop(NODO_PILHA **ptPilha) /* Elimina o elemento no topo da pilha. */
{
    if (*ptPilha == NULL) /* Verficia se a pilha esta vazia. */
        return;

    NODO_PILHA *novo = (*ptPilha)->prox; /* Atualiza o ponteiro do inicio da pilha. */

    free(*ptPilha);
    *ptPilha = novo;
}

int dimensao_pilha(NODO_PILHA *ptPilha) /* Determina a quantidade de nodos da pilha. */
{
    NODO_PILHA *ptaux;
    int contador = 0;

    for (ptaux = ptPilha; ptaux != NULL; ptaux = ptaux->prox)
        contador++; /* Percorre a estrutura e incrementa o contador. */

    return contador; /* Retorna a quantidade de nodos da pilha. */
}

void insereErro (NODO_ERRO **ptErro, int codigo, int linha) /* Insere o codigo de um erro e a linha onde ele ocorre, no final da lista. */
{
    NODO_ERRO *novo;
    NODO_ERRO *ptaux = *ptErro;

    novo = (NODO_ERRO*) malloc (sizeof(NODO_ERRO));
    novo->codigo = codigo;
    novo->linha = linha;
    novo->prox = NULL;

    if (ptaux != NULL) /* Percorre a lista ate o final, para inserir o novo nodo. */
    {
        for (ptaux = *ptErro; ptaux->prox != NULL; ptaux = ptaux->prox);

        ptaux->prox = novo;
    }

    else /* Casos em que a lista esta vazia. */
        *ptErro = novo;
}

int conta_ocorrencias(const char palavra[], const char subpalavra[]) /* Determina quantas vezes uma subpalavra ocorre dentro de uma palavra. */
{
    int contador = 0;
    int j;

    for (int i = 0; palavra[i] != '\0'; i++) /* Iteracao para percorrer todos os caracteres da palavra. */
    {
        for (j = 0; subpalavra[j] != '\0' && subpalavra[j] == palavra[i+j]; j++);

        if (subpalavra[j] == '\0')
            contador++; /* Incrementa o contador de vezes em que a subpalavra aparece. */
    }

    return contador; /* Retorna o numero de vezes em que a subpalavra aparece. */
}

void converte_comp2(int numero, int saida[]) /* Converte o numero para binario, em complemento de dois. */
{
    for(int i = 0; i < TOTALBITS; i++)
    {
        unsigned int mask = 1u << (TOTALBITS - 1 - i);
        saida[i] = (numero & mask) ? 1 : 0; /* Determina os bits no vetor de saida. */
    }
}

int calcula_decimal(int n[]) /* Converte um numero binario em complemento de 2 para decimal. */
{
    int decimal = 0;
    int posicao = 0;

    for (int i = TOTALBITS-1; i >= 0; i--) /* Conversao para decimal usando o metodo polinomial. */
    {
        decimal += n[i]*pow(2,posicao);
        posicao++;
    }

    if (n[0] == 1) /* Faz o complemento do numero, caso o numero seja negativo. */
        return -1*(MAXINTEIRO16BITS - decimal);

    else /* Retorna o numero sem realizar o complemento. */
        return decimal;
}

int controla_instrucao(char linha[], NODO_ERRO **ptErros, int numero_linha, int indice_instrucao) /* Segunda verificacao da instrucao da linha. */
{
    int i = 0;
    char aux_frase[DIMENSAOLINHA];
    char instrucao[DIMENSAOLINHA];

    for (i = 0; linha[i] != '\0' && linha[i] != '\n' && linha[i] != COMENTARIO ; i++)
        aux_frase[i] = linha[i]; /* Armazena somente caracteres validos na string auxiliar, para analise. */

    aux_frase[i] = '\0';

    if (conta_palavras(aux_frase) > MAXTERMOS) /* Acusa erro se a frase da linha possui mais de duas palavras. */
    {
        insereErro(ptErros,ERROSINTAXE,numero_linha); /* Acusa erro de sintaxe. */
        return -1;
    }

    int indice_aux = 0;

    for (i = 0; linha[i] != '\0' && linha[i] != '\n' && linha[i] != COMENTARIO ; i++) /* Iteracao para obter o nome exato da instrucao a ser executada. */
        if (linha[i] != ' ' && linha[i] != '\t')
        {
            instrucao[indice_aux] = linha[i]; /* Obtem o nome exato da instrucao. */
            indice_aux++;
        }

    instrucao[indice_aux] = '\0';

    if (indice_instrucao == INDICEPUSH) /* Controle dos casos em que a instrucao PUSH sera executada, para validacao de operando. */
    {
        if (!strstr(linha,"PUSH ") && !strstr(linha,"PUSH\t"))
        {
            insereErro(ptErros,ERROSINTAXE,numero_linha); /* Caso de erro de sintaxe. */
            return -1;
        }

        if (strncmp(instrucao,instrucoes[indice_instrucao],strlen("PUSH")) != 0)
        {
            insereErro(ptErros,ERROINVALIDA,numero_linha); /* Caso de instrucao invalida. */
            return -1;
        }

        if (instrucao[4] == '$' && instrucao[5] == 'R') /* Verifica se o parametro e o proprio registrador. */
            return INDICEPUSH;

        int achou_argumento = 0;

        for(i = 4; instrucao[i] != '\0'; i++)
        {
            if (i == 4 && instrucao[i] == '-')
                continue;

            else if (!isdigit(instrucao[i]))
            {
                insereErro(ptErros,ERROARGUMENTO,numero_linha); /* Argumento invalido para instrucao PUSH. */
                return -1;
            }

            if (instrucao[i] != '\0' && isdigit(instrucao[i]))
                achou_argumento = 1;
        }

        if (achou_argumento == 0)
        {
            insereErro(ptErros,ERROSINTAXE,numero_linha); /* Argumento invalido para instrucao PUSH. */
            return -1;
        }
    }

    else
    {
        if (conta_palavras(aux_frase) > 1)
        {
            insereErro(ptErros,ERROARGUMENTO,numero_linha);  /* Acusa argumento invalido para outras instrucoes. */
            return -1;
        }

        else if (strcmp(instrucao,instrucoes[indice_instrucao]) != 0)
        {
            insereErro(ptErros,ERROINVALIDA,numero_linha);  /* Acusa argumento invalido para outras instrucoes. */
            return -1;
        }
    }

    return indice_instrucao; /* Caso a instrucao seja totalmente valida, retorna seu indice. */
}

int verifica_instrucao(char linha[], NODO_ERRO **ptErros, int numero_linha) /* Primeira verificacao da instrucao da linha. */
{
    int indice_instrucao = -1;
    int numero_instrucoes = 0;
    int possui_caractere = 0;

    int i = 0;
    int indice_aux = 0;

    char aux[DIMENSAOLINHA];

    for (i = 0; linha[i] != '\0' && linha[i] != '\n' && linha[i] != COMENTARIO; i++)
    {
        if (linha[i] != '\t')
        {
             aux[indice_aux] = linha[i];
             indice_aux++;
        }

        if (aux[i] != ' ')
            possui_caractere = 1; /* Indica que a linha possui caractere. */
    }

    aux[indice_aux] = '\0';

    if (strlen(aux) == 0 || possui_caractere == 0) /* Casos em que a linha nao esta errada, mas nao possui instrucoes. */
        return -1;

    for (i = 0; i < TOTALINSTRUCOES; i++)
    {
        if (strstr(aux, instrucoes[i]))
        {
            indice_instrucao = i; /* Salva o codigo da instrucao a ser executada. */
            numero_instrucoes++;
        }

        else if(conta_ocorrencias(instrucoes[i],aux) > 1) /* Verifica se a mesma instrucao aparece mais de uma vez na linha (erro). */
            numero_instrucoes++;
    }

    if (numero_instrucoes > 1 || indice_instrucao == -1) /* Acusa erro de sintaxe. */
    {
        insereErro(ptErros,ERROINVALIDA,numero_linha);
        return -1;
    }

    indice_instrucao = controla_instrucao(linha,ptErros,numero_linha,indice_instrucao);

    return indice_instrucao; /* Retorna o codigo da instrucao, que sera -1 caso a linha nao contenha instrucao valida. */
}

void imprime_erros(NODO_ERRO *ptErros) /* Impressao de toda a lista de erros, utilizando comando iterativo. */
{
    NODO_ERRO *ptaux;

    printf("ERROS:\n\n");

    for (ptaux = ptErros; ptaux != NULL; ptaux = ptaux->prox) /* Iteracao usada na impressao. */
    {
        if (ptaux != NULL)
        {
            switch(ptaux->codigo) /* Analisa o codigo do erro de cada nodo da lista de erros, e imprime acusando a linha e o erro. */
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

void adicao (int *R,NODO_PILHA **ptPilha) /* Faz uma adicao entre os dois numeros no topo da pilha e armazena o resultado em R. */
{
    *R = (*ptPilha)->n + (*ptPilha)->prox->n;
}

void subtracao (int *R,NODO_PILHA **ptPilha) /* Faz uma subtracao entre os dois numeros no topo da pilha e armazena o resultado em R. */
{
    *R = (*ptPilha)->n - (*ptPilha)->prox->n;
}

void multiplicacao (int *R,NODO_PILHA **ptPilha) /* Faz uma multiplicacao entre os dois numeros no topo da pilha e armazena o resultado em R. */
{
    *R = (*ptPilha)->n * (*ptPilha)->prox->n;
}

void divisao(int *R,NODO_PILHA **ptPilha, int numero_linha) /* Faz uma divisao entre os dois numeros no topo da pilha e armazena o resultado em R. */
{
    if ((*ptPilha)->prox->n == 0) /* Evita divisoes por zero. */
    {
        system("cls");
        printf("Divisao por zero ocorrida na linha %d. Fim do programa.\n", numero_linha);
        getch();
        exit(1); /* Encerra a execucao do programa, retornando 1. */
    }

    *R = (*ptPilha)->n / (*ptPilha)->prox->n;
}

void resto_divisao (int *R,NODO_PILHA **ptPilha, int numero_linha) /* Calcula o resto da divisao entre os dois numeros no topo da pilha e armazena o resultado em R. */
{
    if ((*ptPilha)->prox->n == 0) /* Evita divisoes por zero. */
    {
        system("cls");
        printf("Operacao de resto de divisao com zero ocorrida na linha %d. Fim do programa.\n", numero_linha);
        getch();
        exit(1); /* Encerra a execucao do programa, retornando 1. */
    }

    *R = (*ptPilha)->n % (*ptPilha)->prox->n;
}

void operacao_and(int *R, NODO_PILHA **ptPilha) /* Realiza a operacao AND bit a bit com os operandos. */
{
    int n1 = (*ptPilha)->n; /* Obtem os valores do topo da pilha. */
    int n2 = (*ptPilha)->prox->n;

    int v1[TOTALBITS], v2[TOTALBITS], saida[TOTALBITS]; /* Vetores para conter os operandos e o resultado em binario, complemento de dois. */

    converte_comp2(n1,v1); /* Converte o operando 1 para binario em complemento de dois. */
    converte_comp2(n2,v2); /* Converte o operando 2 para binario em complemento de dois. */

    for (int i = 0; i < TOTALBITS; i++) /* Realiza a operacao AND bit a bit. */
    {
        if (v1[i] == 0 || v2[i] == 0)
            saida[i] = 0;

        else
            saida[i] = 1;
    }

    *R = calcula_decimal(saida); /* Armazena o resultado no registrador $R. */
}

void operacao_or(int *R, NODO_PILHA **ptPilha) /* Realiza a operacao OR bit a bit com os operandos. */
{
    int n1 = (*ptPilha)->n; /* Obtem os valores do topo da pilha. */
    int n2 = (*ptPilha)->prox->n;

    int v1[TOTALBITS], v2[TOTALBITS], saida[TOTALBITS]; /* Vetores para conter os operandos e o resultado em binario, complemento de dois. */

    converte_comp2(n1,v1); /* Converte o operando 1 para binario em complemento de dois. */
    converte_comp2(n2,v2); /* Converte o operando 2 para binario em complemento de dois. */

    for (int i = 0; i < TOTALBITS; i++) /* Calcula a operacao OR bit a bit. */
    {
        if (v1[i] == 0 && v2[i] == 0)
            saida[i] = 0;

        else
            saida[i] = 1;
    }

    *R = calcula_decimal(saida); /* Armazena o resultado no registrador $R. */
}

void operacao_not(int *R, NODO_PILHA **ptPilha) /* Realiza a operacao NOT bit a bit com o operando. */
{
    int n1 = (*ptPilha)->n; /* Obtem o valor do topo da pilha. */

    int v1[TOTALBITS], saida[TOTALBITS]; /* Vetores para conter o operando e o resultado em binario, complemento de dois. */

    converte_comp2(n1,v1); /* Converte o operando para binario em complemento de dois. */

    for (int i = 0; i < TOTALBITS; i++) /* Realiza a operacao NOT bit a bit. */
    {
        if (v1[i] == 0)
            saida[i] = 1;

        else if (v1[i] == 1)
            saida[i] = 0;
    }

    *R = calcula_decimal(saida); /* Armazena o resultado no registrador $R. */
}

void operacao_mir(int *R, NODO_PILHA **ptPilha) /* Realiza a operacao MIR com o operando. */
{
    int n1 = (*ptPilha)->n; /* Obtem o valor do topo da pilha. */

    int v1[TOTALBITS], saida[TOTALBITS], aux[TOTALBITS]; /* Vetores para conter o operando e o resultado em binario, complemento de dois. */

    converte_comp2(n1,v1); /* Converte o operando para binario em complemento de dois. */

    for (int i = TOTALBITS-1; i >= 0; i--) /* Inverte os bits do operando. */
        saida[TOTALBITS-i-1] = v1[i];

    *R = calcula_decimal(saida); /* Armazena o resultado no registrador $R. */
}

void push(NODO_PILHA **ptPilha, int R, char linha[]) /* Obtem um novo numero e insere no topo da pilha. */
{
    int indice_numero = 0;
    char aux_numero[DIMENSAONUMERO];

    if (strstr(linha,NOMEREGISTRADOR)) /* Verifica se o parametro da funcao push e o proprio registrador. */
        insereTopo(ptPilha,R);

    else /* Casos em que o parametro do push e um numero. */
    {
        for (int i = 0; linha[i] != '\0' && linha[i] != '\n' && linha[i] != COMENTARIO ; i++)
            if(isdigit(linha[i])) /* Obtem o numero a partir da string que representa a linha. */
            {
                aux_numero[indice_numero] = linha[i];
                indice_numero++;
            }

        int valor = atoi(aux_numero); /* Converte a string em numero. */

        for (int i = 0; linha[i] != '\0' && linha[i] != '\n' && linha[i] != COMENTARIO ; i++)
            if(linha[i] == '-') /* Verifica se o numero do parametro e negativo. */
                valor *= -1;

        insereTopo(ptPilha,valor); /* Insere o novo numero no topo da pilha. */
    }
}

void realiza_operacao(int *R, NODO_PILHA **ptPilha,int indice_instrucao, NODO_ERRO **ptErros, int numero_linha) /* Realiza a operacao a partir do indice determinado. */
{
    int total_nodos = dimensao_pilha(*ptPilha); /* Verifica o numero de nodos existentes na pilha. */

    if (indice_instrucao >= INDICEADD && indice_instrucao <= INDICEOR) /* Controle dos casos em que o numero de nodos e insuficiente para as operacoes. */
    {
        if(total_nodos < 2)
        {
            insereErro(ptErros,ERROINSUFICIENTE,numero_linha); /* Acusa quantidade de elementos insuficientes na pilha. */
            return;
        }
    }

    else if (indice_instrucao == INDICENOT || indice_instrucao == INDICEMIR) /* Controle dos casos em que o numero de nodos e insuficiente para as operacoes. */
    {
        if(total_nodos < 1)
        {
            insereErro(ptErros,ERROINSUFICIENTE,numero_linha); /* Acusa quantidade de elementos insuficientes na pilha. */
            return;
        }

        else if (total_nodos >= TAMANHOPILHA) /* Controle dos casos em que o numero de nodos da pilha ultrapassa o valor maximo. */
        {
            insereErro(ptErros,ERROCHEIA,numero_linha); /* Acusa pilha cheia. */
            return;
        }
    }

    switch(indice_instrucao) /* Verifica qual operacao sera executada, com base no indice da operacao. */
    {
        case INDICEADD:
            adicao(R,ptPilha); /* Soma os dois numeros no topo da pilha e retorna o valor no registrador &R. */
        break;

        case INDICESUB:
            subtracao(R,ptPilha); /* Subtrai os dois numeros no topo da pilha e retorna o valor no registrador &R. */
        break;

        case INDICEMUL:
            multiplicacao(R,ptPilha); /* Multiplica os dois numeros no topo da pilha e retorna o valor no registrador &R. */
        break;

        case INDICEDIV:
            divisao(R,ptPilha, numero_linha); /* Divide os dois numeros no topo da pilha e retorna o valor no registrador &R. */
        break;

        case INDICEMOD:
            resto_divisao(R,ptPilha,numero_linha); /* Calcula o resto da divisao entre os dois numeros no topo da pilha e retorna o valor no registrador &R. */
        break;

        case INDICEAND: /* Faz a operacao logica AND com os dois numeros do topo da pilha e retorna o valor no registrador &R. */
            operacao_and(R,ptPilha);
        break;

        case INDICEOR: /* Faz a operacao logica OR com os dois numeros do topo da pilha e retorna o valor no registrador $R. */
            operacao_or(R,ptPilha);
        break;

        case INDICENOT: /* Faz a operacao logica NOT com o numero no topo da pilha e retorna o valor no registrador $R. */
            operacao_not(R,ptPilha);
        break;

        case INDICEMIR: /* Faz a operacao logica MIR (inversao da ordem de bits) com o numero no topo da pilha e retorna o valor no registrador $R. */
            operacao_mir(R,ptPilha);
        break;

        case INDICEPOP: /* Remove o nodo no topo da pilha. */
        {
            if(total_nodos == 0)
                insereErro(ptErros,ERROPOP,numero_linha); /* Acusa tentativa de POP em pilha vazia. */

            else
                pop(ptPilha); /* Remove o nodo no topo da pilha. */
        }
        break;

        case INDICEOUT:
        {
            if(total_nodos == 0)
                insereErro(ptErros,ERROINSUFICIENTE,numero_linha); /* Acusa tentativa de POP em pilha vazia. */

            else
                printf("TOPO DA PILHA = %d\n", (*ptPilha)->n); /* Imprime o conteudo do topo da pilha. */
        }
        break;

        case INDICECLEAR:
            clear(ptPilha); /* Remove todos os nodos da pilha. */
        break;
    }
}

void leitura_arquivo(FILE *arq) /* Realiza a leitura de todas as linhas do arquivo texto de entrada. */
{
    NODO_PILHA *ptPilha = inicializa_lista(); /* Inicializa a pilha que ira conter os numeros. */
    NODO_ERRO *ptErros = inicializa_lista(); /* Inicializa a lista que ira conter o codigo e a linha de ocorrencia dos erros. */

    int R = 0; /* Inicializa o registrado $R. */
    int numero_linha = 1;
    int indice_instrucao = -1; /* Inicializa o indice da instrucao, que sera calculado em cada linha. */

    char linha_arquivo[DIMENSAOLINHA]; /* String auxiliar para conter o conteudo de cada linha. */

    while (!feof(arq)) /* Iteracao para percorrer o arquivo do inicio ao fim. */
    {
        fgets(linha_arquivo,DIMENSAOLINHA,arq); /* Realiza a leitura de cada linha do arquivo texto de entrada. */

        indice_instrucao = verifica_instrucao(linha_arquivo,&ptErros,numero_linha); /* Verifica se a linha possui instrucao valida. */

        if(indice_instrucao != INDICEPUSH && indice_instrucao != -1) /* Realiza alguma operacao diferente de PUSH, caso tenha sido encontrada na linha. */
            realiza_operacao(&R,&ptPilha,indice_instrucao,&ptErros,numero_linha);

        else if (indice_instrucao != -1) /* Realiza a instrucao PUSH, unica que recebe um operando. */
        {
            int total_nodos = dimensao_pilha(ptPilha); /* Calcula o numero de nodos da pilha. */

            if (total_nodos >= TAMANHOPILHA) /* Controle dos casos de PUSH em pilha cheia. */
                insereErro(&ptErros,ERROCHEIA,numero_linha); /* Acusa erro de PUSH em pilha cheia. */

            else /* Realiza a operacao de PUSH, caso a pilha nao esteja cheia. */
                push(&ptPilha,R,linha_arquivo);
        }

        numero_linha++; /* Incrementa o contador do numero da linha a cada iteracao. */
        memset(linha_arquivo, 0, sizeof(linha_arquivo)); /* Reinicia todo o array de caracteres da linha antes da proxima iteracao. */
    }

    if (ptErros != NULL)
    {
        system("cls"); /* Limpa a tela para mostrar os erros (programa incorreto). */
        imprime_erros(ptErros); /* Mostra todos os erros, acusando a linha de ocorrencia de cada um deles. */
    }

    printf("\n");
}

void abre_arquivo() /* Abre e inicia a leitura do arquivo de entrada. */
{
    FILE *arq;
    char nome_arquivo[DIMENSAONOME];

    printf("\nDigite o nome do arquivo de entrada:\n"); /* Obtem o nome do arquivo de entrada do usuario. */
    gets(nome_arquivo);
    system("cls");

    if (!(arq = fopen(nome_arquivo,"r"))) /* Controle dos casos em que nao e possivel abrir o arquivo de entrada. */
    {
        printf("Erro na abertura do arquivo texto de entrada. Fim do programa.\n");
        getch();
        exit(1);
    }

    leitura_arquivo(arq); /* Realiza a leitura de todas as linhas do arquivo texto de entrada. */
    fclose(arq); /* Fecha o arquivo de entrada. */
}

void inicia_programa()
{
    char tecla;

    do
    {
        printf("ARQUITETURA E ORGANIZACAO DE COMPUTADORES II\n");
        printf("\nSIMULADOR DE MAQUINA DE PILHA\n");
        printf("\nAndrei Pochmann Koenich\n");
        printf("\n----------------------------------------\n");

        abre_arquivo(); /* Abre e inicia a leitura do arquivo de entrada. */
        printf("\nPressione ESC para encerrar a execucao do programa.\n");
        printf("Pressione qualquer outra tecla para realizar uma nova leitura.\n");

        tecla = getch();
        system("cls");

    } while (tecla != ESC);
}

int main ()
{
    inicia_programa();
    system("pause");
    return 0;
}
