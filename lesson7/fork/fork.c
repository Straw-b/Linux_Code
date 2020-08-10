#include <stdio.h>
#include <unistd.h>


int g_val = 10;
int main ()
{
    pid_t pid = fork();
    if(pid<0)
    {
        perror("fork");
        return 0;
    }
    else if (pid==0)
    {
        //child
        printf("i am child g_val=[%d], pid=%d, ppid=%d\n", g_val, getpid(), getppid());
    }
    else
    {
        //father
        g_val +=10;
        printf("i am father g_val=[%d], pid=%d, ppid=%d\n", g_val, getpid(), getppid());
    }
    return 0;
}
