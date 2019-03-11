#include <unistd.h>
#include <iostream>
#include <cstring>
#include <string>

int main(){
    int parent_to_child[2];
    int child_to_parent[2];

    pipe(parent_to_child);
    pipe(child_to_parent);

    int childPID = fork();

    if(childPID == 0){
        //this is child
        close(parent_to_child[1]);//Close the writing end of the incoming pipe
        close(child_to_parent[0]);//Close the reading end of the outgoing pipe

        dup2(parent_to_child[0], STDIN_FILENO);//replace stdin with incoming pipe
        dup2(child_to_parent[1], STDOUT_FILENO);//replace stdout with outgoing pipe

        //exec child process
        char filename[] = "child";
        char *newargv[] = { NULL };
        char *newenviron[] = { NULL };
        execve(filename, newargv, newenviron);
    }else{
        //this is parent
        close(parent_to_child[0]);//Close the reading end of the outgoing pipe.
        close(child_to_parent[1]);//Close the writing side of the incoming pipe.

	dup2(child_to_parent[0], STDIN_FILENO);//replace stdin with incoming pipe

        int parent_frame = -3;
        char str_to_write[] = "string_to_write";

	int buff_size = 100;
        char reading_buffer;
        std::string received_str;

        do{
            //Make the frame number a cstring and append '\n'
            strcpy(str_to_write, std::to_string(parent_frame).c_str());
            strcat(str_to_write,"\n");

            write(parent_to_child[1], str_to_write, strlen(str_to_write));
            std::cout << "Parent sent: "<< str_to_write;

            received_str = "";
            //while(read(child_to_parent[0], &reading_buffer, 1) > 0){
	    //while({
            //    received_str += reading_buffer;
            //}
            std::getline(std::cin,received_str,'\n');

            std::cout << "Parent received: "<< received_str<< std::endl;
        } while (++parent_frame);
    }
    std::cout << "Parent terminates\n";
    return 0;
}
