#include <stdio.h>
#include <stdlib.h> /* Need for functions such as malloc() */
#include <unistd.h> /* Need for functions such as brk(), sbrk() */

int main(int argc, char const *argv[])
{
    int *ptr;

    /* The current limit of the Heap is referred to as the program break */
    printf("Program break: %p\n", sbrk(0));

    /* Dynamically allocated memory using malloc()/realloc() */
    ptr = (int *)malloc(100000000 * sizeof(int));
    // ptr = (int *)realloc(NULL, 5 * sizeof(int));

    /* Checking if the memory has been successfully allocated */
    if (ptr == NULL)
    {
        printf("Memory was not allocated\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Memory successfully allocated using malloc()/realloc() \n");
        /* Get the elements of the array */
        // for (int i = 0; i < 5; ++i) 
        // {
        //     ptr[i] = i + 1;
        // }
 
        // /* Print the elements of the array */
        // printf("The elements of the array are: ");
        // for (int i = 0; i < 5; ++i) 
        // {
        //     printf("%d ", ptr[i]);
        // }
        // printf("\n");

    }

    free(ptr); /* ptr becomes Dangling pointer */
    if (ptr != NULL)
    {
        ptr = NULL;
    }

    return 0;
}
