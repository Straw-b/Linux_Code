#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define THREAD_COUNT 4


int g_tickets = 100;

struct ThreadData
{
	int num_;
	ThreadData()
	{
		num_ = -1;
	}
};

void* TreadStart(void* arg)
{
    pthread_detach(pthread_self());
	ThreadData* td = (ThreadData*)arg;
    while(1)
	{
        if(g_tickets > 0)
        {
            printf("i am %p-%d, i have ticket is %d\n", pthread_self(),td->num_, g_tickets);
            g_tickets--;
        }
        else
        {
            break;
        }
	}
	delete td;
}

int main()
{
	pthread_t tid[THREAD_COUNT];

	for (int i = 0; i<THREAD_COUNT; i++)
	{
		struct ThreadData* td = new ThreadData; // 给每一个线程创建属于自己的空间 
		td->num_ = i;
		int ret = pthread_create(&tid[i], NULL, TreadStart, (void*)td);

		if (ret < 0)
		{
			perror("pthread_create");
			return -1;
		}
	}

	while (1)
	{
		printf("i am main thread\n");
		sleep(1);
	}

	return 0;
}
