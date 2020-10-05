#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    // 1.创建匿名管道
    int fd[2];
    int ret = pipe(fd);
    if(ret < 0)
    {
        perror("pipe");
        return 0;
    }
    printf("fd[0]:%d\n", fd[0]);
    printf("fd[1]:%d\n", fd[1]);

    // 2.创建子进程
    ret = fork();
    if(ret < 0)
    {
        perror("fork");
        return 0;
    }
    else if(ret == 0)
    {
        close(fd[0]);
        // child
        write(fd[1], "linux so easy!!", 15);

        sleep(10);
        write(fd[1], "linux so easy!!!!!!!", 20);
    }
    else
    {
        close(fd[1]);
        // father
        sleep(5); // 保证子进程将数据写入匿名管道当中
        char buf[1024] = {0};

        read(fd[0], buf, sizeof(buf) - 1);
        printf("i am father: buf is: %s\n", buf);
           
        memset(buf, '\0', sizeof(buf));
        read(fd[0], buf, sizeof(buf) - 1);
        printf("i am father222: buf is: %s\n", buf);
    }

    // 当父子进程执行完上面的逻辑后，从if语句当中跳出来后，都会执行下面的代码
    while(1)
    {
        sleep(1);
    }

    return 0;
}
