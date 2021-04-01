#include<unistd.h>
#include<sys/wait.h>
#include<stdio.h>
int main()
{
    printf("Parent start!(pid = %d)\n", getpid());
    pid_t pid = fork();
    if (pid)
    {
        /* Parent process */
        /* 1. Wait for child process*/
        waitpid(pid, NULL, 0); 
        /* 2. Print child's pid*/
        printf("Child pid is %d\n", pid);
    }
    else
    {
        /* Child process */
        /* 1. echo~ */
        printf("Hello world (from Child process %d)\n", getpid());
        printf("Sleep for 2 seconds~\n");
        /* 2. sleep for several seconds*/
        sleep(2);
        printf("I'm Awake~\n");
    }
    return 0;
}