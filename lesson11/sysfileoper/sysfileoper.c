#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


int main()
{
    int ret = open("./linux84", O_RDWR | O_CREAT, 0664);
    if(ret < 0)
    {
        perror("open");
        return -1;
    }

    printf("file oper ret = %d\n", ret);

    return 0;
}
