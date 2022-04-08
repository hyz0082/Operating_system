#include"ph.h"
extern int state[N]; /* array to keep track of everyone's state */
extern pthread_mutex_t s[N]; /* one semaphore per philosopher */
extern pthread_mutex_t mutex;
void *philosopher(void* j){ /* i: philosopher number, from 0 to N1 */
        int i = (long)j;
        while(1){
            think(i); /* philosopher is thinking */
            take_forks(i); /* acquire two forks or block */
            eat(i); /* yum-yum, spaghetti */
            put_forks(i); /* put both forks back on table */
        }
}
void take_forks(int i){ /* i: philosopher number, from 0 to N1 */
    printf("philosopher %d is hungry\n", i);
    pthread_mutex_lock(&mutex); /* enter critical region */
    state[i] = HUNGRY; /* record fact that philosopher i is hungry */
    test(i); /* try to acquire 2 forks */
    pthread_mutex_unlock(&mutex); /* exit critical region */
    pthread_mutex_lock(&s[i]); /* block if forks were not acquired */

}
void put_forks(int i){ /* i: philosopher number, from 0 to N1 */
    pthread_mutex_lock(&mutex); /* enter critical region */
    state[i] = THINKING; /* philosopher has finished eating */
    test(LEFT); /* see if left neighbor can now eat */
    test(RIGHT); /* see if right neighbor can now eat */
    pthread_mutex_unlock(&mutex); /* exit critical region */
}
void test(int i){
    if (state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING){
    state[i] = EATING;
    pthread_mutex_unlock(&s[i]);
    }
}
void think(int i){
    printf("philosopher %d is thinking\n", i);
    srand(time(NULL));
    int r = rand() % 5 + 1;
    sleep(r);
}
void eat(int i){
    printf("philosopher %d is eating\n", i);
    srand(time(NULL));
    int r = rand() % 6 +1;
    sleep(r);
    printf("philosopher %d finish eating\n", i);
}