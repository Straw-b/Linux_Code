#include <stdio.h>


enum DataType
{
    apple = 0,
    banana,
    //...
};

struct Data
{
    int type;
    char data[1024];
};

int main()
{
    Data a;
    a.type = 1;
    Data b;
    b.type = 2;
    return 0;
}
