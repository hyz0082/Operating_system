#include"myshell_func.h"
char *get_input(){
    char *str = realloc(NULL,64), tmp;
    int count = 0;
    tmp = fgetc(stdin);
    while(tmp != '\n' && tmp != EOF && tmp != '\r'){
        str[count++] = tmp;
        str = realloc(str, 64 + count);
        tmp = fgetc(stdin);
    }
    str[count] = '\0';
    str = realloc(str, count+1);
    return str;   
}
int get_command_num(char* str){
    return strchr(str, '|') ? 2 : 1; 
}
char **split_command(char *str , int *command_num){
    char *sec_proc_pos, **command;
    *command_num = get_command_num(str);
    command = (char**)malloc(sizeof(char*) * (*command_num));
    if(*command_num == 1){
        command[0] = realloc(NULL, strlen(str) + 1);
        strcpy(command[0], str);
    }
    else{
        long int command_len[2];
        char *sec_proc_pos = strchr(str, '|');
        command[0] = realloc(NULL, command_len[0] = (sec_proc_pos - &str[0]) + 1);
        command[1] = realloc(NULL, command_len[1] = (str + strlen(str)) - sec_proc_pos);
        strncpy(command[0], str, command_len[0] - 1);
        strncpy(command[1], str + command_len[0], command_len[1]);
    }
    return command;
}

char **get_argv(char *str){
    char **command = realloc(NULL, 1);
    command[0] = realloc(NULL, 1);
    int curr_command = 0;
    for(int i = 0; i < strlen(str); i++){
        while(isspace(str[i]))
            i++;
        if(str[i] == '<' || str[i] == '>' || str[i] == '&')
            break;
        int count = 0;
        while(!isspace(str[i]) && str[i] != '\0'){
            command[curr_command][count] = str[i];
            count++;
            command[curr_command] = realloc(command[curr_command], count+1);
            i++;
        }
        command[curr_command][count] = '\0';
        curr_command++;
        command = realloc(command, curr_command + 1);
        command[curr_command] = realloc(NULL, 1);
    }
    command[curr_command] = (char*)NULL;
    return command;   
}
char *getfilename(char *command, char symbol){
    int len = strlen(command), count = 0;
    char *filename = (char*)realloc(NULL,1), *symbol_pos;
    symbol_pos = strchr(command, symbol);
    if(!symbol_pos)
        return NULL;
    symbol_pos++;
    while(isspace(*symbol_pos))
        symbol_pos++;
    while(!isspace(*symbol_pos) && *symbol_pos != '\0'){
        filename[count++] = *symbol_pos;
        filename = realloc(filename, count+1);
        symbol_pos++;
    }
    filename[count] = '\0';
    return filename;
}
char *getNewcommand(char *command, char symbol){
    char *new_command, *symbol_pos, *current;
    int count = 0;
    symbol_pos = strchr(command, symbol);
    if(!symbol_pos)
        return command;
    new_command = (char*)realloc(NULL, 1);
    current = command;
    while(*current != symbol){
        new_command[count++] = *current;
        new_command = realloc(new_command, count+1);
        current++;
    }
    new_command[count] = '\0';
    return new_command;
}

void redirect_in(char *src){
    FILE *in = src ? fopen(src, "r") : stdin;
    dup2(fileno(in), STDIN_FILENO);
    return;
}
void redirect_out(char *dst){
    FILE *out = dst ? fopen(dst, "w") : stdout;
    dup2(fileno(out), STDOUT_FILENO);
    return;
}
void exec_command(char **command, int command_num){
    int fd[2], status;
    pid_t pid;
    if(pid = fork()){ //parent
         char *runBackround = strchr(command[command_num-1], '&');
         if(runBackround){
             *runBackround = (char)0;
             printf("[%d]\n", pid);
             return;
         }
        while (waitpid(pid, &status, WUNTRACED | WCONTINUED) && 
               !WIFEXITED(status) && !WIFSIGNALED(status) );
        return;
    }
    char *src,*dst;
    if(command_num > 1){
        pipe(fd);
        pid_t pid = fork();
        if(pid == 0){
            close(fd[0]);
            dup2(fd[1], STDOUT_FILENO);
            close(fd[1]);
            src = getfilename(command[0], '<');
            command[0] = getNewcommand(command[0], '<');
            redirect_in(src); 
            char **arg = get_argv(command[0]);
            execvp(arg[0], arg);
        }
        else{
            close(fd[1]);
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
            dst = getfilename(command[1], '>');
            command[1] = getNewcommand(command[1], '>');
            redirect_out(dst); 
            char **arg = get_argv(command[1]);
            execvp(arg[0], arg);
        }

    }
    dst = getfilename(command[0], '>');
    command[0] = getNewcommand(command[0], '>');
    redirect_out(dst);
    src = getfilename(command[0], '<');
    command[0] = getNewcommand(command[0], '<');
    redirect_in(src); 
    command[0] = getNewcommand(command[0], '<');
    command[0] = getNewcommand(command[0], '>');
    char **arg = get_argv(command[0]);
    execvp(arg[0], arg);
}