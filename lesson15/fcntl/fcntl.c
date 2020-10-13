#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int fd[2];
    int ret = pipe(fd);
    if(ret < 0)
    {
        perror("pipe");
        return -1;
    }

    //fd[0] fd[1]
    int flag = fcntl(fd[0],F_GETFL);
    printf("fd[0] = %d\n", flag);

    flag = fcntl(fd[1],F_GETFL);
    printf("fd[1] = %d\n", flag);

    fcntl(fd[1], F_SETFL, flag | O_NONBLOCK);

    flag = fcntl(fd[1],F_GETFL);
    printf("fd[1] again = %d\n", flag);

    return 0;
}
