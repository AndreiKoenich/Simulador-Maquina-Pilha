# ARQUITETURA E ORGANIZAÇÃO DE COMPUTADORES II

# SIMULADOR DE MÁQUINA DE PILHA

# AUTOR: Andrei Pochmann Koenich

# Makefile

# Variáveis de flags de compilação e de diretórios
FLAGS := -g -fsanitize=address -Wall -o

SOURCES := 	Sources/main.c \
			Sources/pilha.c \
			Sources/gerais.c \
			Sources/listas.c \
			Sources/controleArquivo.c


# Comando para linkar os arquivos compilados e gerar o executável
link: 
	gcc $(FLAGS) maquinaPilha $(SOURCES) -lm

# Comando padrão do Makefile
.DEFAULT_GOAL := link
