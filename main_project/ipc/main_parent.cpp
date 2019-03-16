#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<assert.h>
#include <string>
#include <iostream>

int main()
{
  //any data written to fd[1] 
  //can be read back from fd[0]
  const int WRITE = 1;
  const int READ = 0;
  int data_processed;

  int parent_to_child[2];
  int child_to_parent[2];
  assert(pipe(child_to_parent) == 0);

  char some_data[100];
  std::string input_data;
  char buffer[BUFSIZ + 1];
  pid_t fork_result;

  memset(buffer, '\0', sizeof(buffer));
  if (pipe(parent_to_child) == 0) {
    fork_result = fork();
    if (fork_result == (pid_t)-1) {
      fprintf(stderr, "Fork failure");
      exit(EXIT_FAILURE);
    }
    if (fork_result == 0) {
      //sprintf(buffer, "%d %d", parent_to_child[0], child_to_parent[1]);
      //printf("Starting child with parameters: %s\n", buffer);
      //sleep(1);
      //exec child process
      //const char filename[] = "app2";
      //char const* newargv[] = { std::to_string(parent_to_child[0]).c_str(), 
	    //std::to_string(child_to_parent[1]).c_str() };
      //char const* newenviron[] = { NULL };
      //execve(filename, newargv, newenviron);
      execl("./app2", "app2", std::to_string(parent_to_child[READ]).c_str(),
                              std::to_string(child_to_parent[WRITE]).c_str(), 
                              (char *)0);
      std::cout << "Child process failed\n"; 
      exit(EXIT_FAILURE);
    }
    else {
      do {
        std::getline(std::cin, input_data);
        // std::cout << "Parent. From stdin read: " << input_data << std::endl;
        data_processed = write(parent_to_child[WRITE], input_data.c_str(), input_data.size());
        // std::cout << getpid() << " - wrote " << data_processed << " bytes to child process\n";
	      data_processed = read(child_to_parent[READ], buffer, 20);
        // std::cout << getpid() << " - read " << data_processed << " bytes: " << buffer << "\n";
        memset(buffer, '\0', strlen(buffer));
      } while(strcmp(input_data.c_str(), "quit"));
    }
  }
  exit(EXIT_SUCCESS);
}


// #include<unistd.h>
// #include<stdlib.h>
// #include<stdio.h>
// #include<string.h>

// int main(int argc, char *argv[])
// {
//   int data_processed;
//   int parent_to_child[2];
//   int child_to_parent[2];
//   char some_data[100];
//   char buffer[BUFSIZ + 1];
//   pid_t fork_result;
//   memset(buffer, '\0', sizeof(buffer));
//   if (pipe(parent_to_child) == 0) {
//     fork_result = fork();
//     if (fork_result == (pid_t)-1) {
//       fprintf(stderr, "Fork failure");
//       exit(EXIT_FAILURE);
//     }
//     if (fork_result == 0) { //child
//       pipe(child_to_parent);
//       sprintf(buffer, "%d", parent_to_child[0]);
//       (void)execl("app2", "app2", parent_to_child[0], child_to_parent[0], child_to_parent[1], (char *)0);
//       exit(EXIT_FAILURE);
//     }
//     else { //parent
//       do {
//         scanf("%s", some_data);
//         data_processed = write(parent_to_child[1], some_data, strlen(some_data));      
//         printf("%d - wrote %d bytes\n", getpid(), data_processed);
//       } while(strcmp(some_data, "quit"));
//     }
//   }
//   exit(EXIT_SUCCESS);
// }
