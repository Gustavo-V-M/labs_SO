#include <cstdlib>
#include <iostream>
#include <ostream>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <unistd.h>

/*
 * referências:
 * https://en.cppreference.com/w/cpp/thread/thread - Threads em c++*/

using namespace std;
int current_direction = -1;
int timer = 0;
int final_time = 0;
bool entered = false;
struct person {
  int arrive_time;
  int direction;
};

queue<person> person_queue;

void compute_person(person *person_list, int person_count, int i) {
  if (person_list[i].arrive_time == timer) {
    person_queue.push(person_list[i]);
    if (person_queue.front().direction == current_direction ||
        current_direction == -1) {
      current_direction = person_queue.front().direction;
      i++;
    } else {
      if (current_direction == 0) {
        current_direction = 1;
      } else {
        current_direction = 0;
      }
    }
  }
}
void calculate_total_time(int arrive_time) {
  if (final_time < arrive_time + 10) {
    final_time = arrive_time + 10;
  }
}
void stair(person *person_list, int person_count) {
  int i = 0;
  while (i < person_count) {
    timer++;
    compute_person(person_list, person_count, i);
  }
}

int main(int argc, char *argv[]) {

  person p1;
  p1.direction = 0;
  p1.arrive_time = 5;

  person p2;
  p2.direction = 0;
  p2.arrive_time = 8;

  person p3;
  p3.direction = 0;
  p3.arrive_time = 13;

  person person_list[3] = {p1, p2, p3};

  thread stair_thread(stair, person_list, 3);

  stair_thread.join();

  cout << final_time << endl;

  return EXIT_SUCCESS;
}
