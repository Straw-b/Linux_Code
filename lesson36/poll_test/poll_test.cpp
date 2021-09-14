#include <stdio.h>
#include <unistd.h>
#include <poll.h>

/*
 * 1.poll帮助我们监控0号文件描述符(标准输入), 关心0号文件描述符的可读事件, 一旦产生可读事件, 则poll函数返回
 * 完成这件事情: 
 *     1.创建事件结构数组, 在结构事件数组当中填充0号文件描述符以及关系的事件
 *     2.调用poll函数进行监控
 *     3.poll函数返回之后, 进行相应事件的处理
 * */

int main()
{
    struct pollfd arr[10];
    arr[0].fd = 0;
    arr[0].events = POLLIN;

    while(1)
    {
        printf("begin poll..\n");
        int ret = poll(arr, 1, 5000);
        if(ret < 0)
        {
            perror("poll");
            return 0;
        }

        for(int i = 0; i < 10; i++)
        {
            if(arr[i].revents == POLLIN)
            {
                printf("fd is %d\n", arr[i].fd);

                char buf[1024] = {0};
                read(arr[i].fd, buf, sizeof(buf) - 1);

                printf("buf :  %s\n", buf);
            }
        }
    }
    return 0;
}