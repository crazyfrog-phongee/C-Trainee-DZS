#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    char *ptr = (char *) malloc(10 * sizeof(char));

    if (ptr == NULL)
    {
        printf("Memory was not allocated\n");
        exit(EXIT_FAILURE);
    }
    
    char *tmp = (char*)realloc(ptr, 512);

    if (tmp == NULL)
    {
        /* Handle error */
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Ptr: %p, %d\n", ptr, *ptr);
        printf("Tmp: %p, %d\n", tmp, *tmp);
    }
    
    return 0;
}
