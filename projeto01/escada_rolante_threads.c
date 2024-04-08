#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
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
stair s = {-1, 0};
void *compute_person(void *arg) {
  person *cur_person = (person *)arg;

  if (s.current_direction == cur_person->direction ||
      s.final_time < cur_person->arrival_time + 10) {
    sem_wait(&sem_stair);
    s.final_time = cur_person->arrival_time + 10;
    sem_post(&sem_stair);
  } else if (s.current_direction != cur_person->direction ||
             s.final_time >= cur_person->arrival_time) {
    sem_wait(&sem_stair);
    s.current_direction = cur_person->direction;
    sem_post(&sem_stair);
  }
  return EXIT_SUCCESS;
}
int main(int argc, char *argv[]) {
  FILE *input;
  input = fopen(argv[1], "r");

  int num_person;

  fscanf(input, "%i", &num_person);

  person people[num_person];

  pthread_t person_threads[num_person];

  sem_init(&sem_stair, 0, 1);

  int d, a;

  for (int index = 0; index < num_person; index++) {
    fscanf(input, "%i %i", &a, &d);
    person cur = {d, a};
    people[index] = cur;
  }

  fclose(input);

  for (int n = 0; n < num_person; n++) {
    pthread_create(&person_threads[n], NULL, compute_person,
                   (void *)&people[n]);
  }

  for (int n = 0; n < num_person; n++) {
    pthread_join(person_threads[n], NULL);
  }

  printf("%i", s.final_time);

  sem_destroy(&sem_stair);

  return EXIT_SUCCESS;
}
