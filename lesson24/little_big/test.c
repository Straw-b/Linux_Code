#include <stdio.h>

int main()
{
    union Data
    {
        int a;
        char b;

    }date;

    date.a = 1;

    if(date.b)
    {
        //小端
        printf("little\n");            
    }
    else
    {
        //大端
        printf("big\n");            
    }

    return 0;
}
