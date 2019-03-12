#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string>  
#include<string.h>  
#include<assert.h>

int main(int argc, char *argv[])
{
  printf("Child process starts\n");
  printf("Child arguments are:\n");
  for (int i = 0; i < argc; ++i){
    printf("%d : %s\n", i, argv[i]);
  }  

  int child_to_parent;
  int file_descriptor;
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


  //int data_processed;
  //char buffer[BUFSIZ + 1];
  //int file_descriptor;
  //assert(argc >= 3);
  //memset(buffer, '\0', sizeof(buffer));
  //file_descriptor = atoi(argv[1]);
  //assert(file_descriptor == 5);
  sscanf(argv[1], "%d", &file_descriptor);
  sscanf(argv[2], "%d", &child_to_parent);
  printf("file_descriptor = %d\n", file_descriptor);
  printf("child_to_parent = %d\n", child_to_parent); 
// sscanf(argv[3], "%d", &child_to_parent[WRITE]);
//  while(strcmp(buffer, "quit")) {
//    data_processed = read(file_descriptor, buffer, BUFSIZ);
//    printf("%d - read %d bytes: %s\n", getpid(), data_processed, buffer);
//    memset(buffer, '\0', sizeof(buffer));
//  }
  printf("Child process exits\n");
  exit(EXIT_SUCCESS);
}
