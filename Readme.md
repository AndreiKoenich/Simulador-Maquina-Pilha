ARQUITETURA E ORGANIZACAO DE COMPUTADORES II - SIMULADOR DE MAQUINA DE PILHA

Autor: Andrei Pochmann Koenich

Este programa simula uma arquitetura computacional baseada em uma máquina de pilha. O programa recebe do usuário
via teclado um arquivo texto, contendo outro programa escrito com o assembly da máquina, e retorna na saída os resultados
esperados por meio da execucção das instrucoes do arquivo de entrada. Caso o arquivo texto de entrada possua instruções
inválidas, o programa indica quais linhas contêm essas instruções, informando também qual o erro especifico.

Para mais informações, consulte o arquivo "Descricao.pdf".

Para compilar e executar o programa, basta utilizar o comando "make" no terminal do Linux. Em seguida, utiliza-se
o comando "./maquinaPilha".

Os arquivos "raiz.txt", "bhaskara.txt" e "mruv.txt" presentes nesse repositório podem ser utilizados como arquivos de entrada, para testes.

raiz.txt -> permite obter a raiz quadrada de um determinado número. Para escolher o número, é necessário substituir
todas as ocorrências do caractere "#" pelo número desejado, no arquivo texto.

bhaskara.txt -> permite obter as raízes de uma equação do segundo grau. Para escolher os coeficientes da equação
(a,b e c), é necessário substituir as ocorrências dos caracteres "@", "#", "&" pelos números desejados em todo o
arquivo texto (a = @, b = #, c = &).

mruv.txt -> permite determinar a posição final de um determinado corpo em moviimento retilíneo uniforme variado
(MRUV). Para escolher a posição inicial, a velocidade inicial, a aceleração e o tempo do movimento, é necessário
substituir os caracteres "@", "#", "&", "%" pelos números desejados em todo o arquivo.
