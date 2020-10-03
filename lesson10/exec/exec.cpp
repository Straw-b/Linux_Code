#include <stdio.h>
#include <unistd.h>

int main()
{
    // execl 进程程序替换
    printf("hahahaha,begin...\n");
    
#if 0
    getchar();
    // 看到pwd的结果，那就是替换成功了
    printf("pid : %d\n", getpid());
    execl("/usr/bin/pwd", "pwd",NULL);
    printf("execl failed\n");
#endif

#if 0
    execlp("ls", "ls", "-l", NULL);
    printf("execlp failed\n");
#endif

#if 0
    char* argv[10];
    argv[0] = "ls";
    argv[1] = "-l";
    argv[2] = NULL;
    int ret = execv("/usr/bin/ls", argv);
    printf("execv failed, ret = %d\n", ret);
#endif

    char* argv[10];
    argv[0] = "ls";
    argv[1] = "-l";
    argv[2] = NULL;

    char* envp[10];
    envp[0] = "PATH=/usr/bin";
    envp[1] = NULL;
    int ret = execve("/usr/bin/ls", argv, envp);
    printf("execve failed, ret = %d\n", ret);

    return 0;
}
