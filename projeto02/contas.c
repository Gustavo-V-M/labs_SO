#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Autor: Gustavo Vilela Mitraud | RA: 10400866
// Referências:
// https://stackoverflow.com/questions/14320041/pthread-mutex-initializer-vs-pthread-mutex-init-mutex-param
// Inicialização estatica do mutex
//
// https://linux.die.net/man/3/pthread_mutex_init Diferenças entre inicialização
// estatica e dinamica do mutex
//
// https://linux.die.net/man/3/pthread_mutex_lock pthread_mutex_lock e
// pthread__mutex_unlock
//
// https://www.di.ubi.pt/~operativos/praticos/html/9-threads.html#:~:text=%C2%B7%20Pthreads%20s%C3%A3o%20definidas%20como%20um,mais%20de%2060%20sub%2Drotinas.&text=%C2%B7%20O%20ficheiro%20pthread.,cada%20ficheiro%20de%20c%C3%B3digo%20fonte.
// pthread_create
//

typedef struct {
  int saldo;
} account;

account to;
account from;

typedef struct {
  int value;
  int sw;
} transaction;

int transaction_count;
// Inicialização estatica do mutex
pthread_mutex_t account_mutex = PTHREAD_MUTEX_INITIALIZER;

void *transfer(void *arg) {
  transaction *t = (transaction *)arg;
  int v = t->value;
  int sw = t->sw;

  // TODO logica de verificação de qunatidade de transações

  while (transaction_count >= 100)
    ;
  pthread_mutex_lock(&account_mutex);
  printf("Mutex bloqueado\n");
  transaction_count++;
  if (sw == 0) {
    if (from.saldo < v) {
      printf("saldo insuficiente na conta from\n");
    } else {
      from.saldo -= v;
      to.saldo += v;
      printf("Saldo to: %i\nSaldo from: %i\n", to.saldo, from.saldo);
    }
  } else {
    if (to.saldo < v) {
      printf("saldo insuficiente na conta to\n");
    } else {
      to.saldo -= v;
      from.saldo += v;
      printf("Saldo to: %i\nSaldo from: %i\n", to.saldo, from.saldo);
    }
  }
  transaction_count--;
  pthread_mutex_unlock(&account_mutex);
  printf("Mutex liberado\n");
  return NULL;
}
int main(int argc, char *argv[]) {
  // TODO realizar os testes que comprovam os requerimentos do problema

  transaction_count = 0;

  int value = 10;

  transaction arg_1 = {10, 0};

  // inicializa cada conta com 100 unidades monetarias cada

  to.saldo = 100;
  from.saldo = 100;

  pthread_t a[101];

  for (int i = 0; i < 101; i++) {
    pthread_create(&a[i], NULL, transfer, (void *)&arg_1);
  }
  for (int i = 0; i < 101; i++) {
    pthread_join(a[i], NULL);
  }

  return EXIT_SUCCESS;
}
