#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Error #args");
        exit(1);
    }

    float x = atof(argv[0]);
    int n = atof(argv[1]);
    float t = x;
    float result = 1;

    for (int i = 1; i <= n; ++i)
    {
        result += t;
        t *= x / (i + 1);
    }

    printf("Child(PID=%d) : For x = %.3f the first %d terms yields %f\n", getpid(), x, n, result);

    return 0;
}