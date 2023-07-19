#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

typedef struct
{
    size_t numElements;
    int elements[1]; /* but enough space malloced for numElements at runtime */
} IntArray_t;

int main(int argc, char const *argv[])
{
    IntArray_t *myArray = malloc(sizeof(IntArray_t) + SIZE * sizeof(int));
    myArray->numElements = SIZE;
    
    return 0;
}

