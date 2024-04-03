#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <queue>
#include <stdlib.h>
#include <string>
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
  queue<person> person_queue;
  int direction;
  int final_time;
  int timer;
};

stair s;

void compute_stair(person person_list[], int person_count) {
  int i = 0;
  while (i < person_count) {
    if (s.person_queue.empty()) {
      s.direction = person_list[i].direction;
      s.final_time += person_list[i].arrive_time + 10;
    }
    s.person_queue.push(person_list[i]);
    i++;
  }
}

void compute_timer() {
  while (!s.person_queue.empty()) {
    person p = s.person_queue.front();
    if (p.direction == s.direction) {
      s.final_time += (p.arrive_time + 10) - s.final_time;
      s.person_queue.pop();
    } else {
      if (s.timer >= s.final_time) {
        s.direction = p.direction;
        s.final_time += 10;
        s.person_queue.pop();
      } else {
        s.person_queue.pop();
        s.person_queue.push(p);
      }
    }
    s.timer++;
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

  s.person_queue = person_queue;
  s.final_time = 0;
  s.timer = -1;
  s.direction = 0;

  thread stair_thread = thread(compute_stair, person_list, person_count);
  stair_thread.join();
  thread timer_thread = thread(compute_timer);
  timer_thread.join();

  std::cout << s.final_time << endl;

  fclose(file);

  return EXIT_SUCCESS;
}
