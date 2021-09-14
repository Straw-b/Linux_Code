#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <string>
#include <errno.h>

int main()
{
    int epoll_fd = epoll_create(10);
    if(epoll_fd < 0)
    {
        printf("create failed\n");
        return 0;
    }

    int flag = fcntl(0, F_GETFL);
    fcntl(0, F_SETFL, flag | O_NONBLOCK);

    struct epoll_event ee;
    ee.events = EPOLLIN | EPOLLET;
    ee.data.fd = 0;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, 0, &ee);

    while(1)
    {
        struct epoll_event fd_arr[1];
        int ret = epoll_wait(epoll_fd, fd_arr, sizeof(fd_arr)/sizeof(fd_arr[0]), -1);
        if(ret < 0)
        {
            continue;
        }

        for(size_t i = 0; i < sizeof(fd_arr)/sizeof(fd_arr[0]); i++)
        {
            if(fd_arr[i].data.fd == 0)
            {
                std::string tmp;
                while(1)
                {
                    char buf[3] = {0};
                    ssize_t read_size = read(0, buf, sizeof(buf) - 1);
                    printf("read_size:%d\n", read_size);
                    if(read_size < 0)
                    {
                        if(errno == EAGAIN || errno == EWOULDBLOCK)
                        {
                            printf("正常情况\n");
                        }
                        break;
                    }

                    tmp.append(buf);

                    memset(buf, '\0', sizeof(buf));

                    if(read_size < (ssize_t)sizeof(buf) - 1)
                    {
                        break;
                    }
                }

                printf("buf:%s\n", tmp.c_str());
            }
        }
    }
    return 0;
}
