#include <stdio.h>

int main(int argc, char const *argv[])
{
    unsigned int num = 1;
    char *ptr = (char *)&num;
    if (*ptr)
        printf("Little endian\n");
    else
        printf("Big endian\n");
    return 0;
}
