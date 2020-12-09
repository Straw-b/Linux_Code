#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <vector>

#define CAPACITY 4
#define THREADCOUNT 2

class RingQueue // 线程安全队列
{
    public:
        RingQueue()
            :vec_(CAPACITY)
        {
            capacity_ = CAPACITY;

            //位置
            pos_write_ = 0;
            pos_read_ = 0;

            sem_init(&lock_, 0, 1); // 线程之间初始化为1
            sem_init(&read_, 0, 0); // 读信号量初始化为0
            sem_init(&write_, 0, CAPACITY); // 写信号量初始化为CAPACITY
        }

        ~RingQueue()
        {
            sem_destroy(&read_);
            sem_destroy(&write_);                              
        }

        void Push(int data)
        {
            //1.核心逻辑
            //2.分析当前核心逻辑当中有没有访问到临界资源时
            //3.在考虑同步问题

            sem_wait(&write_); // 获取写的信号量

            sem_wait(&lock_); // 加互斥锁
            vec_[pos_write_] = data;
            pos_write_ = (pos_write_ + 1) % capacity_;
            sem_post(&lock_);

            sem_post(&read_); // 通知读
        }

        void Pop(int* data)
        {
            sem_wait(&read_); // 获取读的信号量

            sem_wait(&lock_); // 加互斥锁 
            *data = vec_[pos_read_];
            pos_read_ = (pos_read_ + 1) % capacity_;
            sem_post(&lock_);

            sem_post(&write_); // 通知写
        }

    private:
        std::vector<int> vec_;
        int capacity_;

        int pos_read_; // 读的位置
        int pos_write_; // 写的位置

        sem_t lock_;
        sem_t read_;
        sem_t write_;

};

void* ReadStart(void* arg) // 入口函数
{
    RingQueue* rq = (RingQueue*)arg;
    while(1)
    {
        int data;
        rq->Pop(&data);
        printf("i am %p, i read %d\n", pthread_self(), data);
    }
    return NULL;
}

void* WriteStart(void* arg) // 入口函数
{
    RingQueue* rq = (RingQueue*)arg;
    int data = 0;
    while(1)
    {
        rq->Push(data);
        printf("i am %p, i write %d\n", pthread_self(), data);
        data++;
    }
    return NULL;
}


int main()
{
	pthread_t rd[THREADCOUNT], wr[THREADCOUNT];
    RingQueue* rq = new RingQueue();

    for(int i = 0; i < THREADCOUNT; i++)
    {
        int ret = pthread_create(&rd[i], NULL, ReadStart, (void*)rq);
        if(ret < 0)
        {
            perror("pthread_create");
            return -1;
        }

        ret = pthread_create(&wr[i], NULL, WriteStart, (void*)rq);
        if(ret < 0)
        {
            perror("pthread_create");
            return -1;
        }
    }

    for(int i = 0; i < THREADCOUNT; i++)
    {
        pthread_join(rd[i], NULL);
        pthread_join(wr[i], NULL);
    }

    delete rq;

    return 0;
}
