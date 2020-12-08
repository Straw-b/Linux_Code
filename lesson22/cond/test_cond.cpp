#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define THREAD_COUNT 2

//0 表示没有面
//1 表示有面
int g_bowl = 0;

pthread_mutex_t g_tex; //互斥锁
pthread_cond_t consume_cond; //消费者条件变量
pthread_cond_t product_cond; //生产者条件变量

void* EatNoddle(void* arg)
{
	pthread_detach(pthread_self()); //分离掉

	(void)arg;
	while (1)
	{
		pthread_mutex_lock(&g_tex);
		while (g_bowl <= 0)
		{
			pthread_cond_wait(&consume_cond, &g_tex);//等待
		}
		g_bowl--;
		printf("Eat: %p ---> g_bowl:%d\n", pthread_self(), g_bowl);
		pthread_mutex_unlock(&g_tex);

		//通知做面的人
        pthread_cond_signal(&product_cond);
    }
    return NULL;
}

void* MakeNoddle(void* arg)
{
    pthread_detach(pthread_self()); //分离掉

    (void)arg;
    while (1)
    {
        pthread_mutex_lock(&g_tex);
        while(g_bowl > 0)
        {
            pthread_cond_wait(&product_cond, &g_tex);//等待
        }
        g_bowl++;
        printf("Make: %p ---> g_bowl:%d\n", pthread_self(),g_bowl);
        pthread_mutex_unlock(&g_tex);

        //通知吃面的人
        pthread_cond_signal(&consume_cond);
    }
    return NULL;
}

int main()
{
    pthread_mutex_init(&g_tex, NULL);
    pthread_cond_init(&consume_cond, NULL);
    pthread_cond_init(&product_cond, NULL);

    pthread_t tid;
    for(int i = 0; i < THREAD_COUNT; i++)
    {
        int ret = pthread_create(&tid, NULL, EatNoddle, NULL);
        if (ret < 0)
        {
            perror("pthread_create");
            return -1;
        }

        ret = pthread_create(&tid, NULL, MakeNoddle, NULL);
        if (ret < 0)
        {
            perror("pthread_create");
            return -1;
        }
    }

    while (1)
    {
        sleep(1);
    }

    pthread_mutex_destroy(&g_tex);
    pthread_cond_destroy(&consume_cond);
    pthread_cond_destroy(&product_cond);
    return 0;
}
