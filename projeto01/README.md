# Projeto 1

Repositório referente ao projeto 1 de Sistemas operacionais do curso de Ciência da Computação. \
**OBS:** A Linguagem C++ foi utilizada ao invez da linguagem C por causa da biblioteca de Filas já inclusa no C++, já que, se fosse utilizado a linguagem C, teria que ser feita a implementação da fila do zero.

**Autores:**\
Gustavo Vilela Mitraud | 10400866

## Índice

- `escada_rolante_threads.cpp` - Arquivo que resolve o problema utilizando Threads.
- `escada_rolante_processos.cpp` - Arquivo que resolve o problema utilizando Processos.
- `testes.sh` - Arquivo que compila os outros arquivos de forma correta, realiza os teste propostos pelo professor e mede o tempo de execução.

## Problema 

Foi criada uma escada rolante dupla, podendo ela descer ou subir. \
Ela possui as seguintes caracteristicas: 
- Tem largura infinita, ou seja, infinitas pessoas podem estar usando ela em uma mesma direção ao mesmo tempo 
- Se ninguem estiver utilizando a escada ela se encontra parada 
- Caso ela se encontre parada, qualquer pessoa pode entrar, e a escada se movera na direção desejada pela pessoa 
- Caso ela se encontre em movimento, apenas pessoas que querem andar na mesma direção que a escada está se movendo atualmente podem entrar 
- Caso uma pessoa queira andar na direção oposta à atual da escada, ela deve esperar a escada parar para entrar 
- Cada pessoa demora 10 unidades de tempo para sair da escada 
- Duas pessoas nunca irão entrar na escada ao mesmo tempo 

O problema se consiste em implementar a escada rolante utilizando-se de threads e processos. \
Apos isso, deve se responder as seguintes perguntas: 
1. Qual a estratégia que você utilizou para evitar que duas pessoas acessem a escada rolante ao mesmo tempo em cada abordagem?
2. Como garantir que somente uma das direções está ativa de cada vez em cada uma das abordagens?
3. Discorra sobre as diferenças entre as implementações utilizando threads e processos e diga qual foi mais eficiente na solução do problema, justificando sua resposta.

## Respostas das perguntas propostas

**TODO** Responder perguntas 

## Compilação

**OBS: Até esse commit (60ff52dec153949a730509d6e591c11b9842bd4e), varios testes propostos pelo professor não estão funcionando**

### Requisitos

- `g++ 12.2.0`
- `Kernel: Linux 6.1.0-18 x86_64`

### Script de testes

1. deixar o script executável com `$ chmod u+x testes.sh`
2. executar o script com o comando `$ ./testes.sh`
3. Verificar os resultados dos testes no arquivo `resultado.txt`

### Manualmente 

1. 
 
