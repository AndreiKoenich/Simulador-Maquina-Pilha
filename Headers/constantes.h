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
extern const char instrucoes[TOTALINSTRUCOES][NOMEINSTRUCAO];