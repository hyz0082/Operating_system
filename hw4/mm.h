#ifndef __MY_MM_H_INCLUDED__
#define __MY_MM_H_INCLUDED__
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/queue.h>
#define NALLOC 1024
typedef long Align;	
void *mymalloc(size_t size);
void myfree(void *ptr);
void *myrealloc(void *ptr, size_t size);
void *mycalloc(size_t nmemb, size_t size);

union header {	// block header
	struct {
		union header *next;	// next block if on free list
		size_t size;		// size of this block
	} s;
	Align x;	// force aligment of blocks (align to long)
};				// to simplify alignment, all blocks are multiples of the header size, and the header is aligned properly

typedef union header Header;


#endif