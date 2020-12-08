#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define THREAD_COUNT 4

struct ThreadData
{
	int num_;
	ThreadData()
	{
		num_ = -1; // 结构体构造，初始化
	}
};

class Data
{
public:
	void SetData(int data)
	{
		data_ = data;
	}

	int GetData()
	{
		return data_;
	}

private:
	int data_;
};


void* TreadStart(void* arg)
{
    pthread_detach(pthread_self());

	//ThreadData* td = (ThreadData*)arg;
	Data* d = (Data*)arg;

    //while(1)
	{
		//printf("i am work thread:%d\n", td->num_);
		printf("i am work thread:%d\n", d->GetData());
		sleep(1);
	}

    sleep(3);

    pthread_cancel(pthread_self());
    while(1)
    {
        sleep(1);
    }

	// 释放堆上的内存， 应该在线程的内部去释放， 当线程不在用的时候
	delete d;
}

int main()
{
	pthread_t tid[THREAD_COUNT];

	// 1.临时变量可以吗？
	// 2.堆上开辟的空间可以吗？
	// 3.结构体可以吗？
	// 4.类的this指针可以吗？
	for (int i = 0; i<THREAD_COUNT; i++)
	{
		//struct ThreadData* td = new ThreadData; // 给每一个线程创建属于自己的空间 
		//td->num_ = i;
		//int ret = pthread_create(&tid, NULL, TreadStart, (void*)td); // 传结构体指针

		Data* d = new Data;
		d->SetData(i);
		int ret = pthread_create(&tid[i], NULL, TreadStart, (void*)d); // 传类的实例化指针

		if (ret < 0)
		{
			perror("pthread_create");
			return -1;
		}
	}

    //for(int i = 0; i < THREAD_COUNT; i++)
    //{
    //    pthread_join(tid[i], NULL); // 等待线程结束，否则阻塞
    //}

    printf("线程退出\n");

    //pthread_exit(NULL);
	while (1)
	{
		printf("i am main thread\n");
		sleep(1);
	}

	return 0;
}
