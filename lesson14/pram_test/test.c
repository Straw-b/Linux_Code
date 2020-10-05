#include <stdio.h>

void swap(int a, int b) // 输入型参数
{
    int c = a;
    a = b;
    b = c;
    printf("%d-%d\n", a, b);
}

void func(int* data) // 输出型参数
{
    *data = 10;
}

int main()
{
    swap(1, 2);
    int i;
    func(&i);
    printf("i = %d\n", i);

    return 0;
}
