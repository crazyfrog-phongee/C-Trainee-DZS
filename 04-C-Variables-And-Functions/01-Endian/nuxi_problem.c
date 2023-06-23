#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    short int *s;

    s = (short int *)malloc(sizeof(short int));
    *s = "UN";
    s += 2;
    *s = "IX";

    return 0;
}
