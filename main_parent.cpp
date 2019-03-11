#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int main()
{
  int data_processed;
  int parent_to_child[2];
  int child_to_parent[2];
  pipe(child_to_parent);

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
      sprintf(buffer, "%d %d %d", parent_to_child[0], child_to_parent[0], child_to_parent[1]);
  
      (void)execl("app2", "app2", buffer, (char *)0);
      exit(EXIT_FAILURE);
    }
    else {
      do {
        scanf("%s", some_data);
        data_processed = write(parent_to_child[1], some_data, strlen(some_data));      
        printf("%d - wrote %d bytes\n", getpid(), data_processed);
      } while(strcmp(some_data, "quit"));
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
