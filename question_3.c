#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define BUFFER_SIZE 50
int main(int argc, char const *argv[])
{
    int pipefd[2];
    pid_t id,id1;
    unsigned char buff1[BUFFER_SIZE];
    pipe(pipefd);
    id=fork();
    if(id==0)
    {
        printf("child process1.\n");    //child process
        close(pipefd[1]);
        read(pipefd[0],buff1,BUFFER_SIZE);
        printf("found child 1.\n");
        printf("received from parent to child process 1:%s\n",buff1);
        close(pipefd[0]);
        id1=fork();
        if(id1==0)
        {
            printf("child process 2.\n");
            close(pipefd[1]);
            read(pipefd[0],buff1,BUFFER_SIZE);
            printf("found child 2.\n");
            printf("received from parent to child process 2:%s\n",buff1);
            close(pipefd[0]);
        }
    }
    else
    {
        close(pipefd[0]);
        write(pipefd[1],"hello world.\n",BUFFER_SIZE);
        close(pipefd[1]);

    }
    return 0;
}
