#include "../Headers/controleArquivo.h"

int controlaInstrucao(char linha[], NodoErro **ptrListaErros, int numeroLinha, int indiceInstrucao) /* Segunda verificacao da instrucao da linha. */
{
    int i = 0;
    char auxFrase[DIMENSAOLINHA];
    char instrucao[DIMENSAOLINHA];

    for (i = 0; linha[i] != '\0' && linha[i] != '\n' && linha[i] != COMENTARIO ; i++)
        auxFrase[i] = linha[i]; 

    auxFrase[i] = '\0';

    if (contaPalavras(auxFrase) > MAXTERMOS) 
    {
        insereErro(ptrListaErros,ERROSINTAXE,numeroLinha); 
        return -1;
    }

    int indiceAux = 0;

    for (i = 0; linha[i] != '\0' && linha[i] != '\n' && linha[i] != COMENTARIO ; i++) 
        if (linha[i] != ' ' && linha[i] != '\t'  && linha[i] != '\n')
        {
            instrucao[indiceAux] = linha[i]; 
            indiceAux++;
        }

    instrucao[indiceAux] = '\0';

    if (indiceInstrucao == INDICEPUSH) 
    {
        if (!strstr(linha,"PUSH ") && !strstr(linha,"PUSH\t"))
        {
            insereErro(ptrListaErros,ERROSINTAXE,numeroLinha); 
            return -1;
        }

        if (strncmp(instrucao,instrucoes[indiceInstrucao],strlen("PUSH")) != 0)
        {
            insereErro(ptrListaErros,ERROINVALIDA,numeroLinha); 
            return -1;
        }

        if (instrucao[4] == '$' && instrucao[5] == 'R') 
            return INDICEPUSH;

        int achou_argumento = 0;

        for(i = 4; instrucao[i] != '\0'; i++)
        {
            if (i == 4 && instrucao[i] == '-')
                continue;

            else if (!isdigit(instrucao[i]))
            {
                insereErro(ptrListaErros,ERROARGUMENTO,numeroLinha); 
                return -1;
            }

            if (instrucao[i] != '\0' && isdigit(instrucao[i]))
                achou_argumento = 1;
        }

        if (achou_argumento == 0)
        {
            insereErro(ptrListaErros,ERROSINTAXE,numeroLinha); 
            return -1;
        }
    }

    else
    {
        if (contaPalavras(auxFrase) > 1)
        {
            insereErro(ptrListaErros,ERROARGUMENTO,numeroLinha);  
            return -1;
        }

        else if (strcmp(instrucao,instrucoes[indiceInstrucao]) != 0)
        {
            insereErro(ptrListaErros,ERROINVALIDA,numeroLinha);  
            return -1;
        }
    }

    return indiceInstrucao; 
}

int verificaInstrucao(char linha[], NodoErro **ptrListaErros, int numeroLinha) /* Primeira verificacao da instrucao da linha. */
{
    int indiceInstrucao = -1;
    int numeroInstrucoes = 0;
    int possuiCaractere = 0;

    int i = 0;
    int indiceAux = 0;

    char aux[DIMENSAOLINHA];

    for (i = 0; linha[i] != '\0' && linha[i] != '\n' && linha[i] != COMENTARIO; i++)
    {
        if (linha[i] != '\t')
        {
             aux[indiceAux] = linha[i];
             indiceAux++;
        }

        if (isalpha(aux[i]) || isdigit(aux[i])) {
            possuiCaractere = 1; 
        }      
    }

    aux[indiceAux] = '\0';

    if (strlen(aux) == 0 || possuiCaractere == 0) 
        return -1;

    for (i = 0; i < TOTALINSTRUCOES; i++)
    {
        if (strstr(aux, instrucoes[i]))
        {
            indiceInstrucao = i; 
            numeroInstrucoes++;
        }

        else if(contaOcorrencias(instrucoes[i],aux) > 1) 
            numeroInstrucoes++;
    }

    if (numeroInstrucoes > 1 || indiceInstrucao == -1) 
    {  
        insereErro(ptrListaErros,ERROINVALIDA,numeroLinha);
        return -1;
    }

    indiceInstrucao = controlaInstrucao(linha,ptrListaErros,numeroLinha,indiceInstrucao);

    return indiceInstrucao; 
}

void leituraArquivo(FILE *arq) /* Realiza a leitura de todas as linhas do arquivo texto de entrada. */
{
    NodoPilha *ptrPilha = inicializaEstrutura(); 
    NodoErro *ptrListaErros = inicializaEstrutura(); 

    int R = 0; 
    int numeroLinha = 1;
    int indiceInstrucao = -1; 

    char linhaArquivo[DIMENSAOLINHA]; 

    while (!feof(arq)) 
    {
        fgets(linhaArquivo,DIMENSAOLINHA,arq); 

        indiceInstrucao = verificaInstrucao(linhaArquivo,&ptrListaErros,numeroLinha); 

        if(indiceInstrucao != INDICEPUSH && indiceInstrucao != -1) 
            realizaOperacao(&R,&ptrPilha,indiceInstrucao,&ptrListaErros,numeroLinha);

        else if (indiceInstrucao != -1) 
        {
            int totalNodos = dimensaoPilha(ptrPilha); 

            if (totalNodos >= TAMANHOPILHA) 
                insereErro(&ptrListaErros,ERROCHEIA,numeroLinha); 

            else 
                push(&ptrPilha,R,linhaArquivo);
        }

        numeroLinha++; 
        memset(linhaArquivo, 0, sizeof(linhaArquivo)); 
    }

    if (ptrListaErros != NULL)
    {
        system("clear"); 
        imprimeErros(ptrListaErros); 
    }

    destroiListaErros(ptrListaErros);
    destroiPilha(ptrPilha);

    printf("\n");
}

void abreArquivo() /* Abre e inicia a leitura do arquivo de entrada. */
{
    FILE *arq;
    char nomeArquivo[DIMENSAONOME];

    printf("\nDigite o nome do arquivo de entrada:\n"); 
    obtemNomeArquivo(nomeArquivo);
    system("clear");

    if (!(arq = fopen(nomeArquivo,"r"))) 
    {
        printf("Erro na abertura do arquivo texto de entrada. Fim do programa.\n");
        exit(1);
    }

    leituraArquivo(arq); 
    fclose(arq); 
}