#include <stdio.h>
#include <string.h>
#include <iostream>

#define func(x,y) (x)*(y)

int sum(int& a, int& b)
{
    int c = a + b;   
    return c;

}

struct data
{
    data() 
    {
        memset(buf, '\0', sizeof(buf));
    }
    int data1;
    int data2;
    char buf[20];

};

int main()
{
    std::string buf = "hahah";
    data d;
    d.data1 = 777;
    d.data2 = 888;
    strcpy(d.buf, "test struct");

    int a = 10;
    int b = 20;
    int ret = sum(a, b);
    printf("ret = %d\n", ret);
    //以下是宏
    printf("func:%d\n", func(1,2));
    printf("func:%d\n", func(2,2+2));
    printf("linux84 666\n");

    printf("20200728\n");
    return 0;

}
