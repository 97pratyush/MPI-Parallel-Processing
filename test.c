#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int getUpdatedValue(int valueToUpdate) {
    printf("\n----------- RUNNING getUpdatedValue() ------------\n");
    int num = valueToUpdate;
    FILE *fptr;

    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fptr = fopen("./statsfile.txt","r");

    if(fptr == NULL)
    {
        printf("File does not exist!\n");   
        // exit(1);     

        fptr = fopen("./statsfile.txt","w");
        fprintf(fptr,"%d",num);
        fclose(fptr);
        printf("File created and number %d written to file\n", num);
        return num;        
    } else {

        int numReadFromFile = 0;
        while ((read = getline(&line, &len, fptr)) != -1) {
            printf("Retrieved line of length %zu:\n", read);
            printf("%s\n", line);

            numReadFromFile = atoi(line);
            printf("numReadFromFile = %d\n", numReadFromFile);
        }
        fclose(fptr);

        int newNum = numReadFromFile + valueToUpdate;
        fptr = fopen("./statsfile.txt","w");
        fprintf(fptr,"%d", (newNum));
        printf("Updated number in the file to %d\n", newNum);
        printf("\nClosing file!\n");
        fclose(fptr);

        num = newNum;
    }
    
    printf("\n----------- COMPLETED getUpdatedValue() ------------\n");
    return num;
}

int main() {
    int a = getUpdatedValue(5);
    printf("\nValue from getUpdatedValue(): %d\n", a);

    return 0;
}