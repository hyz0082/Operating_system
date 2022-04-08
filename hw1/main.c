#include"myshell_func.h"

int main(){
    int running = 1, command_num;
    char *input, **command, sec_proc_pos;
    while(running){
        printf("$ ");
        input = get_input();
        if(!strcmp(input, "q") || !strcmp(input, "quit"))
            return 0;
        command_num = get_command_num(input);
        command = split_command(input, &command_num);
        exec_command(command, command_num);
    }
}
