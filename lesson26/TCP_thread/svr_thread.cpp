#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

// 从堆上开辟newsockfd_结构体
struct NewConnectSockFd
{
    int newsockfd_;
};

// 工作线程入口函数
void* TestTcpStart(void* arg)
{
    pthread_detach(pthread_self()); // 分离自己

    struct NewConnectSockFd* nf = (struct NewConnectSockFd*)arg;

    while(1)
    {
        char buf[1024] = {0};

        int ret = recv(nf->newsockfd_, buf, sizeof(buf) - 1, 0);
        if(ret < 0)
        {
            perror("recv");
            close(nf->newsockfd_);
            delete nf;
            return NULL;
        }
        else if(ret == 0)
        {
            printf("peer shutdown\n");
            close(nf->newsockfd_);
            delete nf;
            return NULL;
        }

        printf("cli say: %s\n", buf);

        memset(buf, '\0', sizeof(buf));
        const char* str = "i am server";
        strncpy(buf, str, strlen(str));

        sleep(2);

        ret = send(nf->newsockfd_, buf, strlen(buf), 0);
        if(ret < 0)
        {
            perror("send");
            close(nf->newsockfd_);
            delete nf;
            return NULL;
        }
    }

    delete nf; // 在所有退出的地方释放
    return NULL;
}


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

    while(1)
    {
        // 主线程
        int newsockfd = accept(sockfd, NULL, NULL);
        if(newsockfd < 0)
        {
            perror("accept");
            return -1;
        }

        struct NewConnectSockFd* ncsf = new NewConnectSockFd();
        ncsf->newsockfd_ = newsockfd;// 刚接收回来的赋值给ncsf

        pthread_t tid; //线程标识符
        // 创建工作线程
        ret = pthread_create(&tid, NULL, TestTcpStart, (void*)ncsf); // 将结构体传入
        if(ret < 0)
        {
            delete ncsf;
            perror("pthread_create");
            return -1;
        }
    }

    close(sockfd);
    return 0;
}
