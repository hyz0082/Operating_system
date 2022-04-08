#include"ph.hpp"
extern monitor m;
void *philosopher(void* j){ /* i: philosopher number, from 0 to N1 */
        int i = (long)j;
        while(1){
            think(i); /* philosopher is thinking */
            m.take_forks(i); /* acquire two forks or block */
            m.put_forks(i); /* put both forks back on table */
        }
}
void monitor::take_forks(int i){ /* i: philosopher number, from 0 to N1 */
    printf("philosopher %d is hungry\n", i);
    pthread_mutex_lock(&(this -> mutex)); /* enter critical region */
    this -> state[i] = HUNGRY; /* record fact that philosopher i is hungry */
    test(i); /* try to acquire 2 forks */
    if(this -> state[i]!=EATING)
        pthread_cond_wait(&(this -> s[i]),&(this -> mutex)); /* block if forks were not acquired */
    pthread_mutex_unlock(&(this -> mutex)); /* exit critical region */
    eat(i);
}
void monitor::put_forks(int i){ /* i: philosopher number, from 0 to N1 */
    pthread_mutex_lock(&(this -> mutex)); /* enter critical region */
    this -> state[i] = THINKING; /* philosopher has finished eating */
    test(LEFT); /* see if left neighbor can now eat */
    test(RIGHT); /* see if right neighbor can now eat */
    pthread_mutex_unlock(&(this -> mutex)); /* exit critical region */
}
void monitor::test(int i){
    if (this -> state[i] == HUNGRY && this -> state[LEFT] != EATING && this -> state[RIGHT] != EATING){
        this -> state[i] = EATING;
        pthread_cond_signal(&(this -> s[i]));
    }
}
void think(int i){
    printf("philosopher %d is thinking\n", i);
    srand(time(NULL));
    int r = rand() % 3 + 1;
    sleep(r);
}
void monitor::eat(int i){
    printf("philosopher %d is eating\n", i);
    srand(time(NULL));
    int r = rand() % 3 +1;
    sleep(r);
    printf("philosopher %d finish eating\n", i);
}
monitor::monitor(){
    pthread_mutex_init(&(this->mutex),NULL);     //for critical section
    for(int i = 0; i < N; i++)
        state[i] = 0;
}
