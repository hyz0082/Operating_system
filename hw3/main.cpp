#include"ph.hpp"

monitor m;
int main(){
    pthread_t t[N];
    for(long i = 0; i < N; i++)
        pthread_create(&t[i], NULL, philosopher, (void *)i); //create five p_thread
    for (int i = 0; i < N; ++i)
		pthread_join(t[i], NULL);    //del
}
