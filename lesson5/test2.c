#include <stdio.h>
#include <unistd.h>

int main()
{
    int ret = fork();
    if(ret<0)
    {
        perror("fork");
        return 0;
    }
    else if(ret==0)
    {
        printf("i am child, pid=%d, ppid=%d\n",getpid(),getppid());
    }
    else
    {
        printf("i am father, pid=%d, ppid=%d\n",getpid(),getppid());
    }
    return 0;
}
