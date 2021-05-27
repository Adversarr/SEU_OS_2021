# badcnt.c
echo "I'm going to compile and run badcnt.c:"
gcc badcnt.c -o badcnt -lpthread && ./badcnt
# goodcnt.c
echo "I'm going to compile and run goodcnt.c:"
gcc goodcnt.c -o goodcnt -lpthread -lrt && ./goodcnt
