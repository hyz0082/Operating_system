all: dep
	gcc -pthread -o main *.o -Wall
dep:
	gcc -c main.c ph.c
clean:
	rm -f main main.o ph.o
