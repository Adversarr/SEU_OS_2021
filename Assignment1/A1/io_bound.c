#include"procedures.h"
#include<stdio.h>
void io_bound_function(int size)
{
    for (int i = 0; i < size * size; ++i)
    {
        FILE* file = fopen("./tmp.txt", "w");
        fprintf(file, "Call IO bound function");
        fclose(file);
    }
}
