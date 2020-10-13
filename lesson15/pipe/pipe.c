#include <stdio.h>
#include <unistd.h>

int main()
{
    //管道的大小
    //策略：1.创建一个管道
    //      2.不读， 但是一直往管道当中写
    //      3.在写的同时记录写的字节数量
    int fd[2];
    int ret = pipe(fd);
    if (ret < 0)
    {
        perror("pipe");
        return -1;
    }

    char buf[1024] = { 0 };
    read(fd[0], buf, sizeof(buf)-1);


#if 0
    int count = 0;
    while(1)
    {
        ssize_t w_size = write(fd[1],"h",1); //一次只写一个字节， 那么一次循环也就是写入了一个字节
        if(w_size != 1)
        {
            break;
        }
        count++;
        printf("count: %d\n", count);

    }
#endif

    return 0;
}
