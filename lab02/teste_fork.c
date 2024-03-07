// Author : Gustavo-V-M
// References:
// https://www.man7.org/linux/man-pages/man2/pipe.2.html - pipe function
// https://cplusplus.com/reference/cstdio/perror/ - perror function

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

int main(int argc, char *argv[]) {

  int pipe_fd[2];
  pid_t current_pid;

  if (pipe(pipe_fd) < 0) {
    perror("Error in pipe: ");
    exit(EXIT_FAILURE);
  }

  current_pid = fork();

  if (current_pid < 0) {
    perror("Error in fork: ");
    exit(EXIT_FAILURE);
  }

  else if (current_pid == 0) { // child
    //
    close(pipe_fd[0]);

    char *buffer = "Pipe test! Hello!!!\n";

    write(pipe_fd[1], buffer, strlen(buffer));
    close(pipe_fd[1]);
    exit(EXIT_SUCCESS);

  } else {      // parent;
    wait(NULL); // waits for child to write;
    printf("finished writing!\n");
    close(pipe_fd[1]);

    char char_buffer[1];

    while (read(pipe_fd[0], char_buffer, 1) > 0) {
      printf("%s", char_buffer);
    }

    close(pipe_fd[0]);
    exit(EXIT_SUCCESS);
  }
}
