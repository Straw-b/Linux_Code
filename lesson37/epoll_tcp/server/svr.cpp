#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>


int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sockfd < 0)
    {
        perror("socket");
        return -1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(19999);
    addr.sin_addr.s_addr = inet_addr("0.0.0.0");

    int ret = bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
    if(ret < 0)
    {
        perror("bind");
        return -1;
    }

    ret = listen(sockfd, 5);
    if(ret < 0)
    {
        perror("listen");
        return -1;
    }

    //创建epoll句柄
    int epoll_fd = epoll_create(10);
    if(epoll_fd < 0)
    {
        printf("epoll_create failed\n");
        return 0;
    }

    struct epoll_event ee;
    ee.events = EPOLLIN;
    ee.data.fd = sockfd;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, sockfd, &ee);


    int newsockfd = -1;
    while(1)
    {
        struct epoll_event fd_arr[10];

        int ret = epoll_wait(epoll_fd, fd_arr, sizeof(fd_arr)/sizeof(fd_arr[0]), -1);
        if(ret < 0)
        {
            continue;
        }

        for(size_t i = 0; i < sizeof(fd_arr)/sizeof(fd_arr[0]); i++)
        {
            //侦听套接字有内容了
            if(fd_arr[i].data.fd == sockfd)
            {
                //accept
                struct sockaddr_in peer_addr;
                socklen_t peer_len = sizeof(peer_addr);
                int newsockfd = accept(sockfd, (struct sockaddr*)&peer_addr, &peer_len);

                printf("ip:port --》 %s:%d\n", inet_ntoa(peer_addr.sin_addr), ntohs(peer_addr.sin_port));
                
                if(newsockfd < 0)
                {
                    continue; //接收连接失败
                }

                struct epoll_event ee;
                ee.events = EPOLLIN;
                ee.data.fd = newsockfd;
                epoll_ctl(epoll_fd, EPOLL_CTL_ADD, newsockfd, &ee);
            }
            else
            {
                char buf[1024] = {0};
                ssize_t recv_size = recv(fd_arr[i].data.fd, buf, sizeof(buf) - 1, 0);
                if(recv_size < 0)
                {
                    continue; //接收内容失败
                }
                else if(recv_size == 0)
                {
                    //peer shutdown
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd_arr[i].data.fd, NULL);
                    close(fd_arr[i].data.fd);

                    continue;
                }

                printf("recv ：%s\n", buf);
            }
        }
    }

    close(newsockfd);
    close(sockfd);
    return 0;
}
