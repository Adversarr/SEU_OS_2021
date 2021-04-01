#include "procedures.h"
int main(int argc, char **argv)
{
    /* For I/O bound program */
#ifndef CPU
    for (int i = 1; i < 100000; i *= 2)
        io_bound_function(i);
#else
    /* For cpu bound program */
    for (int i = 1; i < 100000; i *= 2)
        cpu_bound_function(i);
#endif
    return 0;
}