# Projeto 1

Repositório referente ao projeto 1 de Sistemas operacionais do curso de Ciência da Computação. \

**Autores:**\
Gustavo Vilela Mitraud | 10400866

## Índice

- `escada_rolante_threads.c` - Arquivo que resolve o problema utilizando Threads.
- `escada_rolante_processos.c` - Arquivo que resolve o problema utilizando Processos.
- `testes.sh` - Arquivo que compila os outros arquivos de forma correta, realiza os teste propostos pelo professor e mede o tempo de execução.
- `compilacao.png` - Imagem que comprova compilacao e execução no ambiente da AWS

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
3. Discorra sobre as diferenças entre as implementações utilizando threads e processos e diga qual foi mais eficiente na solução do problema, justificando sua respostas 

## Respostas das perguntas propostas

1. A estratégia utilizada para evitar que duas pessoas acessem a escada ao mesmo tempo foi a implementação de semaforos que, quando uma pessoa "entra" na escada rolante, impede que outras pessoas entrem ao mesmo tempo
2. A forma que foi garantida que apenas uma direção esteja ativa ao mesmo tempo foi a utilização de uma variavel que era compartilhada entre cada pessoa: No caso da implementação utilizando threads, era uma variavel global, e no caso da implementação utilizando processos, um espaço de memoria alocado que pode ser acessado pelo processo pai e seus filhos;
3. Em geral, ambas implementações são similares, visto que concorrência pode ser alcançada de ambas as formas (threads e processos). Em termos de diferenças, a utilização de threads possibilita que variaveis globais sejam utilizadas sem dificuldade, mas cria complicações na hora de chamar as funções (É necessario utilizar-se de void pointers para passar argumentos para as funções). Já a implementação utilizando processos, dificulta o compartilhamento de mensagens entre processos, visto que processos diferentes possuem espaços de memoria diferentes, mas facilita na utilização das funções. Finalizando, a implementação usando threads, para esse problema, foi a mais eficaz em resolver o problema, tendo em vista o tempo de execução e a complexidade da implementação e utilização de recursos. 

## Compilação

**OBS: Alguns testes propostos pelo professor estão falhando (Compilam, executam mas não dão o resultado esperado)**
No meu ver, isso se dá por um erro na lógica criada para realizar um problema, e não na implementação de threads e processos. \ 
Atualmente, a solução se baseia em cada pessoa ser uma thread/processo, e com um semaforo para controlar o acesso à variáveis. Uma possivel alternativa melhor seria a utilização de duas filas que controlam quando cada pessoa de cada direção deve entrar. \
Eu tentei utilizar essa ideia em commits anteriores, mas por falta de tempo e pela quantidade de erros, resolvi tentar utilizando a logica atual, que, apesar de varios erros, compila e executa. 

### Requisitos

- `gcc 12.2.0`
- `bc 1.07.1` (Para executar o script de testes)
- `Kernel: Linux 6.1.0-18 x86_64`

### Instalação dos requisitos 

#### Fedora Based

`sudo dnf install gcc bc`

#### Arch Based 

`sudo pacman -S gcc bc`

#### Debian Based 

`sudo apt install gcc bc`

### Script de testes

1. deixar o script executável com `$ chmod u+x testes.sh`
2. executar o script com o comando `$ ./testes.sh`
3. Verificar os resultados dos testes no arquivo `resultado.txt`

### Manualmente 

#### Threads 

1. Compilar o arquivo com `gcc  escada_rolante_threads.c -o threads.bin -lpthread` 
2. Executar o script com `./threads.bin ./input/<NOME DO ARQUIVO>`, substituindo o nome do arquivo pelo o teste desejado 

#### Processos 

1. Compilar o arquivo com `gcc escada_rolante_processos.c -o processos.bin`
2. Executar o script com `./processos.bin ./input/<NOME DO ARQUIVO>`, substituindo o nome do arquivo pelo teste desejado 
 
