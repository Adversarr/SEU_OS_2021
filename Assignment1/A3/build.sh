echo '===============================ITR = 1==============================='
gcc -DITR=1 code_for_asgn_1.c -o prog
./prog


echo '===============================ITR = 10==============================='
gcc -DITR=10 code_for_asgn_1.c -o prog
./prog

echo '===============================ITR = 100==============================='
gcc -DITR=100 code_for_asgn_1.c -o prog
./prog

echo '===============================ITR = 1000==============================='
gcc -DITR=1000 code_for_asgn_1.c -o prog
./prog

echo '===============================ITR = 10000==============================='
gcc -DITR=10000 code_for_asgn_1.c -o prog
./prog

echo '===============================origin==============================='
gcc code_for_asgn_1.c -o prog
./prog