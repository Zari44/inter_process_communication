#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<assert.h>
#include <string>
#include <iostream>

// Any data written to file_descriptor[1]
// can be read back from file_descriptor[0]

int main()
{
  std::cout << "Parent starts\n";
  const int READ = 0;
  const int WRITE = 1;  
  int data_processed;
  //any data written to fd[1] 
  //can be read back from fd[0]
  int parent_to_child[2];
  int child_to_parent[2];
  assert(pipe(child_to_parent) == 0);

  char some_data[100];
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

      close(parent_to_child[1]);//child does not write to parent-to-child pipe
      close(child_to_parent[0]);//child does not read from child-to-parent pipe

      dup2(parent_to_child[0], STDIN_FILENO);//replace stdin with incoming pipe
      dup2(child_to_parent[1], STDOUT_FILENO);//replace stdout with outgoing pipe

      // close(parent_to_child[0]); //close original fd for pipe communicateion
      // close(parent_to_child[1]); //because child will never write to parent
      execl("./app2", "app2", std::to_string(parent_to_child[0]).c_str(), //child reads from parent-to-child pipe
                              std::to_string(child_to_parent[1]).c_str(), //child writes to child-to-parent pipe
                              (char *)0);
      std::cout << "Child process failed\n";	
      exit(EXIT_FAILURE);
    }
    else {
      std::cout << "Parent after fork\n";
      close(parent_to_child[0]);//parent does not read from parent-to-child pipe
      close(child_to_parent[1]);//parent does not write to child-to-parent pipe

      dup2(parent_to_child[1], STDOUT_FILENO); //parent's stdout is send read at parent-to-child[0]
      dup2(child_to_parent[0], STDIN_FILENO);  //parent's stdin is an end of child_to_parent[1]
      std::cout << "Parent after dup2\n";
      do {
        std::cout << "Enter some data\n";
        std::cin >> some_data;
        // scanf("%s", some_data);
        data_processed = write(parent_to_child[1], some_data, strlen(some_data));
        std::cout << getpid() << " - wrote " << data_processed << " bytes\n";
	      data_processed = read(child_to_parent[0], buffer, BUFSIZ);
        std::cout << getpid() << " - read " << data_processed << " bytes: " << buffer << std::endl;
        memset(buffer, '\0', sizeof(buffer));
      } while(strcmp(some_data, "quit"));
      close(parent_to_child[1]);
    }
  }
  exit(EXIT_SUCCESS);
}


