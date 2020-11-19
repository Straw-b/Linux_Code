#include <stdio.h>
#include <signal.h>

volatile int g_val = 1;


void sigcb(int signo)
{
    g_val = 0;
    printf("signo : %d\n", signo);

}

int main()
{
    signal(2, sigcb);
    while(g_val)
    {
        sleep(1);
    }
}
