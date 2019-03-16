#include<unistd.h>
#include<string>  
#include<string.h>  
#include<iostream>

int main(int argc, char *argv[])
{
  std::cout << "Child process starts" << std::endl;
  std::cout << "Child arguments are: " << std::endl;

  for (int i = 0; i < argc; ++i) {
    std::cout << i << " : " << argv[i] << std::endl;
  }  

  int file_descriptor = std::atoi(argv[1]);
  int child_to_parent = std::atoi(argv[2]);
  char buffer[BUFSIZ + 1];
  memset(buffer, '\0', sizeof(buffer));
  std::cout << "file_descriptor = " << file_descriptor << std::endl;
  std::cout << "child_to_parent = " << child_to_parent << std::endl;

  while(strcmp(buffer, "quit")) {
    int data_processed = 0;
    data_processed = read(file_descriptor, buffer, BUFSIZ);
    std::cout << getpid() << " - read " << data_processed << " bytes: " << buffer << "\n";
    data_processed = write(child_to_parent, buffer, strlen(buffer));
    std::cout << getpid() << " - wrote " << data_processed << " bytes: " << buffer << "\n";
    memset(buffer, '\0', strlen(buffer));
  }
  printf("Child process exits\n");
  exit(EXIT_SUCCESS);
}
