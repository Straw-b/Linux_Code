#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

/*
 * 1.需要监控0号文件描述符（标准输入）的可读事件
 *   使用select进行监控
 */

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
    {
        perror("socket");
        return 0;                            
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(18889);
    addr.sin_addr.s_addr = inet_addr("0.0.0.0");

    bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));

    listen(sockfd, 5);


    //如何将文件描述符添加到可读事件集合当中
    fd_set readfds;
    FD_ZERO(&readfds);

    //添加
    FD_SET(0, &readfds);
    FD_SET(sockfd, &readfds);

    while(1)
    {
        //定义超时时间
        struct timeval tv;
        tv.tv_sec = 6;
        tv.tv_usec = 0;

        fd_set tmp = readfds;
        int ret = select(sockfd+1, &tmp, NULL, NULL, &tv);
        if(ret < 0)
        {
            perror("ret");
            return 0;
        }
        else if(ret == 0)
        {
            //timeout
            ret = FD_ISSET(0, &tmp);
            printf("ret = %d\n", ret);

            ret = FD_ISSET(sockfd, &tmp);
            printf("sockfd ret : %d\n", ret);
            continue;
        }

        //正常监控成功
        //FD_ISSET ：返回0 ， 表示fd没有在集合当中
        //           返回非0， 表示fd在集合当中
        if(FD_ISSET(0, &tmp))
        {
            char buf[1024] = { 0 };
            read(0, buf, sizeof(buf)-1);
            printf("%s", buf);
        }

        if(!FD_ISSET(sockfd, &tmp))
        {
            printf("sockfd is not in readfds\n");               
        }
        else
        {
            printf("sockfd is in tmp\n");                                  
        }
    }

    return 0;
}
