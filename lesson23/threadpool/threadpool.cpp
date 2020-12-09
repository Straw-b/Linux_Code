#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <queue>
#include <vector>

// 1.自定义类型
// 1.1数据
// 1.2处理数据的方法（函数）
typedef void (*Handler)(int);

class Data
{
    public:
        Data(int data, Handler handler)
        {
            data_ = data;
            handler_ = handler;
        }

        void run()
        {
            handler_(data_);
        }
		
    private:
        int data_; // 处理的数据
        Handler handler_; // 处理的方法
};

void func(int data)
{
    printf("data : %d\n", data);
}


// 2.封装线程池
// 2.1线程安全的队列， 队列的类型为自定义类型
// 2.2线程数量
class ThreadPool
{
    public:
        ThreadPool(int thread_count, int capa)
        {
            pthread_mutex_init(&mutex_, NULL);
            pthread_cond_init(&cond_, NULL);

            capacity_ = capa;
            thread_count_ = thread_count;
			
            vec_.clear(); // 初始化
            printf("%d\n", thread_count);
            vec_.resize(thread_count);

            flag = false;
        }

        ~ThreadPool()
        {
            pthread_mutex_destroy(&mutex_);
            pthread_cond_destroy(&cond_);
        }

        int Oninit() // 初始化线程池
        {
            //启动线程池当中的线程
            int ret = CreatThread();
            if(ret < 0)
            {
                return -1;
            }
            return 0;
        }

        void Push(Data* d) // 生产者
        {
            pthread_mutex_lock(&mutex_); // 加锁
			
            if(flag == true)
            {
                pthread_mutex_unlock(&mutex_);
                return;
            }

            while(que_.size() >= capacity_)
            {
                pthread_mutex_unlock(&mutex_);
                return;
            }
            que_.push(d);
			
            pthread_mutex_unlock(&mutex_);
            pthread_cond_signal(&cond_); // 通知消费者
        }

        void Pop(Data** d) // 消费者
        {
            *d = que_.front();
            que_.pop();
        }

        void PthreadJoin()
        {
            for(size_t i = 0; i < vec_.size(); i++)
            {
				printf("-----linux-----\n");
                pthread_join(vec_[i], NULL);
            }
        }

        void ThreadExit()
        { 
            pthread_mutex_lock(&mutex_);
            flag = true; //更改标志位
            pthread_mutex_unlock(&mutex_);
            pthread_cond_broadcast(&cond_); //唤醒全部
        }
		
    private:
        int CreatThread()
        {
            for(int i = 0; i < thread_count_; i++)
            {
                int ret = pthread_create(&vec_[i], NULL, ThreadStart, (void*)this);
                if(ret < 0)
                {
                    return -1;
                }
            }
            return 0;
        }

        // static：多一个this指针
        static void* ThreadStart(void* arg) // 所有线程入口函数
        {
            ThreadPool* tp = (ThreadPool*)arg;
            while(1)
            {
                pthread_mutex_lock(&tp->mutex_);// 加锁
				
                while(tp->que_.empty()) // 考虑同步
                {
                    if(tp->flag) // 优雅的退出
                    {
                        tp->thread_count_--;
                        pthread_mutex_unlock(&tp->mutex_);
                        pthread_exit(NULL);
                    }
                    pthread_cond_wait(&tp->cond_, &tp->mutex_);// 等待
                }

                Data* d;// 从队列出队的数据
                tp->Pop(&d);
                pthread_mutex_unlock(&tp->mutex_);

                d->run();// 执行run函数
                delete d;
            }
            
            return NULL;
        }
		
    private:
        std::queue<Data*> que_;  
        pthread_mutex_t mutex_;
        //线程池当中（消费）线程使用的条件变量
        pthread_cond_t cond_;	
		size_t capacity_;

        //线程数量
        int thread_count_;
        std::vector<pthread_t> vec_;

        //标志线程是否退出，1表示退出，0表示继续运行
        int flag;
};


//3.main函数往队列当中push数据
int main()
{
    ThreadPool* tp = new ThreadPool(4, 1); // 启动4个线程，队列大小1个
    if(!tp)
    {
        printf("init threadpool failed\n");
        return -1;
    }

    if(tp->Oninit() < 0)
    {
        printf("threadpool create thread failed\n");
        return -1;
    }

    //1.往线程池当中的队列进行push数据
    for(int i = 0; i < 100; i++)
    {
        Data* d = new Data(i, func);
        if(!d)
        {
            continue;
        }
        tp->Push(d);
        usleep(1000); // 1毫秒
    }
    
    sleep(3);
    tp->ThreadExit();
	
    //2.等待线程池当中的线程退出
    tp->PthreadJoin();
	
    delete tp;
    return 0;
}
