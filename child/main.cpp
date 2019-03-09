#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int main(int argc, char *argv[])
{
  char buffer[BUFSIZ + 1];
  memset(buffer, '\0', sizeof(buffer));
  scanf("%s", buffer);
  while(strcmp(buffer, "quit")) {
    printf("%d - read bytes: %s\n", getpid(), buffer);
    sleep(1);
  }
  exit(EXIT_SUCCESS);
}
