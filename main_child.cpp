#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string>  
#include<string.h>  
#include<assert.h>

int main(int argc, char *argv[])
{
  const int READ = 0;
  const int WRITE = 1;
  int child_to_parent[2];
//   int file_descriptor;// = std::stoi(argv[1]);
//   // child_to_parent[0] = std::stoi(argv[2]);
//   // child_to_parent[1] = std::stoi(argv[3]);

//   int data_processed;
//   char buffer[BUFSIZ + 1];
//   memset(buffer, '\0', sizeof(buffer));	  
//   sscanf(argv[1], "%d", &file_descriptor);
//   while(strcmp(buffer, "quit")) {
//     data_processed = read(file_descriptor, buffer, BUFSIZ);
//     printf("%d - read %d bytes: %s\n", getpid(), data_processed, buffer);
//     memset(buffer, '\0', sizeof(buffer));	  
//   }
//   exit(EXIT_SUCCESS);
// }


// int main(int argc, char *argv[])
// {
  int data_processed;
  char buffer[BUFSIZ + 1];
  int file_descriptor;
  memset(buffer, '\0', sizeof(buffer));   
  sscanf(argv[1], "%d", &file_descriptor);
  // sscanf(argv[2], "%d", &child_to_parent[READ]);
  // sscanf(argv[3], "%d", &child_to_parent[WRITE]);
  while(strcmp(buffer, "quit")) {
    data_processed = read(file_descriptor, buffer, BUFSIZ);
    printf("%d - read %d bytes: %s\n", getpid(), data_processed, buffer);
    memset(buffer, '\0', sizeof(buffer));   
  }
  exit(EXIT_SUCCESS);
}