#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

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

    int count = 0;
    while(1)
    {
        char buf[1024] = {0};
        strcpy(buf, "a");
        ret = send(sockfd, buf, strlen(buf), 0);
        if(ret < 0)
        {
            perror("send");
            return -1;
        }
        printf("%d\n", ++count);
    }

    close(sockfd);
    return 0;
}
