#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
int main(int argc, char** argv)
{
    if (argc != 3)
    {
        printf("Error #args");
        exit(1);
    }
    
    /* a. launch another process */
    pid_t pid = fork(); 

    if (pid) {
        /* Parent */
        /* c. wait for the child */
        waitpid(pid, NULL, 0);
        /* e. print*/
        printf("Parent(PID=%d): Done\n", getpid());

    } else {
        /* Child */
        
        execlp("./file2", "./file2", argv[1], argv[2], NULL);
    }
    return 0;
}