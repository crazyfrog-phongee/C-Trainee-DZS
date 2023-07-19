#include <stdio.h>
#include <stdlib.h> /* Need for functions such as malloc() */
#include <unistd.h> /* Need for functions such as brk(), sbrk() */

int main(int argc, char const *argv[])
{
    char *ptr;

    /* The current limit of the Heap is referred to as the program break */
    printf("Program break: %p\n", sbrk(0));

    /* Dynamically allocated memory using malloc()/realloc() */
    ptr = (char *)malloc(25 * sizeof(char));
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
    }


    printf("Value of pointer: %p\n", ptr);
    
    for (int i = 1; i < 16; i++)
    {
        printf("%p  %d\n", (ptr - i), *(ptr - i));
    }
    free(ptr); /* ptr becomes Dangling pointer */
    if (ptr != NULL)
    {
        ptr = NULL;
    }

    return 0;
}
