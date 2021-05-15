gcc main.c -O2 -lpthread -pthread -o mm
for size in 16 128 1024 2048 4096 8192
do
    echo "##########################" $size "##########################"

    python gm.py $size $size "Amat$size.txt"
    python gm.py $size $size "Bmat$size.txt"
    for nt in 1 2 4 8
    do
        echo "mm -a Amat$size.txt -b Bmat$size.txt -t $nt"

        time ./mm -a Amat$size.txt -b Bmat$size.txt -t $nt
    done
done
echo "[DONE.]"
