# Laboratório 2
## Realizado na semana do dia 04 de março

**Conteúdo:** Foi criado um código em C que realiza uma troca de mensagens entre um processo pai e um processo filho utilizando Pipes. Vale citar que o código foi compilado no ambiente da AWS utilizando a distribuição RedHat Linux <br> 
**OBS:** A maquina virtual da AWS foi acessada da maquina pessoal do integrante do grupo pelo terminal do linux utilizando o protocolo SSH

**Integrante:**
- Gustavo Vilela Mitraud

## Índice
- `teste_fork.c`: Código em C escrito pelo integrante do grupo
- `compilacao.png`: *Screenshot* com o arquivo sendo compilado e executado

## Bibliotecas extras utilizadas:
- `stdlib.h` biblioteca que contem a função `exit()`
- `sys/types.h` biblioteca que contem o tipo `pid_t`
- `sys/wait.h` biblioteca que implementa a função `wait()`
- `unistd.h` biblioteca que da acesso à API do sistema operacional e, portanto, possibilita a criação de processos filhos com o `fork()`  

## Compilação
**Requisitos:**
- `gcc Version 11.4.1`

**Etapas:**
1. Compilar o arquivo com o comando `$ gcc test_fork.c -o test_fork`
2. Executar o arquivo com o comando `$ ./test_fork`

## Change Log
- 05/03/2024 -> Inicializado o Repositório
- 06/03/2024 -> Finalizado o arquivo `test_fork` 
- 07/03/2024 -> Adicionado o screenshot com a compilação
- 11/03/2024 -> `README` finalizado 
