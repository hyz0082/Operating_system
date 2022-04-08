#include "mm.h"

static Header base={0};				// empty list to get started
static Header *freep = NULL;	// start of free list
								// if freep is NULL, it is at the first call of mymalloc

static Header *morecore(size_t nunits) {	// ask system for more memory
	void *freemem;	//
	Header *insertHptr;

	if (nunits < NALLOC)	// requests at least NALLOC units, beacuse brk is expensive
		nunits = NALLOC;	// this larger block will be chopped up as needed
	freemem = sbrk(nunits * sizeof(Header));	// sbrk(n) 
	if (freemem == (char *)-1)	//check if no space at all (-1 the return value)
		return NULL;
	insertHptr = (Header *)freemem;
	insertHptr->s.size = nunits;	// setting the size field
	myfree((void *)(insertHptr + 1));	// inserts the additional memory into the list by clling free
	return freep;
}

void *mymalloc(size_t size)
{
	Header *currp;
	Header *prevp;
	size_t nunits;

	nunits = (size + sizeof(Header) - 1) / sizeof(Header) + 1;	// calculate size to alloc
	if (freep == NULL) {			// no free list yet, a degenerate free list will be created
		base.s.next = &base;        // first create a zero size block to initialize base 
		freep      = &base;         // to prevent additional check
		//prevp      = &base;	// and pointer to itself
		base.s.size = 0;					// degenerate free list
	}
	prevp = freep;
	currp = prevp->s.next;        //seg fault pos
	for (; ; prevp = currp, currp = currp->s.next) {	// find for the next allocated block that have a size bigger than nunits
		if (currp->s.size >= nunits) {	// big enough
			if (currp->s.size == nunits)	// exactly same size
				prevp->s.next = currp->s.next;	// remove p from the list
			else {				// allocate tail end
				currp->s.size -= nunits;	// cut the size of memory want to malloc,leave remains in list
				currp += currp->s.size;     //put header to new position and renew its size    
				currp->s.size = nunits;
			}
			freep = prevp;
			return currp+1;               //return address of header position plus 1
		}
		if (currp == freep)		// wrapped around free list
			currp = morecore(nunits);
			if (currp == NULL)
				return NULL;	// malloc fail because if none left
	}
}

void myfree(void *ptr)	// put block ap in free list
{
	Header *insertptr;
	Header *currptr;

	insertptr = (Header*)ptr - 1;	// point to block header
	for (currptr = freep; !(currptr < insertptr && insertptr < currptr->s.next); currptr = currptr->s.next)	
	// scans the free list, starting at freep ,
	//find a currptr which one and next one is between ptr which want to free
		if (currptr >= currptr->s.next && (insertptr > currptr || insertptr < currptr->s.next))			
			break;   
			// this is check special case 
			// to check if a block locate at begining or end of list
			// if block being freed is adjacent to either neighbor, the adjacent blocks are combined
	if (insertptr + insertptr->s.size == currptr->s.next) {	// if insert ptr can be concatenated to next block
		insertptr->s.size += currptr->s.next->s.size;       // concatenated it to next one
		insertptr->s.next = currptr->s.next->s.next;	    //insertptr point to next next block 
	}
	else
		insertptr->s.next = currptr->s.next;       //if there are block between two block, just point to next one
	
	if (currptr + currptr->s.size == insertptr) {	//this is same as previous one
		currptr->s.size += insertptr->s.size;       //but it is concatenated to previous one
		currptr->s.next = insertptr->s.next;
	}
	else
		currptr->s.next = insertptr;	// point the next block

	freep = currptr;
}

void *myrealloc(void * ptr, size_t size)
{
	if (ptr == NULL)	// NULL ptr. realloc should act like malloc.
		return mymalloc(size);
	//Header *p = (Header *)ptr - 1;	// point to the header
	//size_t n = (p->s.size - 1) * sizeof(Header);
	int ori_size = ((Header*)ptr -1)->s.size;
	void *temp = mymalloc(size);	// allocate a new block to the given size using malloc
	//if (n < size)
	memcpy(temp, ptr, size);	// Copy data in ptr from the old one to the new one temp
	//else
	//	memcpy(temp, ptr, size);
	myfree(ptr);					// free the old block whick had been malloc
	return temp;					// return the new pointer
}

void *mycalloc(size_t nmemb, size_t size)
{
	void *ptr = mymalloc(nmemb * size);	// use malloc to get the memory
	if (ptr != NULL) {	// clear all the memory on successful alloction to zero
		memset(ptr, 0, nmemb * size);
	}
	return ptr;  // final return ptr
}
