#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int main()
{
  int data_processed;
  int file_pipes[2];
  char some_data[100];
  char buffer[BUFSIZ + 1];
  pid_t fork_result;
  memset(buffer, '\0', sizeof(buffer));
  if (pipe(file_pipes) == 0) {
    fork_result = fork();
    if (fork_result == (pid_t)-1) {
      fprintf(stderr, "Fork failure");
      exit(EXIT_FAILURE);
    }
    if (fork_result == 0) {
      sprintf(buffer, "%d", file_pipes[0]);
      (void)execl("app2", "app2", buffer, (char *)0);
      exit(EXIT_FAILURE);
    }
    else {
      do {
        scanf("%s", some_data);
        data_processed = write(file_pipes[1], some_data, strlen(some_data));      
        printf("%d - wrote %d bytes\n", getpid(), data_processed);
      } while(strcmp(some_data, "quit"));
    }
  }
  exit(EXIT_SUCCESS);
}
