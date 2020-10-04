#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    // close(0);
    
    int ret = -1;
    ret = open("./linux84", O_RDWR | O_CREAT, 0664);
    if(ret < 0)
    {
        return -1;
    }
    printf("file oper ret = %d\n", ret);

    while(1)
    {
        sleep(1);
    }

    return 0;
}
