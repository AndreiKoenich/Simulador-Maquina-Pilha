#include "../Headers/gerais.h"

char getch_()
{
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if(tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if(tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if(read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if(tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return buf;
 }

 void* inicializaEstrutura() /* Inicializa uma lista simplesmente encadeada, que sera usada como uma pilha ou como uma lista de erros. */
{
    return NULL;
}

 int contaPalavras(char *frase) /* Conta quantas palavras uma frase possui. */
{
    int estado = 0;
    int contador_palavras = 0;

    while (*frase) 
    {
        if (*frase == ' ' || *frase == '\n' || *frase == '\t')
            estado = 0;

        else if (estado == 0)
        {
            estado = 1;
            contador_palavras++;
        }

        frase++;
    }

    return contador_palavras; 
}

 /* Funcao para obter o nome do arquivo digitado pelo usuario. */
 void obtemNomeArquivo(char* comando) {
    fgets(comando, DIMENSAONOME, stdin);

    size_t len = strlen(comando);
    if (len > 0 && comando[len - 1] == '\n')
        comando[len - 1] = '\0';
}

int contaOcorrencias(const char palavra[], const char subpalavra[]) /* Determina quantas vezes uma subpalavra ocorre dentro de uma palavra. */
{
    int contador = 0;
    int j;

    for (int i = 0; palavra[i] != '\0'; i++)
    {
        for (j = 0; subpalavra[j] != '\0' && subpalavra[j] == palavra[i+j]; j++);

        if (subpalavra[j] == '\0')
            contador++; 
    }

    return contador; 
}

void converteComplemento2(int numero, int saida[]) /* Converte o numero para binario, em complemento de dois. */
{
    for(int i = 0; i < TOTALBITS; i++)
    {
        unsigned int mask = 1u << (TOTALBITS - 1 - i);
        saida[i] = (numero & mask) ? 1 : 0;
    }
}

int calculaDecimal(int n[]) /* Converte um numero binario em complemento de 2 para decimal. */
{
    int decimal = 0;
    int posicao = 0;

    for (int i = TOTALBITS-1; i >= 0; i--) 
    {
        decimal += n[i]*pow(2,posicao);
        posicao++;
    }

    if (n[0] == 1)
        return -1*(MAXINTEIRO16BITS - decimal);

    else 
        return decimal;
}