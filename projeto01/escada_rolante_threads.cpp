#include <cstdlib>
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

struct person {
  int arrive_time;
  int direction;
};

queue<person> person_queue;

void countTime() {
  timer++;
  sleep(3);
}

void stair(person *person_list, int person_count) {
  int i = 0;
  while (i < person_count) {
    if (person_list[i].arrive_time == timer) {
      person_queue.push(person_list[i]);
      if (person_queue.front().direction == current_direction ||
          current_direction == -1) {
        person_queue.pop();
        i++;
      }
    }
  }
}

int main(int argc, char *argv[]) { return EXIT_SUCCESS; }
