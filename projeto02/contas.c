#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

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

  // TODO melhor a logica de troca das contas

  pthread_mutex_lock(&account_mutex);
  printf("Mutex bloqueado\n");
  if (transaction_count <= 100) {
    if (sw == 0) {
      if (from.saldo < v) {
        int *nullptr = NULL;
        printf("saldo insuficiente na conta from");
        return nullptr;
      } else {
        from.saldo -= v;
        to.saldo += v;
        printf("Saldo to: %i\nSaldo from: %i\n", to.saldo, from.saldo);
      }
    } else {
      if (to.saldo < v) {
        int *nullptr = NULL;
        printf("saldo insuficiente na conta to");
        return nullptr;
      } else {
        to.saldo -= v;
        from.saldo += v;
        printf("Saldo to: %i\nSaldo from: %i\n", to.saldo, from.saldo);
      }
    }
  }
  pthread_mutex_unlock(&account_mutex);
  printf("Mutex liberado\n");
  return NULL;
}
int main(int argc, char *argv[]) {
  // TODO realizar os testes que comprovam os requerimentos do problema

  pthread_t teste01;
  pthread_t teste02;

  transaction_count = 0;

  int value = 10;
  int arg_1[] = {value, 1};
  int arg_2[] = {value, 0};

  // inicializa cada conta com 100 unidades monetarias cada

  to.saldo = 100;
  from.saldo = 100;

  pthread_create(&teste01, NULL, transfer, (void *)&arg_1);
  pthread_create(&teste02, NULL, transfer, (void *)&arg_2);

  pthread_join(teste02, NULL);
  return EXIT_SUCCESS;
}
