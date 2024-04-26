# Laboratório 4

## Realizado na semana do dia 23 de abril

**Conteúdo:** Foi criado um codigo em C que resolve o problema da multiplicação de uma matrix por um vetor utilizando pthreads. \
**OBS:** A maquina virtual da AWS foi acessada da maquina pessoal do integrante do grupo pelo terminal do linux utilizando o protocolo SSH.

**Integrante:**

- Gustavo Vilela Mitraud

## Resolução do problema

Para realizar o problema, foi levada em consideração o seguinte fato: a linha yi sera composta pela soma de cada elemento da linha Ai pelo seu elemento correspondente no vetor x. Portanto, cada linha pode ser separada em uma thread.

## Índice

- `multi_matrix_vector.c`: Código em C devenvolvido para resolver o problema
- `compilacao.png`: *Screenshot* com o arquivo sendo compilado e executado

## Compilação

**Requisitos:**

- `gcc Version 12.2.0`

**Etapas:**

1. Compilar o arquivo com o comando `$ gcc multi_matrix_vector.c -o multi_matrix_vector.bin`
2. Executar o arquivo com o comando `$ ./multi_matrix_vector.bin`

---------------------------------------
