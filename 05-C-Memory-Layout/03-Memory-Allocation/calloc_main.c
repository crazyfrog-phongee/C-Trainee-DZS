#include <stdio.h>
#include <stdlib.h>

#define NUM_ITEMS   5
#define NEW_SIZE    10

int main(int argc, char const *argv[])
{
    int *ptr;

    /* Dynamically allocated memory using calloc() */
    ptr = (int *)calloc(NUM_ITEMS, sizeof(int));
    *ptr = 10;
    printf("The start address of the newly allocated block of memory: %p, %d\n", ptr, *ptr);
    ptr = (int *) malloc(1);

    /* Checking if the memory has been successfully allocated */
    if (ptr == NULL)
    {
        printf("Memory was not allocated\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Memory successfully allocated using calloc()\n");
        printf("The start address of the newly allocated block of memory: %p, %d, %d, %d\n", ptr, *ptr, *(ptr + 1), *(ptr + 2));
    }

    /* Dynamically re-allocate memory using realloc() */
    ptr = (int *)realloc(ptr, NEW_SIZE);
    // free(ptr);   
    ptr = (int *)realloc(ptr, 0); /* <=> free(ptr) */

    return 0;
}
