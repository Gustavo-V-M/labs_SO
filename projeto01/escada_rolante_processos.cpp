#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/*
 * referências:
 * https://biendltb.github.io/tech/inter-process-communication-ipc-in-cpp/ -
 * Alocação de um espaço de memoria compartilhado
 * https://en.cppreference.com/w/cpp/language/new - Uso do new em c++
 * https://www.man7.org/linux/man-pages/man2/fork.2.html - fork no linux
 * */

using namespace std;

struct person {
  int arrive_time;
  int direction;
};

struct stair {
  queue<person> direction0_queue;
  queue<person> direction1_queue;
  int direction;
  int final_time;
};

void compute_timer(stair *s) {
  while (!s->direction1_queue.empty() && !s->direction0_queue.empty()) {
    if (s->direction == -1) {
      if (s->direction0_queue.front().arrive_time <
          s->direction1_queue.front().arrive_time) {
        s->final_time = s->direction0_queue.front().arrive_time + 10;
        s->direction0_queue.pop();
        s->direction = 0;
      } else {
        s->final_time = s->direction1_queue.front().arrive_time + 10;
        s->direction1_queue.pop();
        s->direction = 1;
      }
    } else if (s->direction == 0) {
      if (s->direction0_queue.front().arrive_time <= s->final_time ||
          s->direction1_queue.front().arrive_time > s->final_time) {
        s->final_time = s->direction0_queue.front().arrive_time + 10;
        s->direction0_queue.pop();
      } else if (s->direction1_queue.front().arrive_time <
                 s->direction0_queue.front().arrive_time) {
        s->direction = 1;
        s->final_time += s->direction1_queue.front().arrive_time + 10;
        s->direction1_queue.pop();
      }
    } else if (s->direction == 1) {
      if (s->direction1_queue.front().arrive_time <= s->final_time ||
          s->direction0_queue.front().arrive_time > s->final_time) {
        s->final_time = s->direction1_queue.front().arrive_time + 10;
        s->direction1_queue.pop();
      } else if (s->direction0_queue.front().arrive_time <
                 s->direction1_queue.front().arrive_time) {
        s->direction = 0;
        s->final_time += s->direction0_queue.front().arrive_time + 10;
        s->direction0_queue.pop();
      }
    }
  }
  if (!s->direction0_queue.empty()) {
    while (!s->direction0_queue.empty()) {
      s->final_time = s->direction0_queue.front().arrive_time + 10;
      s->direction0_queue.pop();
    }
  } else {
    while (!s->direction1_queue.empty()) {
      s->final_time = s->direction1_queue.front().arrive_time + 10;
      s->direction1_queue.pop();
    }
  }
}

int main(int argc, char *argv[]) {

  if (argc != 2) {
    printf("Uso incorreto. uso correto: $ %s ./input/<arquivo>\n", argv[0]);
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

  queue<person> direction0_queue;
  queue<person> direction1_queue;

  stair *s = mmap(NULL, sizeof(stair), PROT_READ | PROT_WRITE,
                  MAP_SHARED | MAP_ANONYMOUS, -1, 0);

  s->direction0_queue = direction0_queue;
  s->direction1_queue = direction1_queue;

  s->final_time = 0;
  s->direction = -1;

  pid_t pid;
  int wait_status;

  pid = fork();

  switch (pid) {
  case -1:
    perror("Erro na criação do processo filho");
    exit(EXIT_FAILURE);
  case 0:
    for (int i = 0; i < person_count; i++) {
      cout << i << endl;
      if (person_list[i].direction == 0) {
        s->direction0_queue.push(person_list[i]);
      } else {
        s->direction1_queue.push(person_list[i]);
      }
    }
    exit(EXIT_SUCCESS);
  default:
    // parent process
    waitpid(pid, &wait_status, 0);
    if (WIFEXITED(wait_status)) {
      cout << "A" << endl;
    }
    compute_timer(s);

    fclose(file);
    munmap(s, sizeof(stair));
    exit(EXIT_SUCCESS);
  }

  return EXIT_SUCCESS;
}
