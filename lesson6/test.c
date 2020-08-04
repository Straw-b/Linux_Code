#include <stdio.h> 
#include <stdlib.h>

int main() 
{
    pid_t ret = fork();
    if(ret < 0)
    {
        perror("fork"); 
        return 0; 
    } 
    else if(ret == 0)
    {
        //while (1)
        {
            printf("i am child pid=[%d], ppid[%d]\n", getpid(), getppid());
            sleep(20);
        }
    }
    else
    {
        while (1)
        {
            printf("i am parent pid=[%d], ppid=[%d]\n", getpid(), getppid());
            sleep(1);
        }
    } 
    return 0; 
}
