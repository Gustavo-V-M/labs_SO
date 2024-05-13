# Projeto 2 

Repositório referente ao projeto 2 de Sistemas operacionais do curso de Ciência da Computação.\

**Autores:**\
Gustavo Vilela Mitraud | 10400866

## Índice

- `contas.c` Codigo desenvolvido para resolver o problema 
- `compilacao.png` Screenshot que comprova compilação dentro da Maquina Virtual

## Problema 

O problema se consiste em solucionar causada pela seguinte situacao:\
Existem duas contas bancarias: TO e FROM, com cada uma possuindo um saldo.\
TO sempre ira receber transferencias da FROM, com essas transferencias podendo ser simultaneas.\

As duas contas seguem os seguintes principios:
1. TO pode receber mais de uma transferencia simultanea
2. FROM pode enviar mais de uma transferencia simultanea
3. A conta from nao pode enviar mais dinheiro caso nao possua saldo
4. A conta TO pode trocar de lugar com a conta FROM
5. Poderam ser realizadas ate 100 transacoes simultaneas.

## Solucao

Para solucionar cada condicao do problema, foram utilizadas as seguintes abordagens:\

1. Foram utilizados threads para possibilitar a simultaneadade de transações 
2. Foi feita uma verificação dentro de cada transação caso 

## Compilação  

### Requisitos

- `gcc 14.1.1`
- `Kernel 6.8.9 x86_64`

### Passos de compilação.

1. `gcc contas.c -lpthread`
2. `./a.out`





