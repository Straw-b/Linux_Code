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
    dest_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    int ret = connect(sockfd, (struct sockaddr*)&dest_addr, sizeof(dest_addr));
    if(ret < 0)
    {
        perror("connect");
        return -1;
    }

    while(1)
    {
        char buf[1024] = {0};
        strcpy(buf, "i am client12121");
        ret = send(sockfd, buf, strlen(buf), 0);
        if(ret < 0)
        {
            perror("send");
            return -1;
        }

        sleep(3);

        //memset(buf, '\0', sizeof(buf));

        //ret = recv(sockfd, buf, sizeof(buf) - 1, 0);
        //if(ret < 0)
        //{
        //    perror("recv");
        //    return -1;
        //}
        //else if(ret == 0)
        //{
        //    printf("peer shutdown\n");
        //    close(sockfd);
        //    return 0;
        //}

        //printf("svr say: %s\n", buf);
    }
    return 0;
}
