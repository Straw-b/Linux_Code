#include <stdio.h>
#include <unistd.h>
#include <pthread.h>


class test
{
    public:
	    test()
		{
		}

        ~test()
		{
		}
		
		static void* ThreadStart(void* arg) // 成员函数，会变成2个参数，不匹配
		{
			test* lp = (test*) arg;
		}
		
		int InitSvr()
		{
			pthread_create(&tid_, NULL, ThreadStart, (void*)this);
		}


    private:
        pthread_t tid_;
};
