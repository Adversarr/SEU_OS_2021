gcc main.c -O2 -lpthread -pthread -o mm
for size in 10 100 1000 2000 4000 8000
do
    echo "##########################" $size "##########################"

    python gm.py $size $size "Amat$size.txt"
    python gm.py $size $size "Bmat$size.txt"
    for nt in 1 2 4 8
    do
        echo "mm -a Amat$size.txt -b Bmat$size.txt -t $nt"

        time -p ./mm -a Amat$size.txt -b Bmat$size.txt -t $nt
    done
done
echo "[DONE.]"
