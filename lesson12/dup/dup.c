#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int fd = open("./hello", O_RDWR | O_CREAT, 0664);
    if( fd < 0 )
    {
        perror("open");
        return -1;
    }
    // 标准输出
    write(1, "before dup2\n", 12);
    
    printf("dup2\n");

    // 重定向
    dup2(fd, 1);
    
    // 理论上而言，就会输出到文件当中
    write(1, "hahaha\n", 7);

    return 0;
}
