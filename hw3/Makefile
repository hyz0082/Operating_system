all: dep
	g++ -pthread -o main *.o -Wall
dep:
	g++ -c main.cpp ph.cpp
clean:
	rm -f main main.o ph.o
