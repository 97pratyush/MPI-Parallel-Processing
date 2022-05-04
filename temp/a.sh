#!/bin/bash

# SUB='.txt'
for FILE in *; do 


        # if [ "$FILE" == *"$SUB"* ]; then
        #   echo $FILE;
        # fi

        mpicc MPI.c -o mpitest;
        mpirun -n 3 ./mpitest $FILE "$FILE.out";

done