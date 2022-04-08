CC = gcc
CFLAGS = -Wall -W -Og -g
OUT = main

all: dep
#	$(CC) $(CFLAGS) main.o -o $(OUT)
	$(CC) $(CFLAGS) read.o -o read
	$(CC) $(CFLAGS) write.o -o write

dep: 
#	$(CC) $(CFLAGS) -c main.c
	$(CC) $(CFLAGS) -c read.c write.c	

clean:
	rm -f  *.o read write 1.txt
