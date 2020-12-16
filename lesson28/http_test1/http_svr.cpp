#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sstream>

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
    addr.sin_port = htons(8080);
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

    int newsockfd = -1;
    while(1)
    {
        newsockfd = accept(sockfd, NULL, NULL);
        if(newsockfd < 0)
        {
            perror("accept");
            return -1;
        }

        // <html>hello bite 84</html> text/html
        // 首行
        // 响应报头
        // 空行
        // 响应体
        std::string body = "<html><h1>You are a pig!</h1></html>";
        std::stringstream ss;
        ss << "http/1.1 200 OK\r\n";
        ss << "Content-Type: text/html\r\n";
        ss << "Content-Length: "<< body.size() << "\r\n";
        ss << "\r\n"; //空行

        ret = send(newsockfd, ss.str().c_str(), ss.str().size(), 0); // 发头部
        if(ret < 0)
        {
            perror("send");
            return -1;
        }

        ret = send(newsockfd, body.data(), body.size(), 0); // 发正文
        if(ret < 0)
        {
            perror("send");
            return -1;
        }
    }

    close(newsockfd); 
    close(sockfd); // 侦听的
    return 0;
}
