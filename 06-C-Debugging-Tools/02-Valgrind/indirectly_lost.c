#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void **rrr;

int main(int argc, char const *argv[])
{   
    rrr = malloc(sizeof(void **));
    *rrr = (char *)strdup("bbb");
    rrr = NULL;
    return 0;
}
