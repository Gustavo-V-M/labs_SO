#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

typedef struct {
  int arrival_time;
  int direction;
} person;

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
  person *person_list = (person *)malloc(sizeof(person) * person_count);
  for (int i = 0; i < person_count; i++) {
    int arrival_time;
    int direction;
    fscanf(file, "%i %i", &arrival_time, &direction);

    person p = {arrival_time, direction};
    person_list[i] = p;
  }

  int person_pipe[person_count + 1][2];
  int direction_pipe[2];

  for (int i = 0; i < person_count; i++) {
    if (pipe(person_pipe[i]) < 0) {
      perror("Erro na criação do pipe de pessoas");
      exit(EXIT_FAILURE);
    }
  }

  if (pipe(direction_pipe) < 0) {
    perror("Erro na criação do pipe de direção");
    exit(EXIT_FAILURE);
  }

  pid_t person_pid[person_count + 1];

  person_pid[0] = fork();

  switch (person_pid[0]) {
  case -1:
    perror("Erro no fork");
    exit(EXIT_FAILURE);

  case 0:
    close(direction_pipe[0]);
    close(direction_pipe[1]);
    close(person_pipe[0][1]);

    wait(NULL);

    int final_time;
    read(person_pipe[0][0], &final_time, sizeof(final_time));
    close(person_pipe[0][0]);
    printf("Tempo final: %i", final_time);
    exit(EXIT_SUCCESS);

  default:
    for (int i = 1; i < person_count + 1; i++) {
      person_pid[i] = fork();
      switch (person_pid[i]) {
      case -1:
        perror("Erro no fork()");
        exit(EXIT_FAILURE);
      case 0:
        // child
        int cur_direction;
        read(direction_pipe[1], &cur_direction, sizeof(cur_direction));
        if (person_list[i].direction == 0)
      }
    }
  }

  return EXIT_SUCCESS;
}
