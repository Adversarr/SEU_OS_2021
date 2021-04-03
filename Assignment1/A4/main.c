#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
int main()
{
    pid_t pid[4];
    FILE* file = fopen("./file.txt", "r");
    for (int i = 0; i < 4; ++i)
    {
        pid[i] = fork();
        if (pid[i] == 0){
            /* child process */
            
            char s[32];
            // fseek(file, (long) i * 24L, SEEK_SET);
            fgets(s, 32, file);
            fprintf(stdout,"%s", s);
            return 0;
        }
    }
    for (int i = 0; i < 4; ++i)
        waitpid(pid[i], NULL, 0);
    fclose(file);
    return 0;
}