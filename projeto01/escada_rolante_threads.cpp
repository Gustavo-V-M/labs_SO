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
      }
    }
    s.timer++;
  }
}

void enter_person(person person_list[], int person_count) {}

int main(int argc, char *argv[]) {

  person p1;
  p1.direction = 0;
  p1.arrive_time = 5;

  person p2;
  p2.direction = 1;
  p2.arrive_time = 7;

  person p3;
  p3.direction = 0;
  p3.arrive_time = 9;

  person person_list[3] = {p1, p2, p3};

  queue<person> person_queue;

  s.person_queue = person_queue;
  s.final_time = 0;
  s.timer = -1;
  s.direction = 0;

  thread stair_thread(compute_stair, person_list, 3);
  stair_thread.join();
  thread timer_thread(compute_timer);
  timer_thread.join();

  std::cout << s.final_time << endl;

  return EXIT_SUCCESS;
}
