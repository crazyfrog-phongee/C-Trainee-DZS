#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>

void *rrr;

int main(int argc, char const *argv[])
{
    rrr = (char *)strdup("bbb");
    rrr = ((char *)rrr) + 1;
    return 0;
}
