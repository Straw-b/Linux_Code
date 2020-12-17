#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <sstream>

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        //./http_test [ip] [port] 或者 ./http_test 0.0.0.0 9090
        printf("using \"./http_test [ip] [port]\"\n");
        return -1;
    }

    std::string ip = argv[1];
    uint16_t port = atoi(argv[2]);

    int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sockfd < 0)
    {
        perror("socket");
        return -1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip.c_str());

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

    int newfd = accept(sockfd, NULL, NULL);
    if(newfd < 0)
    {
        perror("accept");
        return -1;
    }

    while(1)
    {
        char buf[1024] = { 0 };
        ret = recv(newfd, buf, sizeof(buf) - 1, 0);
        if(ret < 0)
        {
            perror("recv");
            continue;
        }
        else if(ret == 0)
        {
            printf("peer shutdown\n");
            close(newfd);
            close(sockfd);
            return -1;
        }
        printf("chrome say: %s\n", buf);
        memset(buf, '\0', sizeof(buf));

        //模拟http协议：
        //buf==>响应报头,body==>响应正文
        std::string body = "<html><h1>You are pig!</h1></html>";

        //snprintf(buf, sizeof(buf) - 1, 
        //        "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: %lu\r\n\r\n", 
        //        body.size());
        //send(newfd, buf, strlen(buf), 0);
        //send(newfd, body.c_str(), body.size(), 0);


        //std::stringstream header;
        //header << "HTTP/1.1 200 OK\r\n";
        //header << "Content-Type: text/html\r\n";
        //header << "Content-Length: " << body.size() << "\r\n";
        //header << "\r\n";

        //std::stringstream header;
        //header << "HTTP/1.1 302 Redirect\r\n";
        //header << "Content-Type: text/html\r\n";
        //header << "Content-Length: " << body.size() << "\r\n";
        //header << "Location: https://www.baidu.com\r\n"; // 重定向
        //header << "\r\n";

        std::stringstream header;
        header << "HTTP/1.1 404 page not found\r\n";
        header << "Content-Type: text/html\r\n";
        header << "Content-Length: " << body.size() << "\r\n";
        header << "\r\n";

        send(newfd, header.str().c_str(), header.str().size(), 0);
        send(newfd, body.c_str(), body.size(), 0);
    }

    close(newfd);
    close(sockfd);
    return 0;
}
