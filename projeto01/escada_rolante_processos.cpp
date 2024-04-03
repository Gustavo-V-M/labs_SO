#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/*
 * referências:
 * https://www.man7.org/linux/man-pages/man2/shmget.2.html - Uso do shmget para
 * criação de um espaço de memoria compartilhado em linux
 * https://man7.org/linux/man-pages/man2/wait.2.html - uso do wait()
 *
 * */

using namespace std;

struct person {
  int arrive_time;
  int direction;
};

struct stair {
  queue<person> person_queue;
  int direction;
  int final_time;
  int timer;
};

void compute_stair(person person_list[], int person_count, stair *s) {
  int i = 0;
  while (i < person_count) {
    if (s->person_queue.empty()) {
      s->direction = person_list[i].direction;
      s->final_time += person_list[i].arrive_time + 10;
    }
    s->person_queue.push(person_list[i]);
    i++;
  }
}

void compute_timer(stair *s) {
  while (!s->person_queue.empty()) {
    person p = s->person_queue.front();
    if (p.direction == s->direction) {
      s->final_time += (p.arrive_time + 10) - s->final_time;
      s->person_queue.pop();
    } else {
      if (s->timer >= s->final_time) {
        s->direction = p.direction;
        s->final_time += 10;
        s->person_queue.pop();
      } else {
        s->person_queue.pop();
        s->person_queue.push(p);
      }
    }
    s->timer++;
  }
}

int main(int argc, char *argv[]) {

  if (argc != 2) {
    printf("Uso incorreto. uso correto: $ %s ./input/<arquivo>", argv[0]);
    return EXIT_FAILURE;
  }

  FILE *file;
  file = fopen(argv[1], "r");

  if (file == NULL) {
    perror("Erro na abartura do arquivo");
    return EXIT_FAILURE;
  }

  int person_count;

  // first line contains number of people
  fscanf(file, "%i", &person_count);

  // adding each person to the list of persons
  person *person_list = new person[person_count];
  for (int i = 0; i < person_count; i++) {
    int arrival_time;
    int direction;
    fscanf(file, "%i %i", &arrival_time, &direction);

    person p = {arrival_time, direction};
    person_list[i] = p;
  }

  queue<person> person_queue;

  stair *s;
  *s = {person_queue, 0, 0, -1};
  size_t STAIR_SIZE = sizeof(*s);

  // Creating shared memory space and attaching it to the father processes
  // BEFORE creating child processes
  int shmem_id = shmget(IPC_PRIVATE, STAIR_SIZE, IPC_CREAT);
  stair *stair_sh_mem = (stair *)shmat(shmem_id, nullptr, 0);
  memcpy(stair_sh_mem, s, STAIR_SIZE);

  // From this point, use stair_sh_mem as the parameters of the functions

  pid_t pid;
  pid = fork();

  switch (pid) {
  case -1:
    perror("Erro na criação do processo filho (fork)");
    exit(EXIT_FAILURE);
  case 0:
    // Child process
    compute_stair(person_list, person_count, stair_sh_mem);
    exit(EXIT_SUCCESS);
  default:
    // parent processe
    waitpid(pid, NULL, 0); // wait for child to exit
    compute_timer(stair_sh_mem);
    exit(EXIT_SUCCESS);
  }

  std::cout << s->final_time << endl;

  fclose(file);
  shmdt(stair_sh_mem);

  return EXIT_SUCCESS;
}
