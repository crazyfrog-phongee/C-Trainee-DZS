#include <stdio.h>


int sub(int first, int second)
{
    return second - first;
}

int main(int argc, char const *argv[])
{
    int x = 10;
    int a = x;
    int b = x;
    int c = a + b;
    printf("%d\n", c);
    printf("%d\n", sub(3, 5));
    
    return 0;
}
