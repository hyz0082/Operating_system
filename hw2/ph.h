#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#ifndef ph_h
#define ph_h
#define N 5 /* number of philosophers */
#define LEFT (i+N-1)%N /* number of i's left neighbor */
#define RIGHT (i+1)%N /* number of i's right neighbor */
#define THINKING 0 /* philosopher is thinking */
#define HUNGRY 1 /* philosopher is trying to get forks */
#define EATING 2 /* philosopher is eating */
#endif
void *philosopher(void* i); /* i: philosopher number, from 0 to N1 */
void take_forks(int i); /* i: philosopher number, from 0 to N1 */
void put_forks(int i); /* i: philosopher number, from 0 to N1 */
void test(int i); ///* i: philosopher number, from 0 to N1* /
void think(int i);
void eat(int i);



