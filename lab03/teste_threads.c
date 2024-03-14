#define _GNU_SOURCE
#include <malloc.h>
#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
// 64kB stack
#define FIBER_STACK 1024 * 64

/*
referências: 
void pointer -> https://www.geeksforgeeks.org/void-pointer-c-cpp/
passando parametros para a clone(): https://stackoverflow.com/questions/8364950/how-to-pass-parameters-to-the-function-called-by-clone
*/

int num_1 = 0;
int num_2 = 1;
// The child thread will execute this function
int threadFunction(void *argument) {
  for (int i = 0; i < *(int*) argument; i++) {
    num_1++;
    num_2 = num_2*2;

  }
  printf("child thread exiting\n");
  return 0;
}
int main() {
  void *stack;
  pid_t pid;
  // Allocate the stack
  stack = malloc(FIBER_STACK);
  if (stack == 0) {
    perror("malloc: could not allocate stack");
    exit(1);
  }
  printf("Creating child thread\n");

  int arg = 10; 

  // Call the clone system call to create the child thread
  pid = clone(&threadFunction, (char *)stack + FIBER_STACK,
              SIGCHLD | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, (void*) &arg);
  if (pid == -1) {
    perror("clone");
    exit(2);
  }

  printf("Before thread startes-> %i, %i\n", num_1, num_2);
  // Wait for the child thread to exit
  pid = waitpid(pid, 0, 0);
  if (pid == -1) {
    perror("waitpid");
    exit(3);
  }
  printf("After thread finishes -> %i, %i\n", num_1, num_2);
  // Free the stack
  free(stack);
  printf("Child thread returned and stack freed.\n");
  return 0;
}