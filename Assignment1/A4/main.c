#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
int main()
{
    // open the required file
    pid_t pid1 = fork();

    if (pid1)
    {
        /* Parent -> fork 3 more*/
        pid_t pid2 = fork();
        if (pid2)
        {
            /* Parent -> fort 2 more */
            pid_t pid3 = fork();
            if (pid3)
            {
                /* Parent -> fork one*/
                pid_t pid4 = fork();
                if (pid4)
                {
                    /* Parent -> wait for 1234 */
                    waitpid(pid1, NULL, 0);
                    waitpid(pid2, NULL, 0);
                    waitpid(pid3, NULL, 0);
                    waitpid(pid4, NULL, 0);
                }
                else
                {
                    char str[32];
                    FILE *file = fopen("file.txt", "r");
                    fgets(str, 32, file);
                    fgets(str, 32, file);
                    fgets(str, 32, file);
                    fgets(str, 32, file);
                    printf("%s\n", str);
                    fclose(file);
                }
            }
            else
            {
                /* Child 3 */
                char str[32];
                FILE *file = fopen("file.txt", "r");
                fgets(str, 32, file);
                fgets(str, 32, file);
                fgets(str, 32, file);
                printf("%s\n", str);
                fclose(file);
            }
        }
        else
        {
            /* Child 2*/
            char str[32];
            FILE *file = fopen("file.txt", "r");
            fgets(str, 32, file);
            fgets(str, 32, file);
            printf("%s\n", str);
            fclose(file);
        }
    }
    else
    {
        /* Child 1: read first line. */
        FILE *file = fopen("file.txt", "r");
        char str[32];
        fgets(str, 32, file);

        printf("%s\n", str);
        fclose(file);
    }

    return 0;
}