#include"ph.h"

int state[N]; /* array to keep track of everyone's state */
pthread_mutex_t s[N]; /* one semaphore per philosopher */
pthread_mutex_t mutex;
int main(){
    pthread_t t[N];
    pthread_mutex_init(&mutex,NULL);     //for critical section
    for(int i = 0; i < N; i++){
        pthread_mutex_init(&s[i],NULL);
        pthread_mutex_lock(&s[i]);   //first lock all s[N] 
    }
    //pthread_mutex_unlock(&s[0]);
    //pthread_mutex_unlock(&s[2]);
    for(long i = 0; i < N; i++)
        pthread_create(&t[i], NULL, philosopher, (void *)i); //create five p_thread
    for (int i = 0; i < N; ++i)
		pthread_join(t[i], NULL);    //del
}

//pthread_mutex_unlock(&mutex);
//pthread_mutex_lock(&s[i]);
