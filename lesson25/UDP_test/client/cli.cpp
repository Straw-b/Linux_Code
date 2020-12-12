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

    while(1)
    {
        //2.发送数据
        char buf[1024] = { 0 };
        printf("please enter message: ");
        std::cin >> buf;
		
		// 服务端的地址信息
        struct sockaddr_in svr_addr; 
        svr_addr.sin_family = AF_INET;
        svr_addr.sin_port = htons(19999);
        svr_addr.sin_addr.s_addr = inet_addr("172.17.0.12"); 
		socklen_t svr_len = sizeof(svr_addr);

        ssize_t send_size = sendto(sockfd, buf, strlen(buf), 0, (sockaddr*)&svr_addr, svr_len);
        if(send_size < 0)
        {
            perror("sendto");
            return -1;
        }

        //3.接收应答
        memset(buf, '\0', sizeof(buf));
        ssize_t recv_size = recvfrom(sockfd, buf, sizeof(buf) - 1, 0, NULL, NULL);
        if(recv_size < 0)
        {
            perror("recvfrom");
            return -1;
        }

        //4.打印应答
        printf("server say: %s\n", buf);
    }

    close(sockfd);
    return 0;
}
