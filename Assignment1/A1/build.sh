gcc cpu_bound.c io_bound.c main.c -o io_bound_prog
gcc -DCPU cpu_bound.c io_bound.c main.c -o cpu_bound_prog