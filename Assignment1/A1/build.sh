gcc cpu_bound.c io_bound.c main.c -o io_bound_prog
gcc -DCPU cpu_bound.c io_bound.c main.c -o cpu_bound_prog
touch ./tmp.txt
taskset -c 0 ./io_bound_prog&
taskset -c 0 ./cpu_bound_prog&
top
