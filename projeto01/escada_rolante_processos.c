#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

typedef struct {
  int direction;
  int arrival_time;
} person;

typedef struct {
  int current_direction;
  int final_time;
} stair;
sem_t sem_stair;
void compute_person(person *cur_person, stair *s) {
  if (s->current_direction == cur_person->direction ||
      s->final_time < cur_person->arrival_time + 10) {
    sem_wait(&sem_stair);
    s->final_time = cur_person->arrival_time + 10;
    sem_post(&sem_stair);
  } else if (s->current_direction != cur_person->direction ||
             s->final_time >= cur_person->arrival_time) {
    sem_wait(&sem_stair);
    s->current_direction = cur_person->direction;
    sem_post(&sem_stair);
  }
}
int main(int argc, char *argv[]) {
  FILE *input;
  input = fopen(argv[1], "r");

  int num_person;

  fscanf(input, "%i", &num_person);

  person people[num_person];
  stair *s = (stair *)mmap(NULL, sizeof(stair), PROT_READ | PROT_WRITE,
                           MAP_SHARED | MAP_ANONYMOUS, -1, 0);

  sem_init(&sem_stair, 0, 1);

  int d, a;

  for (int index = 0; index < num_person; index++) {
    fscanf(input, "%i %i", &a, &d);
    person cur = {d, a};
    people[index] = cur;
  }

  fclose(input);

  pid_t cur_pid, wpid;

  for (int n = 0; n < num_person; n++) {
    cur_pid = fork();
    switch (cur_pid) {
    case -1:
      perror("Erro no fork");
    case 0:
      compute_person(&people[n], s);
      exit(EXIT_SUCCESS);
    }
  }

  while ((wpid = wait(NULL) > 0))
    ;
  printf("%i", s->final_time);
  return EXIT_SUCCESS;
}
