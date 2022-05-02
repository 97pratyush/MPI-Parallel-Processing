#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
    
void processFile(MPI_File *in, MPI_File *out, const int rank, const int size, const int overlap) {
    MPI_Offset globalstart;
    int mysize;
    char *chunk;
    {
        MPI_Offset globalend;
        MPI_Offset filesize;
    
        MPI_File_get_size(*in, &filesize);
        filesize--; 
        mysize = filesize/size;
        globalstart = rank * mysize;
        globalend   = globalstart + mysize - 1;
        if (rank == size-1) globalend = filesize-1;
    
        if (rank != size-1)
            globalend += overlap;
    
        mysize =  globalend - globalstart + 1;
    
        chunk = malloc( (mysize + 1)*sizeof(char));
    

        MPI_File_read_at_all(*in, globalstart, chunk, mysize, MPI_CHAR, MPI_STATUS_IGNORE);
        chunk[mysize] = '\0';
    }
    
    
    int locstart=0, locend=mysize-1;
    if (rank != 0) {
        while(chunk[locstart] != '\n') locstart++;
        locstart++;
    }
    if (rank != size-1) {
        locend-=overlap;
        while(chunk[locend] != '\n') locend++;
    }
    mysize = locend-locstart+1;
    
    // int counter[3];

    for (int i=locstart; i<=locend; i++) {
        char c = chunk[i];
        chunk[i] = ( isspace(c) ? c : '1' + (char)rank );

        // counter[rank] += isspace(c) ? 0 : 1;
    }

    // for(int i=0; i<3; i++) {
    //   printf("%d \n", counter[i]);
    // }

    
    MPI_File_write_at_all(*out, (MPI_Offset)(globalstart+(MPI_Offset)locstart), &(chunk[locstart]), mysize, MPI_CHAR, MPI_STATUS_IGNORE);
    
    return;
}
    
int main(int argc, char **argv) {
    
    MPI_File in, out;
    int rank, size;
    int ierr;
    const int overlap = 100;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    if (argc != 3) {
        if (rank == 0) fprintf(stderr, "Usage: %s infilename outfilename\n", argv[0]);
        MPI_Finalize();
        exit(1);
    }
    
    ierr = MPI_File_open(MPI_COMM_WORLD, argv[1], MPI_MODE_RDONLY, MPI_INFO_NULL, &in);
    if (ierr) {
        if (rank == 0) fprintf(stderr, "%s: Couldn't open file %s\n", argv[0], argv[1]);
        MPI_Finalize();
        exit(2);
    }
    
    ierr = MPI_File_open(MPI_COMM_WORLD, argv[2], MPI_MODE_CREATE|MPI_MODE_WRONLY, MPI_INFO_NULL, &out);
    if (ierr) {
        if (rank == 0) fprintf(stderr, "%s: Couldn't open output file %s\n", argv[0], argv[2]);
        MPI_Finalize();
        exit(3);
    }
    
    processFile(&in, &out, rank, size, overlap);
    
    MPI_File_close(&in);
    MPI_File_close(&out);
    
    MPI_Finalize();
    return 0;
}