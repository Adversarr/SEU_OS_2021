#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
    /* 1. Check the arguments */
    if (argc != 3)
    {
        printf("Error #args");
        exit(1);
    }
    /* 2. preprocess n and x */
    float x = atof(argv[1]);
    int n = atof(argv[2]);
    float t = x;
    float result = 1;

    /* 3. Calculate exp(x) using n terms*/
    for (int i = 1; i <= n; ++i)
    {
        result += t;
        t *= x / (i + 1);
    }

    /* 4. Print the required line*/
    printf("Child(PID=%d) : For x = %.3f the first %d terms yields %f\n", getpid(), x, n, result);

    return 0;
}