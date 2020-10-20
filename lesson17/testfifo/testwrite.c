#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>


int main()
{
    mkfifo("./fifo", 0664); // 创建命名管道

    int fd = open("./fifo", O_RDWR);
    if(fd < 0)
    {
        perror("open");
        return -1;
    }

    write(fd, "linux-84", 8);
    printf("write done\n");

    while(1)
    {
        sleep(1);
    }

    close(fd);
    return 0;
}
