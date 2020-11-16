#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main()
{
    printf("process start\n");
    //int raise(int signo);
    raise(2);
    printf("hehehe\n");
    kill(getpid(), 2);
    while(1)
    {
        sleep(1);
    }
    return 0;
}
