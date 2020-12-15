#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "../ConnectInfo.h"

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sockfd < 0)
    {
        perror("socket");
        return -1;
    }

    struct sockaddr_in dest_addr;
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(19999);
    dest_addr.sin_addr.s_addr = inet_addr("42.192.103.123");

    int ret = connect(sockfd, (struct sockaddr*)&dest_addr, sizeof(dest_addr));
    if(ret < 0)
    {
        perror("connect");
        return -1;
    }

    while(1)
    {
        struct AppHeader ah;
        ah.packet_size_ = 4;
        send(sockfd, &ah, sizeof(ah), 0); // 发送头部4个字节

        char buf[1024] = {0};

        strcpy(buf, "1+1\r\n");
        //char* m = (char*)malloc(sizeof(struct AppHeader)+strlen(buf));
        //memcpy(m, (struct AppHeader*)&ah, sizeof(ah));
        //memcpy(m + sizeof(ah), buf, strlen(buf));
        //ret = send(sockfd, (char*)m, strlen(buf), 0);

        ret = send(sockfd, buf, strlen(buf), 0); // 第一次发送
        if(ret < 0)
        {
            perror("send");
            return -1;
        }
        memset(buf, '\0', sizeof(buf));

        strcpy(buf, "2+1\r\n");
        ret = send(sockfd, buf, strlen(buf), 0); // 第二次发送
        if(ret < 0)
        {
            perror("send");
            return -1;
        }
        memset(buf, '\0', sizeof(buf));

        ret = recv(sockfd, buf, sizeof(buf) - 1, 0);
        if(ret < 0)
        {
            perror("recv");
            return -1;
        }
        else if(ret == 0)
        {
            printf("peer shutdown\n");
            close(sockfd);
            return 0;
        }

        printf("svr say: %s\n", buf);
    }

    close(sockfd);
    return 0;
}
