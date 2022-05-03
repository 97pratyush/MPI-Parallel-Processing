#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define MAX_FILE_NAME 100
  
int main(int argc, char *argv[])
{
    clock_t start = clock();
    FILE* fp;
  
    // Character counter (result)
    int count = 0;

    char c;
  
    // Open the file
    fp = fopen(argv[1], "r");
  
    // Check if file exists
    if (fp == NULL) {
        printf("Could not open file %s");
        return 0;
    }
  
    // Extract characters from file
    // and store in character c
    for (c = getc(fp); c != EOF; c = getc(fp))
  
        // Increment count for this character
        if((c < 97 || c > 122) && !isspace(c)) count++;
  
    // Close the file
    fclose(fp);
  
    // Print the count of characters
    printf("The file has %d characters\n",count);

    clock_t end = clock();

    printf("Elapsed: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
  
    return 0;
}