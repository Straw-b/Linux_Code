#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define THREAD_COUNT 2

pthread_mutex_t tex1;
pthread_mutex_t tex2;

int g_tickets = 100;

struct ThreadData
{
    int num_;
    ThreadData()
    {
        num_ = -1;
    }
};

void* TreadStart1(void* arg)
{
    pthread_detach(pthread_self());
    pthread_mutex_lock(&tex1);

    sleep(5);
    pthread_mutex_lock(&tex2);
}

void* TreadStart2(void* arg)
{
    pthread_detach(pthread_self());
    pthread_mutex_lock(&tex2);

    sleep(5);
    pthread_mutex_lock(&tex1);
}


int main()
{
    pthread_mutex_init(&tex1, NULL);
    pthread_mutex_init(&tex2, NULL);
    pthread_t tid;

    int ret = pthread_create(&tid, NULL, TreadStart1, NULL);
    if (ret < 0)
    {
        perror("pthread_create");
        return -1;
    }

    ret = pthread_create(&tid, NULL, TreadStart2, NULL);
    if (ret < 0)                                            
    {           
        perror("pthread_create");
        return -1;               
    }        

    while (1)
    {
        //printf("i am main thread\n");
        sleep(1);
    }

    pthread_mutex_destroy(&tex1);
    pthread_mutex_destroy(&tex2);
    return 0;
}
