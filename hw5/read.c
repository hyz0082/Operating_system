#include<sys/mman.h>
#include<string.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
#include <errno.h>
#define handle_error(msg)   \
    do {                    \
        perror(msg);        \
        exit(EXIT_FAILURE); \
    } while (0)
typedef struct{
    char name[2];
    int age;
}people;
int main()//map a normal file as shared mem:
{
    int fd,i;
    people *p_map;
    fd=open("1.txt",O_CREAT|O_RDWR,00777);
    p_map=(people*)mmap(NULL,getpagesize(),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if (p_map == (void *)-1){
        fprintf(stderr, "mmap: %s\n", strerror(errno));
        return 0;
    }
    for(i=0;i<10;i++){
        printf("name:%s age%d\n",(*(p_map+i)).name,(*(p_map+i)).age);
    }
    munmap(p_map,getpagesize());
}
