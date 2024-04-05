#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <stdlib.h>
#include <thread>
#include <unistd.h>

/*
 * referências:
 * https://en.cppreference.com/w/cpp/thread/thread - Threads em c++
 * https://en.cppreference.com/w/cpp/language/new - Uso do new em c++*/

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
  int timer;
};

stair s;

void compute_stair(person person_list[], int person_count) {
  for (int i = 0; i < person_count; i++) {
    if (person_list[i].direction == 0) {
      s.direction0_queue.push(person_list[i]);
    } else {
      s.direction1_queue.push(person_list[i]);
    }
  }
}

void compute_timer() {
  while (!s.direction1_queue.empty() && !s.direction0_queue.empty()) {
    if (s.direction == -1) {
      if (s.direction0_queue.front().arrive_time <
          s.direction1_queue.front().arrive_time) {
        s.final_time = s.direction0_queue.front().arrive_time + 10;
        s.direction0_queue.pop();
        s.direction = 0;
      } else {
        s.final_time = s.direction1_queue.front().arrive_time + 10;
        s.direction1_queue.pop();
        s.direction = 1;
      }
    } else if (s.direction == 0) {
      if (s.direction0_queue.front().arrive_time <= s.final_time) {
        s.final_time = s.direction0_queue.front().arrive_time + 10;
        s.direction0_queue.pop();
      } else if (s.direction1_queue.front().arrive_time <
                 s.direction0_queue.front().arrive_time) {
        s.direction = 1;
        s.final_time += s.direction1_queue.front().arrive_time + 10;
        s.direction1_queue.pop();
      }
    } else if (s.direction == 1) {
      if (s.direction1_queue.front().arrive_time <= s.final_time) {
        s.final_time = s.direction1_queue.front().arrive_time + 10;
        s.direction1_queue.pop();
      } else if (s.direction0_queue.front().arrive_time <
                 s.direction1_queue.front().arrive_time) {
        s.direction = 0;
        s.final_time += s.direction0_queue.front().arrive_time + 10;
        s.direction0_queue.pop();
      }
    }
  }
  if (!s.direction0_queue.empty()) {
    while (!s.direction0_queue.empty()) {
      s.final_time = s.direction0_queue.front().arrive_time + 10;
      s.direction0_queue.pop();
    }
  } else {
    while (!s.direction1_queue.empty()) {
      s.final_time = s.direction1_queue.front().arrive_time + 10;
      s.direction1_queue.pop();
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

  s.direction0_queue = direction0_queue;
  s.direction1_queue = direction1_queue;

  s.final_time = 0;
  s.timer = -1;
  s.direction = -1;

  thread stair_thread = thread(compute_stair, person_list, person_count);
  stair_thread.join();
  thread timer_thread = thread(compute_timer);
  timer_thread.join();

  std::cout << s.final_time << endl;

  fclose(file);

  return EXIT_SUCCESS;
}
