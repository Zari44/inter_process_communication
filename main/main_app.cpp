#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<assert.h>
#include<string>
#include<iostream>
#include<fstream>
#include<queue>

void print_help(){
  std::cout << "You can run this program with the following options:\n"
                "--commands_file  -  specify path to file containing commands\n"
                "--help  -  prints this help and exits\n";
}

std::string parse_input_commands(int argc, char *argv[]){

  std::string commands_file_path = "";

  if (argc > 4) {
    std::cout << "Too many input parameters\n";
    print_help();
    std::cout << "Continuing with input ignored";
    return commands_file_path;
  }

  for (int i = 1; i < argc; ++i) {

    if (std::string(argv[i]) == "--help") {
      print_help();
      exit(EXIT_SUCCESS);
    }
    else if (std::string(argv[i]) == "--commands_file"){
      commands_file_path = std::string(argv[++i]);
    }
    else {
      std::cout << "Unknonw parameter\n";
      print_help();
    }
  }  
  return commands_file_path;
}

std::queue<std::string> get_commands_from_commands_file(std::string commands_file_path){
  std::ifstream commands_file;
  std::queue<std::string> commands;
  commands_file.open (commands_file_path);

  if (!commands_file.is_open())
    return commands;

  std::string command_line;

  while (std::getline(commands_file, command_line)){
    commands.push(command_line);
  }
  commands_file.close();
  return commands;
}

int main(int argc, char *argv[]) {

  //any data written to fd[1] 
  //can be read back from fd[0]
  const int WRITE = 1;
  const int READ = 0;

  std::string commands_file_path = parse_input_commands(argc, argv);
  
  int parent_to_child[2];
  int child_to_parent[2];
  assert(pipe(child_to_parent) == 0);
  assert(pipe(parent_to_child) == 0);

  pid_t fork_result = fork();
  if (fork_result == -1) {
    std::cout << "Fork failure" << std::endl;
    exit(EXIT_FAILURE);
  }
  if (fork_result == 0) { //child process
    const char* drawer_path = "./drawer_app";
    execl(drawer_path, drawer_path, std::to_string(parent_to_child[READ]).c_str(),
                                    std::to_string(child_to_parent[WRITE]).c_str(), 
                                    (char *)0);
    std::cout << "Child process failed\n"; 
    exit(EXIT_FAILURE);
  }
  else { //parent process
    int MAX_MESSAGE_LEN = 100;
    int data_processed;
    std::string input_data;
    char buffer[BUFSIZ + 1];
    memset(buffer, '\0', sizeof(buffer));

    std::ofstream log;
    bool is_log = true;
    log.open ("log.log", std::ofstream::app);
    if (!log.is_open()){
      std::cout << "Unable to open log file.\nContinue without logging.\n";
      is_log = false;
    }

    std::queue<std::string> commands = get_commands_from_commands_file(commands_file_path);

    do {
      if (!commands.empty()){
        input_data = commands.front();
        commands.pop();
      } else {
        std::getline(std::cin, input_data);
      }
      data_processed = write(parent_to_child[WRITE], input_data.c_str(), input_data.size());
      data_processed = read(child_to_parent[READ], buffer, MAX_MESSAGE_LEN);
      if (is_log) {
        log << buffer << std::endl;
      }
      memset(buffer, '\0', data_processed);
    } while(strcmp(input_data.c_str(), "quit"));
    log.close();
  }
  exit(EXIT_SUCCESS);
}
