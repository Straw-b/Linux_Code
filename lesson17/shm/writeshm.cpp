#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>

#define KEY 0x99999999

int main()
{
    int shmid = shmget(KEY, 1024, IPC_CREAT | 0664);
    if( shmid < 0 )
    {
        perror("shmget");
        return -1;
    }

    void* lp = shmat(shmid, NULL, 0);
    // for(int i = 0; i < 10000; i++)
    {
        char buf[1024] = {0};
        sprintf(buf, "%s-%d\n","linux-84", 1);
        strcpy((char*)lp, buf);
        sleep(1);
    }

    sleep(10);

    shmdt(lp); // 脱离


    struct shmid_ds buf;
    shmctl(shmid, IPC_STAT, &buf);
    printf("%lu\n", buf.shm_segsz);

    sleep(5);
    shmctl(shmid, IPC_RMID, NULL);

    while(1)
    {
        sleep(1);
    }

    return 0;
}
