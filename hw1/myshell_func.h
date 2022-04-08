#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *get_input();
int get_command_num(char*);
char **split_command(char *, int *);
char **get_argv(char *); 
void exec_command(char**, int);
char *getfilename(char *, char);
char *getNewcommand(char*, char symbol);
void redirect_in(char *);
void redirect_out(char *);

