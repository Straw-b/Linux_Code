#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>

int main()
{
    //1.创建套接字
    int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(sockfd < 0)
    {
        perror("socket");
        return -1;
    }

    //2.绑定端口
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

    while(1)
    {
        //3.接收
        char buf[1024] = { 0 };
		
		// 客户端的地址信息
        struct sockaddr_in cli_addr; 
        socklen_t cli_len = sizeof(cli_addr);
		
        ssize_t recv_size = recvfrom(sockfd, buf, sizeof(buf) - 1, 0, (sockaddr*)&cli_addr, &cli_len);
        if(recv_size < 0)
        {
            perror("recvfrom");
            return -1;
        }

        //4.处理
        printf("client say: %s\n", buf);
        printf("please enter respond: ");
        
        //5.回复应答
        fflush(stdout); // 强制刷新标准输出
        std::cin >> buf;

        ssize_t send_size = sendto(sockfd, buf, strlen(buf), 0, (sockaddr*)&cli_addr, cli_len);
        if(send_size < 0)
        {
            perror("sendto");
            return -1;
        }
    }

    close(sockfd);
    return 0;
}
