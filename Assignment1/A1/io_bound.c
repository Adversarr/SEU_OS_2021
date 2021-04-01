#include"procedures.h"
#include<stdio.h>
void io_bound_function(int size)
{
    for (int i = 0; i < size * size; ++i)
        printf("Call IO bound function\n");
}