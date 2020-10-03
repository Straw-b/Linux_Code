#include <stdio.h>

// 命令行参数
// 在启动这个程序时，可以给这个程序从命令行当中传递一些参数

int main(int argc, char* argv[], char* env[])
{
    // grac --> 代表命令行参数的个数
    // grgv --> 代表每一个命令行参数的值
    // argc的值对应argv数组的下标
    // env --> 代表环境变量
    for (int i=0; i<argc; i++)
    {
        printf("argv[%d] : %s\n", i, argv[i]);
    }

    return 0;
}
