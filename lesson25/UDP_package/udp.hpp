#pragma once

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <string>
#include <iostream>

class UdpApi
{
    public:
        UdpApi()
        {
            sockfd_ = -1;
        }

        // 创建套接字
        int CreateSocket()
        {
            sockfd_ = socket(AF_INET, SOCK_DGRAM, 17);
            if(sockfd_ < 0)
            {
                perror("socket");
                return -1;
            }
            return 0;
        }

        // 绑定地址信息
        int Bind(std::string ip, uint16_t port)
        {
            struct sockaddr_in addr;
            addr.sin_family = AF_INET;
            addr.sin_port = htons(port);
            addr.sin_addr.s_addr = inet_addr(ip.c_str());

            int ret = bind(sockfd_, (sockaddr*)&addr, sizeof(addr));
            if(ret < 0)
            {
                perror("bind");
                return -1;
            }
            return 0;
        }

        // 发送数据
        int SendData(std::string data, struct sockaddr_in* addr, socklen_t addrlen)
        {
            ssize_t send_size = sendto(sockfd_, data.c_str(), data.size(), 0, (sockaddr*)addr, addrlen);
            if(send_size < 0)
            {
                perror("sendto");
                return -1;
            }
            return send_size;
        }
        
        // 接收数据
        int RecvData(std::string* data, struct sockaddr_in* addr, socklen_t* addrlen)
        {
            char buf[1024] = { 0 };
            ssize_t recv_size = recvfrom(sockfd_, buf, sizeof(buf) - 1, 0, (sockaddr*)addr, addrlen);
            if(recv_size < 0)
            {
                perror("recvfrom");
                return -1;
            }

            data->assign(buf, strlen(buf));
            return recv_size;
        }

        void Close()
        {
            close(sockfd_);
        }

    private:
        int sockfd_;
};
