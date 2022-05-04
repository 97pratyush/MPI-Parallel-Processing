# for i in `seq 1 69`; do
#         if [ $i -eq 10 ] | [ $i -eq 28 ] | [ $i -eq 29 ] | [ $i -eq 30 ] | [ $i -eq 31 ] | [ $i -eq 40 ] | [ $i -eq 48 ] | [ $i -eq 54 ] | [ $i -eq 55 ] ; then
#                 continue;
#         fi
#         cpuid -l 0x4ffffffc -s $i;
# done

for FILE in *; do 

        echo $FILE;

        # mpicc MPI.c -o mpitest;
        # mpirun -n 3 ./mpitest $FILE $FILE + ".out";
         
done