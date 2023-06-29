#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int *ptr;
    ptr = (int *)calloc(5, sizeof(int));
    for (int i = 0; i < 6; i++)
    {
        *(ptr + i) = i;
    }

    for (int i = 0; i < 6; i++)
    {
        printf("%p %d", ptr, *(ptr + i));
    }
    
    while (1);
    
    return 0;
}
