#include <stdio.h>
#include <string.h>


int main()
{
    FILE* fp = fopen("./linux84", "w+");
    if(!fp)
    {
        perror("fopen");
        printf("open file failed\n");
        return -1;
    }
    printf("open file success\n");
    
    const char* str = "linux so easy\n";
    ssize_t ret = fwrite(str, 1, strlen(str), fp);
    printf("write block count is %d\n", ret);
    
    fseek(fp, 0, SEEK_SET);// 将文件流重置到文件头部

    char buf[1024] = {0};
    // 将块的大小设置为1，这是公司当中常用的方式
    // 但是我们一定要理解参数的含义
    ret = fread(buf, 1, 4, fp);
    printf("ret = %d, buf = %s\n", ret, buf);

    fclose(fp);
    return 0;
}

