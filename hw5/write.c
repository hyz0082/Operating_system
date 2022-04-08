#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
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
    char temp;
    fd = open("1.txt",O_CREAT|O_RDWR|O_TRUNC,00777);
    lseek(fd,getpagesize(),SEEK_SET);
    if (write(fd, "", 1) != 1)
        handle_error("write error");
    p_map=(people*)mmap(NULL,getpagesize(),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if (p_map == (void *)-1){
        fprintf(stderr, "mmap: %s\n", strerror(errno));
        return 0;
    }
    close(fd);
    temp='a' -1;
    for(i=0;i<10;i++){
        temp+=1;
        (*(p_map+i)).name[1] = '\0';
        memcpy((*(p_map+i)).name,&temp,1);
        (*(p_map+i)).age = 20+i;
    }
    printf("initializeover\n");
    sleep(10);
    munmap(p_map,getpagesize());
    printf("umapok\n");
}
