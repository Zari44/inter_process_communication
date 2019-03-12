#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
  printf("Starting app2\n");
  sleep(1);
  int code = execl("app2", "app2", (char*)0);
  printf("Execl returned with %d\n", code);
  exit(1);
}
