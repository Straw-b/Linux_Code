#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void sigcb(int signo)
{
    wait(NULL);
}

int main()
{
    signal(SIGCHLD, sigcb);

    pid_t pid = fork();
    if(pid < 0)
    {
        return -1;
    }
    else if(pid == 0)
    {
        //child
    }
    else
    {
        //father
    }
    return 0;
}

