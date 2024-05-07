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
typedef struct {
  int saldo;
} account;

account to;
account from;

// Inicialização estatica do mutex
pthread_mutex_t account_mutex = PTHREAD_MUTEX_INITIALIZER;

void *transfer(void *value) {
  int *nullptr = NULL;
  int v = *((int *)value);

  pthread_mutex_lock(&account_mutex);
  if (from.saldo < v) {
    int *nullptr = NULL;
    printf("saldo insuficiente na conta from");
    return nullptr;
  } else {
    from.saldo -= v;
    to.saldo += v;
  }
  pthread_mutex_unlock(&account_mutex);
  return nullptr;
}
int main(int argc, char *argv[]) {
  // TODO realizar os testes que comprovam os requerimentos do problema
  return EXIT_SUCCESS;
}
