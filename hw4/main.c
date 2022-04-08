#include"mm.h"

int main(){
    int *ptr1;
    ptr1 = mymalloc(20);
    printf("malloc testing:\nmalloc a block with size 20 and put 0~4 in it\n");
    for(int i = 0; i <5;i++)
         ptr1[i]=i;
    for(int i = 0; i <5;i++)
         printf("ptr[%d]: %d, ",i,ptr1[i]);
    printf("\n");
    printf("============================\nrealloc testing:\nrealloc a block with size 40 and additionally put 5~9 in it\n");
    ptr1 = myrealloc(ptr1,40);
    for(int i = 5; i <10;i++)
        ptr1[i]=i;
    for(int i = 0; i <10;i++){
         printf("ptr[%d]: %d, ",i,ptr1[i]);
         if(i == 4)
          printf("\n");
    }
    printf("\n");
    myfree(ptr1);
    printf("============================\ncalloc testing:\ncalloc a block with size 20\n");
    ptr1 = mycalloc(4,5);
    for(int i = 0; i <5;i++)
         printf("ptr[%d]: %d, ",i,ptr1[i]);
    myfree(ptr1);
    printf("\n");
}

