#include <stdio.h>    
#include <unistd.h>    
#include <sys/socket.h>    
#include <netinet/in.h>    
#include <arpa/inet.h>                                                                                    
#include <iostream>    

int main()    
{    
    int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);    
    if(sockfd < 0)    
    {    
        perror("socket");    
        return -1;    
    }    

    //地址信息
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(18989);
    //私网IP：172.17.0.12
    //1. 将点分十进制的IP地址转化成无符号的4字节的整数
    //2. 将该整数转化成为网络字节序(二进制)
    addr.sin_addr.s_addr = inet_addr("172.17.0.12");

    int ret = bind(sockfd, (sockaddr*)&addr, sizeof(addr));
    if(ret < 0)
    {
        perror("bind");
        return -1;
    }


    while(1)    
    {    
        sleep(1);    
    }    
    return 0;    
}    

