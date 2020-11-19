#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sigcb(int signo)
{
    printf("signo is %d\n", signo);
}

int main()
{
    signal(2, sigcb);
    signal(40, sigcb);

    sigset_t newset, oldset;
    sigemptyset(&oldset);
    sigfillset(&newset);

    sigprocmask(SIG_SETMASK, &newset, &oldset);

    getchar();
    // 5(2) 5(40)
    //解除阻塞
    sigprocmask(SIG_SETMASK, &oldset, NULL);
    //观察，2号信号调用了几次sigcb      
    //      40信号调用了几次sigcb
    
    while(1)
    {
        sleep(1);
    }
    return 0;
}
