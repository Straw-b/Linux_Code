#include <stdio.h>
#include <unistd.h>
//调用wait函数用到的头文件
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t pid = fork();
    if(pid < 0)
    {
        perror("fork");
    }
    else if (pid == 0)
    {
        //child
        int count = 20;
        while(1)
        {
            if(count<=0)
            {
                break;
            }
            printf("i am child pid=%d, ppid=%d\n", getpid(), getppid());
            count--;
            sleep(1);
        }

        exit(10);
    }
    else
    {
        //father
        printf("begin ---> i am father pid=%d, ppid=%d\n", getpid(), getppid());

        int status;
        printf("child pid num is %d\n", pid);
        // 由于是非阻塞，所以需要使用到循环判断
        while( waitpid(pid, &status, WNOHANG) == 0);
        
        //printf("exit_code : %d\n", (status >> 8) & 0xFF);
        printf("sig_code : %d\n", status & 0x7F);
        printf("coredump_code : %d\n", (status >> 7) & 0x1);

        //父进程是否一开始就能进到这个逻辑当中
        //判断的依据：一开始是否大量输出“i am father”
        while (1)
        {
            printf("i am father pid=%d, ppid=%d\n", getpid(), getppid());
            sleep(1);
        }
    }
    return 0;
}
